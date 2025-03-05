/**********************************************************
MC_AUX
1. motor control auxiliary
2. The motor control is mainly completed by MATLAB and CubeMX. 
   This document implements complete motor control through necessary auxiliary work, including:
   - Necessary operations for normal operation of ADC and PWM
   - Motor control interface function
   - Current variable interface function
   - Speed variable interface function
   - position variable interface function
**********************************************************/

#include "stm32f1xx_hal.h"
#include "mc_aux.h"
#include "tim.h"
#include "adc.h"
#include "mmcs_s2f.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_adc.h"
#include "model_param.h"
#include "msconfig.h"
#include "spd_sensor.h"
#include "key_process.h"

uint8_t adc_eoc;				// ADC conversion completed
uint16_t ia_adc_ori;
uint16_t ib_adc_ori;
uint32_t ia_offset;				// A-phase current offset value
uint32_t ib_offset;				// B-phase current offset value
int8_t rotate_dir;				// Motor rotation direction
static uint32_t clk_time_2ms;	// 2ms counter


/* part1: Necessary operations for normal operation of ADC and PWM */

/**********************************************************
void McAuxInit(void)
Function: Initialize the relevant variables defined in this document
**********************************************************/
void McAuxInit(void)
{
	// ADC related variable initialization
	adc_eoc = 0;
	ia_adc_ori = 0;
	ib_adc_ori = 0;
	ia_offset = 32768;
	ib_offset = 32768;
	clk_time_2ms = 0;

	// rotate direction initialization
	if(spd_ref >= 0)
		rotate_dir = DIR_POSTIVE;
	else
		rotate_dir = DIR_NEGTIVE;
}

/**********************************************************
void SystickConfig(void)
Function: Configure systick interrupt frequency to 500Hz
**********************************************************/
void SystickConfig(void)
{
	/* start systick(f = 500Hz) */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/SPD_SAMPLE_FREQ);
}

/**********************************************************
void ClkIncTime(void)
Function: 2ms counter increase
caller: Calling within a systick interrupt
**********************************************************/
void ClkIncTime(void)
{
	clk_time_2ms++;
}

/**********************************************************
uint32_t ClkGetTime(void)
Function: Obtain absolute system time in 2ms
Return: 2ms counter, which represents the absolute time from power on 
        to the current time, measured in 2ms
**********************************************************/
uint32_t ClkGetTime(void)
{
	return clk_time_2ms;
}

/**********************************************************
void PwmTimStart(void)
Function: Start PWM timer(Start timer and enable interrupt)
**********************************************************/
void PwmTimStart(void)
{
	uint32_t i;
	
	/* TIM1 channels 1-4 output enable */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);		// CCxE：输出使能；MOE：主输出使能
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);	// CCxNE：互补输出使能；MOE：主输出使能
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

	/* Enable TIM1 update interrupt */
	HAL_TIM_Base_Start_IT(&htim1);					// 允许TIM1更新中断，即UIE = 1
	
	/* close PWM during initialization phase */
	TurnOffPWM();
	
	for(i = 0; i < 5000000; i++);

}

/**********************************************************
void ADC1_Start_IT(void)
Function: Start ADC and enable interrupt
**********************************************************/
void ADC1_Start_IT(void)
{
	// adc calibration
	HAL_ADCEx_Calibration_Start( &hadc1);
	HAL_ADCEx_Calibration_Start( &hadc2);

	// clear flag
	__HAL_ADC_CLEAR_FLAG( &hadc1, ADC_FLAG_JEOC);
	__HAL_ADC_CLEAR_FLAG( &hadc1, ADC_FLAG_EOC);
	__HAL_ADC_CLEAR_FLAG( &hadc2, ADC_FLAG_JEOC);
	__HAL_ADC_CLEAR_FLAG( &hadc2, ADC_FLAG_EOC);

	// start
	HAL_ADCEx_InjectedStart_IT(&hadc1);
	/* lww: ADC1 and ADC2 share the same interrupt processing program, 
	do not enable two interrupts, as this may result in ADC1 not being able to collect data; 
	It is recommended to only enable ADC1 interrupt and read ADC1 and ADC2 conversion data 
	simultaneously in the interrupt processing program */
//	HAL_ADCEx_InjectedStart_IT(&hadc2);
}

