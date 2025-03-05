#include "stm32f1xx_hal.h"
#include "encoder.h"
#include "hall.h"
#include "model_param.h"
#include "mc_aux.h"

void SensorInit(void)
{
	uint8_t mode;

	mode = McGetSysCtrlMode();
	if((mode == ENC_ST_CTRL) || (mode == ENC_PT_CTRL))
		EncInit();
	else if(mode == HALL_ST_CTRL)
		HallInit();
	else
	{
		/* Generally, there is a hall, which can be enabled in sto mode for synchronous monitoring */
	//	EncInit();
		HallInit();
	}
}

void SensorAlign(void)
{
	uint8_t mode;

	mode = McGetSysCtrlMode();
	if((mode == ENC_ST_CTRL) || (mode == ENC_PT_CTRL))
		EncAlign();
}


void SensorClear(void)
{
	uint8_t mode;

	mode = McGetSysCtrlMode();
	if((mode == ENC_ST_CTRL) || (mode == ENC_PT_CTRL))
		EncClear();
	else if(mode == HALL_ST_CTRL)
		HallClear();
	else
	{
		/* Generally, there is a hall, which can be enabled in sto mode for synchronous monitoring */
	//	EncClear();
		HallClear();
	}
}

uint8_t SensorCalcSpdPos(int16_t *mec_spd, int32_t *mec_pos)
{
	uint8_t mode;

	mode = McGetSysCtrlMode();
	if((mode == ENC_ST_CTRL) || (mode == ENC_PT_CTRL))
		return EncCalcSpdPos(mec_spd, mec_pos);
	else if(mode == HALL_ST_CTRL)
		return HallCalcSpdPos(mec_spd, mec_pos);
	else
	{
		/* Generally, there is a hall, which can be enabled in sto mode for synchronous monitoring */
	//	return EncCalcSpdPos(mec_spd, mec_pos);
		return HallCalcSpdPos(mec_spd, mec_pos);
	}
}

uint8_t SensorCalcAngle(int16_t *theat_e)
{
	uint8_t mode;

	mode = McGetSysCtrlMode();
	if((mode == ENC_ST_CTRL) || (mode == ENC_PT_CTRL))
		return EncCalcAngle(theat_e);
	else if(mode == HALL_ST_CTRL)
		return HallCalcAngle(theat_e);
	else
	{
		/* Generally, there is a hall, which can be enabled in sto mode for synchronous monitoring */
	//	return EncCalcAngle(theat_e);
		return HallCalcAngle(theat_e);
	}
}


