#include "string.h"
#include "vofa_justfloat_engine.h"
#include "mc_aux.h"
#include "usart.h"
#include "mmcs_s2f.h"
#include "hall.h"

uint8_t CurrentLoopVarCpy(float *pbuf)
{
	uint8_t chan_num;

	chan_num = 0;
	
	if(pbuf)
	{
		*pbuf = (float)McGetIa();
		pbuf++;
		*pbuf = (float)McGetIb();
		pbuf++;
		*pbuf = (float)McGetIc(); // Add-on
		pbuf++;
		#if 0
		*pbuf = (float)McGetId();
		pbuf++;
		*pbuf = (float)McGetIq();
		pbuf++;
		*pbuf = (float)McGetIdRef();
		pbuf++;
		*pbuf = (float)McGetIqRef();
		pbuf++;
		*pbuf = (float)McGetTheatE();
		pbuf++;
		#endif

		chan_num = 3;
	}
	
	return chan_num;
}

uint8_t SpdLoopVarCpy(float *pbuf)
{
	uint8_t chan_num;

	chan_num = 0;
	
	if(pbuf)
	{
		*pbuf = (float)McGetSpdRef();
		pbuf++;
		//*pbuf = (float)McGetSpdFedSensor();
		//pbuf++;
		*pbuf = (float)McGetSpdFed();
		pbuf++;

		chan_num = 2;
	}
	
	return chan_num;
}

uint8_t PosLoopVarCpy(float *pbuf)
{
	uint8_t chan_num;

	chan_num = 0;
	
	if(pbuf)
	{
		//*pbuf = (float)McGetPosRefInt();
		//pbuf++;
		*pbuf = (float)McGetPosFedS16();
		pbuf++;
		//*pbuf = (float)(McGetPosRefInt() - McGetPosFedS16());
		//pbuf++;

		chan_num = 1;
	}
	
	return chan_num;
}

#if 1
uint8_t HallVarCpy(float *pbuf)
{
	uint8_t chan_num;
	
	chan_num = 0;
	
	if(pbuf)
	{
		HallHandle_t *phandle;
		phandle = HallGetHandle();
		
	//	*pbuf = (float)phandle->state_period[phandle->buf_idx];
	//	pbuf++;
	//	*pbuf = (float)phandle->avr_spd_dpp;
	//	pbuf++;
		*pbuf = (float)phandle->cur_state;
		pbuf++;
		chan_num = 1;
	}
	
	return chan_num;
}
#endif

HAL_StatusTypeDef JustfloatSendFocVar(void)
{
	float *pbuf;
	uint8_t chan_num;
	uint8_t chan_total;
	HAL_StatusTypeDef ret;
	uint8_t justfloat_frame_buf[96];
	uint8_t tail[4] = {0x00, 0x00, 0x80, 0x7F};

	chan_num = 0;
	chan_total = 0;
	
	/* get justfloat frame buf*/
	pbuf = (float *)justfloat_frame_buf;

	#if 1
	/* get current loop var */
	chan_num = CurrentLoopVarCpy(pbuf);
	pbuf += chan_num;
	chan_total += chan_num;
	#endif

	#if 1
	/* get speed loop var */
	chan_num = SpdLoopVarCpy(pbuf);
	pbuf += chan_num;
	chan_total += chan_num;
	#endif
	
	/* get position loop var */
	chan_num = PosLoopVarCpy(pbuf);
	pbuf += chan_num;
	chan_total += chan_num;
	#if 0
	/* get hall var */
	chan_num = HallVarCpy(pbuf);
	pbuf += chan_num;
	chan_total += chan_num;
	#endif
	
	/* add justfloat frame tail */
	memcpy((uint8_t *)pbuf, tail, sizeof(tail));

	/* send justfloat frame */

	ret = HAL_UART_Transmit(&huart1, justfloat_frame_buf, chan_total * sizeof(float) + sizeof(tail), 10);
	
	return ret;

}