/**********************************************************
void GetPhaseCurrent(void)
Function: Read the ADC and convert it to phase current in units of s16A
caller: Calling within a ADC interrupt
**********************************************************/
void GetPhaseCurrent(void)
{
	int32_t value;
	
	/* disable ADC trigger source */
	LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH4);

	/* read ADC data */
	ia_adc_ori = (ADC1->JDR1 << 4); 
	ib_adc_ori = (ADC2->JDR1 << 4);

	// caculate ia
	value = (int32_t)(ia_offset) - (int32_t)(ia_adc_ori);
	if(value < -32767)
		iab_adc[0] = -32767;
	else if(value > 32767)
		iab_adc[0] = 32767;
	else
		iab_adc[0] = value;

	// caculate ib
	value = (int32_t)(ib_offset) - (int32_t)(ib_adc_ori);
	if(value < -32767)
		iab_adc[1] = -32767;
	else if(value > 32767)
		iab_adc[1] = 32767;
	else
		iab_adc[1] = value;

	adc_eoc = 1;

}

/**********************************************************
void FocControler(void)
Function: Complete FOC high-frequency tasks (calculating angles, calling 
          high-frequency tasks, setting TIM1->CCRX)
caller: Must be called after GetPhaseCurrent()
**********************************************************/
void FocControler(void)
{
	/* Assign encoder pulse number to HFTask for angle calc */
	SensorCalcAngle(&theta_sensor);
	
	/* call HFTask */
	mmcs_s2f_step0();

	/* Assign the action time calculated by SVPWM to MCU CCRX */
	SetTim1CCRX();
}

/**********************************************************
void SetTim1CCRX(void)
Function: setting TIM1->CCRX
**********************************************************/
void SetTim1CCRX(void)
{
	TIM1->CCR1 = mcu_ccrx[0];
	TIM1->CCR2 = mcu_ccrx[1];
	TIM1->CCR3 = mcu_ccrx[2];
}

/**********************************************************
void TIMx_UP_IRQHandler(void)
Function: TIMx_UP_IRQHandler
**********************************************************/
void TIMx_UP_IRQHandler(void)
{
	/* Disabling trigger to avoid unwanted conversion */
	LL_ADC_INJ_StopConversionExtTrig(ADC1);
	LL_ADC_INJ_StopConversionExtTrig(ADC2);

	/* Enabling next Trigger */
	LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH4);

	LL_ADC_INJ_StartConversionExtTrig(ADC1, LL_ADC_INJ_TRIG_EXT_RISING);
	LL_ADC_INJ_StartConversionExtTrig(ADC2, LL_ADC_INJ_TRIG_EXT_RISING);
  
}

/**********************************************************
void TurnOnPWM(void)
Function: Turn on PWM output
**********************************************************/
void TurnOnPWM(void)
{  
	/* Set all duty to 50% */
	LL_TIM_OC_SetCompareCH1(TIM1, (uint32_t)PWM_PERIOD_CYCLES_HALF);
	LL_TIM_OC_SetCompareCH2(TIM1, (uint32_t)PWM_PERIOD_CYCLES_HALF);
	LL_TIM_OC_SetCompareCH3(TIM1, (uint32_t)PWM_PERIOD_CYCLES_HALF);
	LL_TIM_OC_SetCompareCH4(TIM1, (uint32_t)(PWM_PERIOD_CYCLES_HALF - 2u));
  
	/* wait for a new PWM period */
	LL_TIM_ClearFlag_UPDATE(TIM1);
	while ( LL_TIM_IsActiveFlag_UPDATE( TIM1 ) == 0 )
	{}
	/* Clear Update Flag */
	LL_TIM_ClearFlag_UPDATE(TIM1);

	/* Main PWM Output Enable */
	TIM1->BDTR |= LL_TIM_OSSI_ENABLE;
	LL_TIM_EnableAllOutputs( TIM1 );

	/* Clear Update Flag */
	LL_TIM_ClearFlag_UPDATE( TIM1 );
	/* Enable Update IRQ */
	LL_TIM_EnableIT_UPDATE(TIM1);

}

