#ifndef MC_AUX_H_
#define	MC_AUX_H_

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
/* part1: Necessary operations for normal operation of ADC and PWM */
void McAuxInit(void);
void SystickConfig(void);
void ClkIncTime(void);
uint32_t ClkGetTime(void);
void PwmTimStart(void);
void ADC1_Start_IT(void);
void GetPhaseCurrent(void);
void FocControler(void);
void SetTim1CCRX(void);
void TIMx_UP_IRQHandler(void);
void TurnOnPWM(void);
void TurnOffPWM(void);
void PWMLowSideOn(void);
void McCalcOffsetVol(void);
void StmSwitchAction(void);

/* part2: Motor control interface function */
uint8_t McGetSysCtrlMode(void);
uint8_t McSetSysCtrlMode(uint8_t mode);
void McKeySetSysCtrlMode(void);
void McStartMotor(void);
void McStopMotor(void);
uint8_t McGetMotorStart(void);
int8_t McGetRotateDir(void);
void McSetRotateDir(int8_t dir);
void McIncSpdRef(void);
void McDecSpdRef(void);
uint8_t McSetPosRef(float pos_rad, float duration_sec);

/* part3: Current variable interface function */
uint16_t McGetIaOri(void);
uint16_t McGetIbOri(void);
int16_t McGetIa(void);
int16_t McGetIb(void);
int16_t McGetIc(void);
int16_t McGetId(void);
int16_t McGetIq(void);
int16_t McGetIdRef(void);
int16_t McGetIqRef(void);
int16_t McGetUd(void);
int16_t McGetUq(void);
int16_t McGetUalpha(void);
int16_t McGetUbeta(void);
int16_t McGetTheatE(void);

/* part4: Speed variable interface function */
int16_t McGetSpdFed(void);
int16_t McGetSpdFedSensor(void);
int16_t McGetSpdRef(void);
void McSetSpdRef(int16_t speed);

/* part5: position variable interface function */
float McGetPosRefRad(void);
int32_t McGetPosRefInt(void);
int32_t McGetPosFedS16(void);
float McGetPosFedRad(void);

#endif

