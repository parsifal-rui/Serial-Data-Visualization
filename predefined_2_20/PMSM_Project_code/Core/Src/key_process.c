#include "stm32f1xx_hal.h"
#include "key_read.h"
#include "key_process.h"
#include "string.h"
#include "stdio.h"
//#include "vofa_justfloat_engine.h"
//#include "mc_api.h"
#include "mmcs_s2f.h"
#include "model_param.h"
#include "msconfig.h"
#include "mc_aux.h"

KeyObj_t keyobj_group[] = 
{
	{KEY_RUN_GPIO_PORT, 	KEY_RUN_PIN, 	KEY_UP_LEVEL, 0},
	{KEY_STOP_GPIO_PORT, 	KEY_STOP_PIN, 	KEY_UP_LEVEL, 0},
	{KEY_UP_GPIO_PORT, 		KEY_UP_PIN, 	KEY_UP_LEVEL, 0},
	{KEY_DOWN_GPIO_PORT, 	KEY_DOWN_PIN, 	KEY_UP_LEVEL, 0},
	{KEY_DIR_GPIO_PORT, 	KEY_DIR_PIN, 	KEY_UP_LEVEL, 0},
};


void KeyProcInit(void)
{
	uint8_t i;
	uint8_t len;

	len = sizeof(keyobj_group) / sizeof(KeyObj_t);

	for(i = 0; i < len; i++)
	{
		KeyObjInit(&keyobj_group[i]);
	}
}

uint8_t KeyGetKeyValue(void)
{
	uint8_t len;
	KeyVal_t key_value;
	uint8_t key_value1;
	
	len = sizeof(keyobj_group) / sizeof(KeyObj_t);
	key_value = ReadGroupKey(keyobj_group, len);
	key_value1 = key_value.key_idx * KEY_EVT_MAX + key_value.key_evt;

	return key_value1;
}

void KeyProcess(void)
{
	uint8_t len;
	KeyVal_t key_value;
	uint8_t key_value1;
//	static uint8_t preset_seq = 0;
	
	len = sizeof(keyobj_group) / sizeof(KeyObj_t);
	key_value = ReadGroupKey(keyobj_group, len);
	key_value1 = key_value.key_idx * KEY_EVT_MAX + key_value.key_evt;
	
	switch (key_value1)
	{
		case KEY_RUN_DOWN:
		{
			McStartMotor();
		}
		break;
		case KEY_STOP_DOWN:
		{
			McStopMotor();
		}
		break;
		case KEY_UP_DOWN:
		{
			if(McGetSysCtrlMode() == ENC_PT_CTRL)
			{
				float pos_rad;
				
				pos_rad = McGetPosFedRad();
				McSetPosRef(pos_rad + 60*MC_PI, 4);
			}
			else
			{
				McIncSpdRef();
			}
		}
		break;
		case KEY_DOWN_DOWN:
		{
			if(McGetSysCtrlMode() == ENC_PT_CTRL)
			{
				float pos_rad;
				
				pos_rad = McGetPosFedRad();
				McSetPosRef(pos_rad - 60*MC_PI, 4);
			}
			else
			{
				McDecSpdRef();
			}
		}
		break;
		case KEY_DIR_DOWN:
		{
			if(McGetMotorStart() == 0)
			{
				int16_t spd;

				/* switch rotate direction */
				if(McGetRotateDir() == DIR_POSTIVE)
					McSetRotateDir(DIR_NEGTIVE);
				else
					McSetRotateDir(DIR_POSTIVE);

				/* switch spd_ref */
				spd = McGetSpdRef();
				McSetSpdRef(-spd);
			}
			
			#if 0
			uint8_t mode;

			mode = McGetSysCtrlMode();
			if(mode == ENC_ST_CTRL)
			{
				McSetSysCtrlMode(ENC_PT_CTRL);
			}
			else if(mode == ENC_PT_CTRL)
			{
				McSetSysCtrlMode(ENC_ST_CTRL);
			}
			#endif
		}
		break;
		default:
		break;
	}

}