/**********************************************************
void TurnOffPWM(void)
Function: Turn off PWM output
**********************************************************/
void TurnOffPWM(void)
{ 
	/* Disable UPDATE ISR */
	LL_TIM_DisableIT_UPDATE( TIM1 );
  
	/* Main PWM Output Disable */
	LL_TIM_DisableAllOutputs( TIM1 );

	/* wait for a new PWM period */
	LL_TIM_ClearFlag_UPDATE(TIM1);
	while ( LL_TIM_IsActiveFlag_UPDATE( TIM1 ) == 0 )
	{}
	LL_TIM_ClearFlag_UPDATE(TIM1);
}

/**********************************************************
void PWMLowSideOn(void)
Function: Turn on the low side MOSFET of the inverter
**********************************************************/
void PWMLowSideOn(void)
{  
	/* Set all duty to 50% */
	LL_TIM_OC_SetCompareCH1(TIM1, 0);
	LL_TIM_OC_SetCompareCH2(TIM1, 0);
	LL_TIM_OC_SetCompareCH3(TIM1, 0);
	LL_TIM_OC_SetCompareCH4(TIM1, (uint32_t)(PWM_PERIOD_CYCLES_HALF - 2u));
  
	/* wait for a new PWM period */
	LL_TIM_ClearFlag_UPDATE(TIM1);
	while ( LL_TIM_IsActiveFlag_UPDATE( TIM1 ) == 0 )
	{}
	/* Clear Update Flag */
	LL_TIM_ClearFlag_UPDATE(TIM1);

	/* Main PWM Output Enable */
	TIM1->BDTR |= LL_TIM_OSSI_ENABLE;
	LL_TIM_EnableAllOutputs( TIM1 );

	/* Clear Update Flag */
	LL_TIM_ClearFlag_UPDATE( TIM1 );
	/* Enable Update IRQ */
	LL_TIM_EnableIT_UPDATE(TIM1);
}

/**********************************************************
void McCalcOffsetVol(void)
Function: Calculate the offset value of the ADC at zero phase current
**********************************************************/
void McCalcOffsetVol(void)
{
	uint16 i;
	uint32 ia_sum;
	uint32 ib_sum;
	
	/* Turn on the low side of the three-phase inverter */
	PWMLowSideOn();

	/* Delay waiting for stability */
	for(i = 0; i <= 1000; i++);

	/* Initialize ia, ib accumulator */
	ia_sum = 0;
	ib_sum = 0;

	/* Calculate the average of ADC 16 times */	
	for(i = 0; i < 128; i++)
	{
		// Waiting for ADC conversion to complete
		while(adc_eoc == 0);
		adc_eoc = 0;
		
		ia_sum += ia_adc_ori;
		ib_sum += ib_adc_ori;
	}
	ia_offset = ia_sum >> 7;
	ib_offset = ib_sum >> 7;

	/* close PWM output */
	TurnOffPWM();
}

/**********************************************************
void StmSwitchAction(void)
Function: Detect state switching and take necessary actions
**********************************************************/
void StmSwitchAction(void)
{
	static uint8_t align = 0;
	static uint8_t last_state = 0;
	
	/* Record alignment completion flag */
	if((last_state == STM_ALIGN) && (stm_state != STM_ALIGN))
	{
		align = 1;
	}

	/* close pwm output while entry stop state */
	if((last_state != STM_STOP) && (stm_state == STM_STOP))
	{
		TurnOffPWM();
	}

	/* After alignment, enter the stop state and perform the alignment operation of the speed sensor */
	if((last_state != STM_STOP_IDLE) && (stm_state == STM_STOP_IDLE))
	{
		if(align)
		{
			align = 0;
			SensorAlign();
		}
	}

	/* open pwm output while entry STM_START state */
	if((last_state == STM_PREPARE) && (stm_state == STM_START))
	{
		SensorClear();
		TurnOnPWM();
	}

	last_state = stm_state;
}


