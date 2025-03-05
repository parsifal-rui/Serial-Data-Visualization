#include "stm32f1xx_hal.h"
#include "stm32f1xx_ll_tim.h"
#include "model_param.h"
#include "msconfig.h"
#include "encoder.h"
#include <string.h>
#include "mmcs_s2f.h"

EncHandle_t enc_handle;

EncHandle_t *EncGetHandle(void)
{
	return &enc_handle;
}

void EncInit(void)
{
	EncHandle_t *phandle;

	phandle = EncGetHandle();

	memset(phandle, 0, sizeof(EncHandle_t));
	phandle->TIMx = TIM2;

//	LL_TIM_EnableIT_UPDATE(phandle->TIMx);
	LL_TIM_SetCounter(phandle->TIMx, 0);
	LL_TIM_EnableCounter(phandle->TIMx);
}

void EncAlign(void)
{
	EncHandle_t *phandle;

	phandle = EncGetHandle();
	
	phandle->TIMx->CNT = 0;
	phandle->enc_cnt = 0;
	phandle->enc_cnt_pre = 0;
	phandle->enc_cnt_pos = 0;
}

void EncClear(void)
{
	uint8_t i;
	EncHandle_t *phandle;

	phandle = EncGetHandle();
	
	for(i = 0; i < ENC_BUFF_SIZE; i++)
	{
		phandle->buff[i] = 0;
	}
}


/***********************************************
1, GetEncCnt: get enc_cnt_mf, of_cnt, cnt_dir
2, GetEncCnt must be called before speed_torq_ctrl_step1
3, GetEncCnt provide params for SpdCalc calc
***********************************************/
void EncGetTimInfo(void)
{
	EncHandle_t *phandle;

	phandle = EncGetHandle();
	
	phandle->enc_cnt = phandle->TIMx->CNT; 			// encoder pluse counter
	phandle->cnt_dir = LL_TIM_GetDirection(phandle->TIMx);	// encoder counter direction
	if(phandle->cnt_dir == TIM_COUNTERMODE_UP)
	{
	  if(phandle->enc_cnt < phandle->enc_cnt_pre)
		  phandle->of_cnt = 1;						// overflow occurred
	  else
		  phandle->of_cnt = 0;						// No overflow occurred
	}
	else
	{
		if(phandle->enc_cnt > phandle->enc_cnt_pre)
			phandle->of_cnt = 1; 					// overflow occurred
		else
			phandle->of_cnt = 0; 					// No overflow occurred
	}
	
	/* record enc_cnt：Move to EncCalcMecSpeed to record */
	//	phandle->enc_cnt_pre = phandle->enc_cnt_mf;
	
}

uint8_t EncCalcSpdPos(int16_t *mec_spd, int32_t *mec_pos)
{
	int32_t pulses_once;	// Encoder pulse count per speed sampling
	int32_t pulse_freq;		// Encoder pulse frequency
	EncHandle_t *phandle;

	phandle = EncGetHandle();

	/* update encoder TIM info */
	EncGetTimInfo();

	/* Calculate Encoder pulse count per speed sampling */
	pulses_once = (int32_t)(phandle->enc_cnt) - (int32_t)(phandle->enc_cnt_pre);
	if(phandle->cnt_dir == 0)
		pulses_once += ((int32_t)(phandle->of_cnt) * (int32_t)ENC_PULSE_NUM);
	else
		pulses_once -= ((int32_t)(phandle->of_cnt) * (int32_t)ENC_PULSE_NUM);

	phandle->pulses_once = pulses_once;
	
	/* Calculate the average encoder pulse count for each sampling */
	phandle->pulses_avr = EncGetBuffAvgVal(pulses_once);

	/* Calculate encoder pulse frequency：pulses/s */
	pulse_freq = phandle->pulses_avr * SPD_SAMPLE_FREQ;

	/* Calculate Mechanical speed in rpm */
	phandle->mec_spd = pulse_freq * 60 / ((int32_t)ENC_PULSE_NUM);
	*mec_spd = phandle->mec_spd;

	/* Calculate Mechanical position */
	if((pulses_once < PULSES_ONCE_THR) && (pulses_once > -PULSES_ONCE_THR))
	{
		/* pulses_once needs to be within the threshold, otherwise it is a sampling error */
		int64_t temp;
		
		phandle->enc_cnt_pos += pulses_once;
		temp = phandle->enc_cnt_pos * 65536;
		temp /= (int32_t)ENC_PULSE_NUM;
		phandle->mec_pos = (int32_t)temp;
		*mec_pos = phandle->mec_pos;
	}
	
	/* record enc_cnt */
	phandle->enc_cnt_pre = phandle->enc_cnt;
	
	return 1;
}

#if 0
uint8_t EncCalcAngle(int16_t *theat_e)
{
	uint32_t cnt;
	EncHandle_t *phandle;

	phandle = EncGetHandle();

	/* theat_e = cnt * U32MAXdivPulseNumber * Pn / 65536 */
	cnt = phandle->TIMx->CNT;
	phandle->theat_e = (int16_t)(cnt * U32MAXdivPulseNumber * MOTOR_PN / 65536);
	*theat_e = phandle->theat_e;

	return 1;
}
#endif

uint8_t EncCalcAngle(int16_t *theat_e)
{
	int64_t temp1;
	int16_t theta_m;
	uint32_t cnt;
	EncHandle_t *phandle;

	phandle = EncGetHandle();

	/* theat_e = cnt * U32MAXdivPulseNumber * Pn / 65536 */
	cnt = phandle->TIMx->CNT;
	temp1 = cnt * U32MAXdivPulseNumber;
	theta_m = (int16_t)(temp1 / 65536);
	phandle->theat_e = (int16_t)(theta_m * MOTOR_PN);
//	phandle->theat_e = (int16_t)(cnt * U32MAXdivPulseNumber * MOTOR_PN / 65536);
	*theat_e = phandle->theat_e;

	return 1;
}

int32_t EncGetBuffAvgVal(int32_t in_data)
{
	uint8_t i;
	int32_t sum;
	int32_t avg;
	EncHandle_t *phandle;

	phandle = EncGetHandle();

	/* put new data in buffer */
	phandle->buff[phandle->index] = in_data;
	phandle->index++;
	if(phandle->index >= ENC_BUFF_SIZE)
		phandle->index = 0;

	/* calc buff average val */
	sum = 0;
	for(i = 0; i < ENC_BUFF_SIZE; i++)
	{
		sum += phandle->buff[i];
	}
	avg = sum/ENC_BUFF_SIZE;

	return avg;
}


