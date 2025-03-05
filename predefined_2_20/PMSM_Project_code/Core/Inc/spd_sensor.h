#ifndef SPD_SENSOR_H_
#define	SPD_SENSOR_H_

void SensorInit(void);
void SensorAlign(void);
void SensorClear(void);
uint8_t SensorCalcSpdPos(int16_t *mec_spd, int32_t *mec_pos);
uint8_t SensorCalcAngle(int16_t *theat_e);

#endif