/* part2: Motor control interface function */

uint8_t McGetSysCtrlMode(void)
{
	return sys_ctrl_mode;
}

uint8_t McSetSysCtrlMode(uint8_t mode)
{
	if(stm_state != STM_IDLE)
		return false;
	
	sys_ctrl_mode = mode;
	if(sys_ctrl_mode == ENC_PT_CTRL)
	{
		float pos_rad;

		pos_rad = McGetPosFedRad();
		McSetPosRef(pos_rad, 5);
	}
	
	return true;
}

void McKeySetSysCtrlMode(void)
{
	uint32_t i;
	uint8_t key_value1;

	for(i = 0; i < 10000; i++)
	{
		key_value1 = KeyGetKeyValue();

		if(MOTOR_TYPE == MOTOR_TYPE_TB2P)
		{
			switch(key_value1)
			{
				case KEY_STOP_DOWN:
					sys_ctrl_mode = IF_CTRL;
				break;
				case KEY_UP_DOWN:
					sys_ctrl_mode = STO_ST_CTRL;
				break;
				case KEY_DOWN_DOWN:
				break;
				case KEY_DIR_DOWN:
				break;
				default:
				break;
			}
		}
		else if((MOTOR_TYPE == MOTOR_TYPE_TG5P60) || (MOTOR_TYPE == MOTOR_TYPE_JSF630))
		{
			switch(key_value1)
			{
				case KEY_STOP_DOWN:
					sys_ctrl_mode = IF_CTRL;
				break;
				case KEY_UP_DOWN:
					sys_ctrl_mode = STO_ST_CTRL;
				break;
				case KEY_DOWN_DOWN:
					sys_ctrl_mode = HALL_ST_CTRL;
				break;
				case KEY_DIR_DOWN:
					sys_ctrl_mode = ENC_PT_CTRL;
				break;
				default:
				break;
			}
		}
	}
}

void McStartMotor(void)
{
	if(motor_start == 0)
	{
		motor_start = 1;
	}
}

void McStopMotor(void)
{
	if(motor_start == 1)
	{
		motor_start = 0;
	}
}

uint8_t McGetMotorStart(void)
{
	return motor_start;
}

int8_t McGetRotateDir(void)
{
	return rotate_dir;
}

void McSetRotateDir(int8_t dir)
{
	rotate_dir = dir;
}

void McIncSpdRef(void)
{
	if(McGetRotateDir() == DIR_POSTIVE)
	{
		if(spd_ref < 50)
			spd_ref += 10;
		else
			spd_ref += 50;
		
		if(spd_ref >= MAX_CLOSELOOP_SPD)
			spd_ref = MAX_CLOSELOOP_SPD;
	}
	else
	{
		if(spd_ref > -50)
			spd_ref -= 10;
		else
			spd_ref -= 50;
		if(spd_ref <= (-MAX_CLOSELOOP_SPD))
			spd_ref = (-MAX_CLOSELOOP_SPD);
	}
}

