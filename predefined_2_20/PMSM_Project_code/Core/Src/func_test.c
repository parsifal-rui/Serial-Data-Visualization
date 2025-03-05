#include "stm32f1xx_hal.h"
#include "func_test.h"
#include "usart.h"
#include "mc_aux.h"
#include "msconfig.h"

/**********************************************************
HAL_StatusTypeDef RS485RcvFw1B(void)
Function: RS485 receives 1 byte and forwards it, Used for RS485 testing
caller: Can be called in while (1) of main()
**********************************************************/
HAL_StatusTypeDef RS485RcvFw1B(void)
{
	uint8_t rev_data;
	HAL_StatusTypeDef ret;
	
	ret = HAL_UART_Receive(&huart1, &rev_data, 1, 10);
	if(ret == HAL_OK)
	{
		ret = HAL_UART_Transmit(&huart1, &rev_data, 1, 10);
	}

	return ret;
}

/**********************************************************
void PosCtrlAutoPan(void)
Function: In position control mode, automatically move between two points, Used for posctrl testing
caller: Can be called in while (1) of main()
**********************************************************/
void PosCtrlAutoPan(void)
{
	static uint32_t dly_time = 1000;
	static uint8_t stat1 = 0;
	static uint32_t last_time = 0;


	if(stat1 == 0)
	{
		/* start motor */
		if(ClkGetTime() >= 500)	// dly 1s
		{
			McStartMotor();
			
			stat1 = 1;
			last_time = ClkGetTime();
			dly_time = 1000;		// dly 2s exec next task 
		}
	}
	else if(stat1 == 1)
	{
		if(ClkGetTime() - last_time >= dly_time)
		{
			float pos_rad;
			
			pos_rad = McGetPosFedRad();
			McSetPosRef(pos_rad + 60*MC_PI, 4);

			stat1 = 2;
			last_time = ClkGetTime();
			dly_time = 3500;		// dly 6s exec next task 
		}
	}
	else if(stat1 == 2)
	{
		if(ClkGetTime() - last_time >= dly_time)
		{
			float pos_rad;
			
			pos_rad = McGetPosFedRad();
			McSetPosRef(pos_rad - 60*MC_PI, 4);

			stat1 = 1;
			last_time = ClkGetTime();
			dly_time = 3500;		// dly 6s exec next task 
		}
	}
}

