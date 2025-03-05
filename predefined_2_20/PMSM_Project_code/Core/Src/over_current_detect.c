#include "stm32f1xx_hal.h"
#include "over_current_detect.h"
#include "mc_aux.h"
#include "led.h"

//static OCDetect_t oc_detect_handle;
OCDetect_t oc_detect_handle;

OCDetect_t *OcDetectGetHandle(void)
{
	return &oc_detect_handle;
}

void OcDetectInit(void)
{
	OCDetect_t *phandle;

	phandle = OcDetectGetHandle();
	phandle->oc_cnt = 0;
	phandle->pre_oc_time = 0;
	phandle->is_oc = 0;
	phandle->is_oc_cnt = 0;
}

void OcDetectExec(void)
{
	int16_t id;
	int16_t iq;
	OCDetect_t *phandle;
	
	phandle = OcDetectGetHandle();
	if(phandle->is_oc)
	{
		if(ClkGetTime() - phandle->pre_oc_time >= 5000)	// 10s
		{
			phandle->is_oc = 0;
			LedFreqSet(LED_FREQ_2HZ);
		}
	}

	if(McGetMotorStart() == 0)
		return;
		
	// get id, iq
	id = McGetId();
	iq = McGetIq();

	if((id >= OVER_CURRENT_UPL) || (id <= OVER_CURRENT_LOL) || \
		(iq >= OVER_CURRENT_UPL) || (iq <= OVER_CURRENT_LOL))
	{
		uint32_t cur_time;
		uint32_t interval_time;
		
		/* Current overload occurred during this sampling */
		cur_time = ClkGetTime();
		interval_time = cur_time - phandle->pre_oc_time;
		
		if(interval_time <= 10)		// 1*ClkTime=2ms, 10 here represents 20ms
		{
			/* Less than 20ms since the last overload time */
			phandle->oc_cnt++;
			if(phandle->oc_cnt >= 30)	// 30*20ms=600ms
			{
				/* Stop the motor if the number of consecutive overloads exceeds 10 times */
				McStopMotor();
				TurnOffPWM();
				phandle->oc_cnt = 0;
				phandle->is_oc = 1;
				phandle->is_oc_cnt++;
				LedFreqSet(LED_FREQ_5HZ);
			}
		}
		else if(interval_time >= 50)	// // 1*ClkTime=2ms, 50 here represents 100ms
		{
			phandle->oc_cnt = 0;
		}

		/* Record the overload time this time */
		phandle->pre_oc_time = cur_time;
	}
}


