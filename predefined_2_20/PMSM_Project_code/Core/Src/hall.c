#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_tim.h"
#include "model_param.h"
#include "msconfig.h"
#include "hall.h"
#include <string.h>
#include "mc_aux.h"

HallHandle_t hall_handle;

HallHandle_t *HallGetHandle(void)
{
	return &hall_handle;
}

void HallInit(void)
{
	HallHandle_t *phandle;

	phandle = HallGetHandle();

	// Set hall_handle to 0
	memset(phandle, 0, sizeof(HallHandle_t));

	// Initialize member variables
	phandle->TIMx = TIM3;
	phandle->direction = DIR_POSTIVE;
	phandle->operational = 1;
	phandle->err_cnt = 0;
	if(MOTOR_TYPE == MOTOR_TYPE_TG5P60)
		phandle->hall_bemf = (int16_t)(HALL_BEMF_TG5P60 * 65536/360);
	else if(MOTOR_TYPE == MOTOR_TYPE_JSF630)
		phandle->hall_bemf = (int16_t)(HALL_BEMF_JSF630 * 65536/360);
	else if(MOTOR_TYPE == MOTOR_TYPE_TB2P)
		phandle->hall_bemf = (int16_t)(HALL_BEMF_TB2P * 65536/360);
	else
		phandle->hall_bemf = (int16_t)(HALL_BEMF_TB2P * 65536/360);

	LL_TIM_SetUpdateSource(phandle->TIMx, LL_TIM_UPDATESOURCE_COUNTER);

	LL_TIM_EnableIT_CC1(phandle->TIMx);
	LL_TIM_EnableIT_UPDATE(phandle->TIMx);
	LL_TIM_SetCounter(phandle->TIMx, 0);

	LL_TIM_CC_EnableChannel(phandle->TIMx, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableCounter(phandle->TIMx);
}

void HallInitElAngle(void)
{
	HallHandle_t *phandle;

	phandle = HallGetHandle();

	if(MOTOR_TYPE == MOTOR_TYPE_JSF630)
	{
		phandle->cur_state = (HAL_GPIO_ReadPin(H2_GPIO_PORT, H2_PIN) << 2) | \
				  (HAL_GPIO_ReadPin(H3_GPIO_PORT, H3_PIN) << 1) | \
				  (HAL_GPIO_ReadPin(H1_GPIO_PORT, H1_PIN) << 0);
	}
	else
	{
	phandle->cur_state = (HAL_GPIO_ReadPin(H3_GPIO_PORT, H3_PIN) << 2) | \
			  (HAL_GPIO_ReadPin(H2_GPIO_PORT, H2_PIN) << 1) | \
			  (HAL_GPIO_ReadPin(H1_GPIO_PORT, H1_PIN) << 0);
	}

  switch(phandle->cur_state)
  {
	case HALL_STATE5:
	  phandle->theat_e = ( int16_t )(phandle->hall_bemf + S16_DEGREE_60 / 2);
	  break;
	case HALL_STATE1:
	  phandle->theat_e = ( int16_t )(phandle->hall_bemf + S16_DEGREE_60 + S16_DEGREE_60 / 2);
	  break;
	case HALL_STATE3:
	  phandle->theat_e = ( int16_t )(phandle->hall_bemf + S16_DEGREE_120 + S16_DEGREE_60 / 2);
	  break;
	case HALL_STATE2:
	  phandle->theat_e = ( int16_t )(phandle->hall_bemf - S16_DEGREE_120 - S16_DEGREE_60 / 2);
	  break;
	case HALL_STATE6:
	  phandle->theat_e = ( int16_t )(phandle->hall_bemf - S16_DEGREE_60 - S16_DEGREE_60 / 2);
	  break;
	case HALL_STATE4:
	  phandle->theat_e = ( int16_t )(phandle->hall_bemf - S16_DEGREE_60 / 2);
	  break;
	default:
	  /* HALL has encountered an abnormal state and is set to be inoperable */
	  phandle->operational = 0;
	  phandle->err_cnt++;
	  break;
  }

  /* Initialize the measured angle */
  phandle->measured_theat_e = phandle->theat_e;

}

void HallClear(void)
{
	uint8_t i;
	HallHandle_t *phandle;

	phandle = HallGetHandle();

	LL_TIM_DisableIT_CC1(phandle->TIMx);

	phandle->ovf_num = 0;
	phandle->comp_spd = 0;
	phandle->direction = DIR_POSTIVE;
	phandle->operational = 1;
	phandle->err_cnt = 0;
	phandle->buf_filled = 0;
	phandle->buf_idx = 0;
	for(i = 0; i < HALL_BUFF_SIZE; i++)
		phandle->state_period[i] = 0;
	phandle->period_sum = 0;
	phandle->first_capt = 0;
	phandle->avr_spd_dpp = 0;
	phandle->state_upd_time = ClkGetTime();
//	phandle->is_stall = 0;
		
	/* Re-initialize partly the timer */
	LL_TIM_SetCounter(phandle->TIMx, 0);
	LL_TIM_EnableCounter(phandle->TIMx);
	LL_TIM_EnableIT_CC1(phandle->TIMx);

	HallInitElAngle();
}

void HallTimUPIRQHandler(void)
{
	HallHandle_t *phandle;

	phandle = HallGetHandle();

	phandle->ovf_num++;
}

void HallTimCCIRQHandler(void)
{
	uint8_t pre_state;
	uint32_t cap_period;
	HallHandle_t *phandle;

	phandle = HallGetHandle();

	/* 1, get hall state */
	pre_state = phandle->cur_state;
	if(MOTOR_TYPE == MOTOR_TYPE_JSF630)
	{
		phandle->cur_state = (HAL_GPIO_ReadPin(H2_GPIO_PORT, H2_PIN) << 2) | \
					(HAL_GPIO_ReadPin(H3_GPIO_PORT, H3_PIN) << 1) | \
					(HAL_GPIO_ReadPin(H1_GPIO_PORT, H1_PIN) << 0);
	}
	else
	{
	phandle->cur_state = (HAL_GPIO_ReadPin(H3_GPIO_PORT, H3_PIN) << 2) | \
				(HAL_GPIO_ReadPin(H2_GPIO_PORT, H2_PIN) << 1) | \
				(HAL_GPIO_ReadPin(H1_GPIO_PORT, H1_PIN) << 0);
	}

	phandle->state_upd_time = ClkGetTime();

	/* 2, calc rotate direction and measured_theat_e */
	switch(phandle->cur_state)
	{
		case HALL_STATE5:
		{
			if(pre_state == HALL_STATE4)
			{
				phandle->direction = DIR_POSTIVE;
				phandle->measured_theat_e = phandle->hall_bemf;
			}
			else if(pre_state == HALL_STATE1)
			{
				phandle->direction = DIR_NEGTIVE;
				phandle->measured_theat_e = phandle->hall_bemf + S16_DEGREE_60;
			}
		}
		break;
		case HALL_STATE1:
		{
			if(pre_state == HALL_STATE5)
			{
				phandle->direction = DIR_POSTIVE;
				phandle->measured_theat_e = phandle->hall_bemf + S16_DEGREE_60;
			}
			else if(pre_state == HALL_STATE3)
			{
				phandle->direction = DIR_NEGTIVE;
				phandle->measured_theat_e = phandle->hall_bemf + S16_DEGREE_120;
			}
		}
		break;
		case HALL_STATE3:
		{
			if(pre_state == HALL_STATE1)
			{
				phandle->direction = DIR_POSTIVE;
				phandle->measured_theat_e = phandle->hall_bemf + S16_DEGREE_120;
			}
			else if(pre_state == HALL_STATE2)
			{
				phandle->direction = DIR_NEGTIVE;
				phandle->measured_theat_e = phandle->hall_bemf + S16_DEGREE_120 + S16_DEGREE_60;
			}
		}
		break;
		case HALL_STATE2:
		{
			if(pre_state == HALL_STATE3)
			{
				phandle->direction = DIR_POSTIVE;
				phandle->measured_theat_e = phandle->hall_bemf + S16_DEGREE_120 + S16_DEGREE_60;
			}
			else if(pre_state == HALL_STATE6)
			{
				phandle->direction = DIR_NEGTIVE;
				phandle->measured_theat_e = phandle->hall_bemf - S16_DEGREE_120;
			}
		}
		break;
		case HALL_STATE6:
		{
			if(pre_state == HALL_STATE2)
			{
				phandle->direction = DIR_POSTIVE;
				phandle->measured_theat_e = phandle->hall_bemf - S16_DEGREE_120;
			}
			else if(pre_state == HALL_STATE4)
			{
				phandle->direction = DIR_NEGTIVE;
				phandle->measured_theat_e = phandle->hall_bemf - S16_DEGREE_60;
			}
		}
		break;
		case HALL_STATE4:
		{
			if(pre_state == HALL_STATE6)
			{
				phandle->direction = DIR_POSTIVE;
				phandle->measured_theat_e = phandle->hall_bemf - S16_DEGREE_60;
			}
			else if(pre_state == HALL_STATE5)
			{
				phandle->direction = DIR_NEGTIVE;
				phandle->measured_theat_e = phandle->hall_bemf;
			}
		}
		break;
		default:
		  /* HALL has encountered an abnormal state and is set to be inoperable */
		//  phandle->operational = 0;
			phandle->err_cnt++;
		  break;
	}

	if(phandle->first_capt == 0)
	{
		phandle->first_capt++;
		cap_period = LL_TIM_IC_GetCaptureCH1(phandle->TIMx);
	}
	else
	{
		uint32_t min_peroid;

		min_peroid = MIN_PERIOD_FACT / MOTOR_PN;

		/* 3, get current period */
		cap_period = LL_TIM_IC_GetCaptureCH1(phandle->TIMx);
		cap_period += (phandle->ovf_num * 65536);
		if(cap_period >= min_peroid)
		{
			phandle->period_sum -= phandle->state_period[phandle->buf_idx];
			phandle->state_period[phandle->buf_idx] = cap_period;
			phandle->state_period[phandle->buf_idx] *= phandle->direction;
			phandle->period_sum += phandle->state_period[phandle->buf_idx];

			phandle->buf_idx++;
			if(phandle->buf_idx >= HALL_BUFF_SIZE)
				phandle->buf_idx = 0;

			if(phandle->buf_filled < HALL_BUFF_SIZE)
				phandle->buf_filled++;

			/* 4, calc avrage speed dpp */
			if(phandle->buf_filled < HALL_BUFF_SIZE)
			{
				phandle->avr_spd_dpp = (int16_t)((CALC_DPP_FACT1 / cap_period)*phandle->direction);
			}
			else
			{
				uint32_t max_peroid;
				max_peroid = MAX_PERIOD_FACT / MOTOR_PN;
				if(cap_period >= max_peroid)
					phandle->avr_spd_dpp = (int16_t)((CALC_DPP_FACT1 / cap_period)*phandle->direction);
				else
					phandle->avr_spd_dpp = (int16_t)((int32_t)CALC_DPP_FACT1 / (phandle->period_sum / HALL_BUFF_SIZE));
			}
		}
	}
	
	/* 5, reset overflow num */
	phandle->ovf_num = 0;
}

uint8_t HallCalcSpdPos(int16_t *mec_spd, int32_t *mec_pos)
{
	int32_t value;
	HallHandle_t *phandle;

	phandle = HallGetHandle();
	
	if(phandle->operational == 0)
		return 0;

	/**********************************************************
	Function: Detect motor stalling and handle it
	- Record the number of stalling times
	- Execute HallClear drive motor to continue rotating
	**********************************************************/
	if(McGetMotorStart())
	{
		/**********************************************************
		Basis for blockage judgment:
		1. Hall status has not been updated for more than 1 second
		2. The control direction is forward rotation, but the feedback direction is reverse rotation
		3. The control direction is reverse, but the feedback direction is forward
		**********************************************************/
		if(((phandle->first_capt > 0) && (ClkGetTime() - phandle->state_upd_time >= 500)) || 
			((McGetSpdRef() >= 0) && (phandle->avr_spd_dpp < 0)) || 
			((McGetSpdRef() < 0) && (phandle->avr_spd_dpp > 0)))
		{
			phandle->stall_cnt++;
			HallClear();
		}
	}

	/* Calculate Mechanical speed in rpm */
	phandle->delta_theat = phandle->measured_theat_e - phandle->theat_e;
	phandle->comp_spd = (int16_t)((int32_t)(phandle->delta_theat) / (int32_t)(PWMNUM_PER_MTASK));

	value = phandle->avr_spd_dpp * PWM_FREQUENCY;	// s16 degree per second
	value *= 60;									// s16 degree per min
	value /= 65536;									// rotate per min
	value /= ((int8_t)MOTOR_PN);					// el to mec
	phandle->mec_spd = (int16_t)value;
	*mec_spd = phandle->mec_spd;

	/* Hall does not support positional calculation, assign a value of 0 */
	*mec_pos = 0;
	
	return 1;
}

uint8_t HallCalcAngle(int16_t *theat_e)
{
	HallHandle_t *phandle;

	phandle = HallGetHandle();
	
	if(phandle->operational == 0)
		return 0;

	phandle->measured_theat_e += phandle->avr_spd_dpp;
	phandle->theat_e += (phandle->avr_spd_dpp + phandle->comp_spd);
	*theat_e = phandle->theat_e;

	return 1;
}