void McDecSpdRef(void)
{
	int16_t min_spd;
	uint8_t	ctrl_mode;

	// Set minimum speed
	min_spd = MIN_CLOSELOOP_SPD;

	ctrl_mode = McGetSysCtrlMode();
	if(ctrl_mode == STO_ST_CTRL)
	{
		min_spd = MIN_STO_SPD;
	}
	else if(ctrl_mode == HALL_ST_CTRL)
	{
		if(MOTOR_TYPE == MOTOR_TYPE_TG5P60)
			min_spd = MIN_HALL_SPD_TG5P60;
		else if(MOTOR_TYPE == MOTOR_TYPE_JSF630)
			min_spd = MIN_HALL_SPD_JSF630;
		else if(MOTOR_TYPE == MOTOR_TYPE_TB2P)
			min_spd = MIN_HALL_SPD_TB2P;
		else
			min_spd = MIN_HALL_SPD_TB2P;
	}
	
	if(McGetRotateDir() == DIR_NEGTIVE)
		min_spd = -min_spd;

	// Reduce reference speed
	if(McGetRotateDir() == DIR_POSTIVE)
	{
		if(spd_ref > min_spd + 50)
			spd_ref -= 50;
//		else if(spd_ref > min_spd + 10)
//			spd_ref -= 10;
		else
			spd_ref = min_spd;
	}
	else
	{
		if(spd_ref <= (min_spd - 50))
			spd_ref += 50;
//		else if(spd_ref <= (min_spd - 10))
//			spd_ref += 10;
		else
			spd_ref = min_spd;
	}
}

uint8_t McSetPosRef(float pos_rad, float duration_sec)
{
	uint8_t ret;

	ret = 0;
	if(duration_sec > 0)
	{
		float radps;
		float distance;

		/* Calculate the distance traveled */
		distance = pos_rad - McGetPosFedRad();
		if(distance < 0)
			distance = -distance;

		/* Calculate rad/s */
		radps = distance / duration_sec;
		if(radps > 30*MC_PI)
		{
			/* Suggest no more than 15rps(30/2pi = 15) */
			radps = 30*MC_PI;
			duration_sec = distance / radps;
		}
		else if(radps < 2*MC_PI)
		{
			/* Suggest no less than 1rps(2pi/2pi = 1) */
			radps = 2*MC_PI;
			duration_sec = distance / radps;
		}
	
		pos_ref = pos_rad;
		move_duration = duration_sec;

		ret = 1;
	}
	return ret;
}


/* part3: Current variable interface function */

uint16_t McGetIaOri(void)
{
	return ia_adc_ori;
}

uint16_t McGetIbOri(void)
{
	return ib_adc_ori;
}

int16_t McGetIa(void)
{
	return ia;
}

int16_t McGetIb(void)
{
	return ib;
}

int16_t McGetIc(void)
{
	return (-ia - ib);	// ia + ib + ic = 0
}

int16_t McGetId(void)
{
	return id;
}

int16_t McGetIq(void)
{
	return iq;
}

int16_t McGetIdRef(void)
{
	return id_ref;
}

int16_t McGetIqRef(void)
{
	return iq_ref;
}

int16_t McGetUd(void)
{
	return ud;
}

int16_t McGetUq(void)
{
	return uq;
}

int16_t McGetUalpha(void)
{
	return u_alpha;
}

int16_t McGetUbeta(void)
{
	return u_beta;
}

int16_t McGetTheatE(void)
{
	return theta_e;
}


/* part4: Speed variable interface function */

int16_t McGetSpdFed(void)
{
	return spd_fed;
}

int16_t McGetSpdFedSensor(void)
{
	return spd_sensor;
}

int16_t McGetSpdRef(void)
{
	return spd_ref;
}

void McSetSpdRef(int16_t speed)
{
	uint16_t spd_abs;

	if(speed >= 0)
		spd_abs = speed;
	else
		spd_abs = (-speed);

	if(spd_abs <= MAX_CLOSELOOP_SPD)
		spd_ref = speed;
}


/* part5: position variable interface function */
float McGetPosRefRad(void)
{
	return pos_ref;
}

int32_t McGetPosRefInt(void)
{
	return pos_ref_int;
}

int32_t McGetPosFedS16(void)
{
	return pos_fed;
}

float McGetPosFedRad(void)
{
	float pos_rad;

	pos_rad = (float)(pos_fed / RADTOS16_F);

	return pos_rad;
}


