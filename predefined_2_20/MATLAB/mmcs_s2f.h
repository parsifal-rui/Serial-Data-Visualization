/*
 * File: mmcs_s2f.h
 *
 * Code generated for Simulink model 'mmcs_s2f'.
 *
 * Model version                  : 1.729
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Mon Oct 28 20:34:39 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_mmcs_s2f_h_
#define RTW_HEADER_mmcs_s2f_h_
#ifndef mmcs_s2f_COMMON_INCLUDES_
#define mmcs_s2f_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "em_sincos.h"
#include "circle_limit.h"
#include "em_svpwm.h"
#include "trajectory_ctrl.h"
#endif                                 /* mmcs_s2f_COMMON_INCLUDES_ */

#include "mmcs_s2f_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Child system includes */
#include "HFTask.h"
#include "MFTask.h"
#include "SpeedConvert.h"

/* Includes for objects with custom storage classes */
#include "model_param.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  int32_T RT5;                         /* '<Root>/RT5' */
  uint16_T sfun_EmSvpwm_o1;            /* '<S9>/sfun_EmSvpwm' */
  uint16_T sfun_EmSvpwm_o2;            /* '<S9>/sfun_EmSvpwm' */
  uint16_T sfun_EmSvpwm_o3;            /* '<S9>/sfun_EmSvpwm' */
  int16_T RT3[2];                      /* '<Root>/RT3' */
  int16_T RT4;                         /* '<Root>/RT4' */
  int16_T UnitDelay8;                  /* '<Root>/Unit Delay8' */
  int16_T spd_ref_h;                   /* '<Root>/RT9' */
  int16_T RT8;                         /* '<Root>/RT8' */
  int16_T avg;                         /* '<S5>/GetAvgVal' */
  int16_T Merge2;                      /* '<S4>/Merge2' */
  int16_T DataTypeConversion;          /* '<S124>/Data Type Conversion' */
  uint8_T RT1;                         /* '<Root>/RT1' */
  uint8_T RT2;                         /* '<Root>/RT2' */
  uint8_T RT_a;                        /* '<Root>/RT' */
  uint8_T RT6;                         /* '<Root>/RT6' */
  B_SpeedConvert_mmcs_s2f_T SpeedConvert;/* '<Root>/SpeedConvert' */
  B_MFTask_mmcs_s2f_T MFTask;          /* '<Root>/MFTask' */
  B_HFTask_mmcs_s2f_T HFTask;          /* '<Root>/HFTask' */
} B_mmcs_s2f_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  int16_T UnitDelay8_DSTATE;           /* '<Root>/Unit Delay8' */
  volatile int16_T RT3_Buffer[4];      /* '<Root>/RT3' */
  volatile int16_T RT4_Buffer0;        /* '<Root>/RT4' */
  volatile int8_T RT3_ActiveBufIdx;    /* '<Root>/RT3' */
  volatile uint8_T RT1_Buffer0;        /* '<Root>/RT1' */
  volatile uint8_T RT2_Buffer0;        /* '<Root>/RT2' */
  DW_SpeedConvert_mmcs_s2f_T SpeedConvert;/* '<Root>/SpeedConvert' */
  DW_MFTask_mmcs_s2f_T MFTask;         /* '<Root>/MFTask' */
  DW_HFTask_mmcs_s2f_T HFTask;         /* '<Root>/HFTask' */
} DW_mmcs_s2f_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCE_HFTask_mmcs_s2f_T HFTask;        /* '<Root>/HFTask' */
} PrevZCX_mmcs_s2f_T;

/* Real-time Model Data Structure */
struct tag_RTM_mmcs_s2f_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_mmcs_s2f_T mmcs_s2f_B;

/* Block states (default storage) */
extern DW_mmcs_s2f_T mmcs_s2f_DW;

/* Zero-crossing (trigger) state */
extern PrevZCX_mmcs_s2f_T mmcs_s2f_PrevZCX;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint8_T motor_start;            /* '<Root>/motor_start' */
extern uint8_T sys_ctrl_mode;          /* '<Root>/sys_ctrl_mode' */
extern int16_T spd_ref;                /* '<Root>/spd_ref' */
extern real32_T pos_ref;               /* '<Root>/pos_ref' */
extern real32_T move_duration;         /* '<Root>/move_duration' */
extern int16_T iab_adc[2];             /* '<Root>/iab_adc' */
extern int16_T spd_sensor;             /* '<Root>/spd_sensor' */
extern int16_T theta_sensor;           /* '<Root>/theta_sensor' */
extern int32_T pos_fed;                /* '<Root>/pos_sensor' */
extern uint16_T mcu_ccrx[3];           /* '<Root>/Variant Sink1' */
extern int16_T spd_fed;                /* '<Root>/SpeedConvert' */
extern int16_T id_ref;                 /* '<S4>/Merge' */
extern int16_T iq_ref;                 /* '<S4>/Merge1' */
extern int16_T w_dot;                  /* '<S122>/Divide' */
extern uint8_T stm_state;              /* '<S4>/Chart1' */
extern uint8_T ct_ctrl_mode;           /* '<S4>/Chart1' */
extern int32_T pos_ref_int;            /* '<S178>/Switch' */
extern int32_T i_alpha_dot;            /* '<S123>/Saturation' */
extern int32_T i_beta_dot;             /* '<S123>/Saturation1' */
extern int16_T theta_e;                /* '<S6>/Switch1' */
extern int16_T i_alpha;                /* '<S9>/Clark' */
extern int16_T i_beta;                 /* '<S9>/Clark' */
extern int16_T u_alpha;                /* '<S9>/AntiPark' */
extern int16_T u_beta;                 /* '<S9>/AntiPark' */
extern int32_T e_alpha_dot;            /* '<S123>/Saturation2' */
extern int32_T e_beta_dot;             /* '<S123>/Saturation3' */
extern int16_T ia;                     /* '<S9>/Data Type Conversion' */
extern int16_T ib;                     /* '<S9>/Data Type Conversion1' */
extern int16_T id;                     /* '<S9>/Park' */
extern int16_T id_err;                 /* '<S9>/Sum3' */
extern int16_T iq;                     /* '<S9>/Park' */
extern int16_T iq_err;                 /* '<S9>/Sum1' */
extern int16_T ud;                     /* '<S9>/sfun_CircleLimit' */
extern int16_T uq;                     /* '<S9>/sfun_CircleLimit' */

/* Model entry point functions */
extern void mmcs_s2f_initialize(void);
extern void mmcs_s2f_step0(void);
extern void mmcs_s2f_step1(void);
extern void mmcs_s2f_terminate(void);

/* Real-time Model object */
extern RT_MODEL_mmcs_s2f_T *const mmcs_s2f_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S15>/Scope' : Unused code path elimination
 * Block '<S9>/Scope1' : Unused code path elimination
 * Block '<S9>/Scope2' : Unused code path elimination
 * Block '<S9>/Scope3' : Unused code path elimination
 * Block '<S9>/Scope4' : Unused code path elimination
 * Block '<S9>/Scope5' : Unused code path elimination
 * Block '<S9>/Scope6' : Unused code path elimination
 * Block '<S9>/Scope7' : Unused code path elimination
 * Block '<S9>/Scope8' : Unused code path elimination
 * Block '<S9>/Scope9' : Unused code path elimination
 * Block '<S123>/Scope' : Unused code path elimination
 * Block '<S123>/Scope1' : Unused code path elimination
 * Block '<S123>/Scope2' : Unused code path elimination
 * Block '<S124>/Scope1' : Unused code path elimination
 * Block '<S124>/Scope2' : Unused code path elimination
 * Block '<S124>/Scope3' : Unused code path elimination
 * Block '<S124>/Scope6' : Unused code path elimination
 * Block '<Root>/Scope37' : Unused code path elimination
 * Block '<S189>/Scope' : Unused code path elimination
 * Block '<S180>/Scope' : Unused code path elimination
 * Block '<S250>/Scope' : Unused code path elimination
 * Block '<Root>/Scope23' : Unused code path elimination
 * Block '<S314>/Scope' : Unused code path elimination
 * Block '<S315>/Scope' : Unused code path elimination
 * Block '<Root>/Scope3' : Unused code path elimination
 * Block '<Root>/Scope4' : Unused code path elimination
 * Block '<Root>/Scope13' : Unused code path elimination
 * Block '<Root>/Scope20' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<Root>/Scope10' : Unused code path elimination
 * Block '<Root>/Scope11' : Unused code path elimination
 * Block '<Root>/Scope12' : Unused code path elimination
 * Block '<Root>/Scope14' : Unused code path elimination
 * Block '<Root>/Scope15' : Unused code path elimination
 * Block '<Root>/Scope16' : Unused code path elimination
 * Block '<Root>/Scope17' : Unused code path elimination
 * Block '<Root>/Scope18' : Unused code path elimination
 * Block '<Root>/Scope19' : Unused code path elimination
 * Block '<Root>/Scope2' : Unused code path elimination
 * Block '<Root>/Scope21' : Unused code path elimination
 * Block '<Root>/Scope22' : Unused code path elimination
 * Block '<Root>/Scope24' : Unused code path elimination
 * Block '<Root>/Scope25' : Unused code path elimination
 * Block '<Root>/Scope26' : Unused code path elimination
 * Block '<Root>/Scope27' : Unused code path elimination
 * Block '<Root>/Scope28' : Unused code path elimination
 * Block '<Root>/Scope29' : Unused code path elimination
 * Block '<Root>/Scope30' : Unused code path elimination
 * Block '<Root>/Scope31' : Unused code path elimination
 * Block '<Root>/Scope32' : Unused code path elimination
 * Block '<Root>/Scope33' : Unused code path elimination
 * Block '<Root>/Scope34' : Unused code path elimination
 * Block '<Root>/Scope35' : Unused code path elimination
 * Block '<Root>/Scope36' : Unused code path elimination
 * Block '<Root>/Scope5' : Unused code path elimination
 * Block '<Root>/Scope6' : Unused code path elimination
 * Block '<Root>/Scope7' : Unused code path elimination
 * Block '<Root>/Scope8' : Unused code path elimination
 * Block '<Root>/Scope9' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'mmcs_s2f'
 * '<S1>'   : 'mmcs_s2f/AngleConvert'
 * '<S2>'   : 'mmcs_s2f/CurrentConvert'
 * '<S3>'   : 'mmcs_s2f/HFTask'
 * '<S4>'   : 'mmcs_s2f/MFTask'
 * '<S5>'   : 'mmcs_s2f/SpeedConvert'
 * '<S6>'   : 'mmcs_s2f/HFTask/AngleCalc'
 * '<S7>'   : 'mmcs_s2f/HFTask/Compare To Constant1'
 * '<S8>'   : 'mmcs_s2f/HFTask/Compare To Constant3'
 * '<S9>'   : 'mmcs_s2f/HFTask/CurrentLoop'
 * '<S10>'  : 'mmcs_s2f/HFTask/ObserverPLL'
 * '<S11>'  : 'mmcs_s2f/HFTask/AngleCalc/VssCalcAngle'
 * '<S12>'  : 'mmcs_s2f/HFTask/AngleCalc/VssCalcAngle/Compare To Constant1'
 * '<S13>'  : 'mmcs_s2f/HFTask/AngleCalc/VssCalcAngle/Compare To Constant2'
 * '<S14>'  : 'mmcs_s2f/HFTask/AngleCalc/VssCalcAngle/Compare To Constant3'
 * '<S15>'  : 'mmcs_s2f/HFTask/AngleCalc/VssCalcAngle/EncCalcAngle'
 * '<S16>'  : 'mmcs_s2f/HFTask/AngleCalc/VssCalcAngle/VssEncoder'
 * '<S17>'  : 'mmcs_s2f/HFTask/CurrentLoop/AntiPark'
 * '<S18>'  : 'mmcs_s2f/HFTask/CurrentLoop/Clark'
 * '<S19>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler'
 * '<S20>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler'
 * '<S21>'  : 'mmcs_s2f/HFTask/CurrentLoop/Park'
 * '<S22>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Anti-windup'
 * '<S23>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/D Gain'
 * '<S24>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Filter'
 * '<S25>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Filter ICs'
 * '<S26>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/I Gain'
 * '<S27>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Ideal P Gain'
 * '<S28>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Ideal P Gain Fdbk'
 * '<S29>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Integrator'
 * '<S30>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Integrator ICs'
 * '<S31>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/N Copy'
 * '<S32>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/N Gain'
 * '<S33>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/P Copy'
 * '<S34>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Parallel P Gain'
 * '<S35>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Reset Signal'
 * '<S36>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Saturation'
 * '<S37>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Saturation Fdbk'
 * '<S38>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Sum'
 * '<S39>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Sum Fdbk'
 * '<S40>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Tracking Mode'
 * '<S41>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Tracking Mode Sum'
 * '<S42>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Tsamp - Integral'
 * '<S43>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Tsamp - Ngain'
 * '<S44>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/postSat Signal'
 * '<S45>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/preSat Signal'
 * '<S46>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Anti-windup/Disc. Clamping Parallel'
 * '<S47>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S48>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S49>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/D Gain/Disabled'
 * '<S50>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Filter/Disabled'
 * '<S51>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Filter ICs/Disabled'
 * '<S52>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/I Gain/Internal Parameters'
 * '<S53>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Ideal P Gain/Passthrough'
 * '<S54>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Ideal P Gain Fdbk/Disabled'
 * '<S55>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Integrator/Discrete'
 * '<S56>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Integrator ICs/Internal IC'
 * '<S57>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/N Copy/Disabled wSignal Specification'
 * '<S58>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/N Gain/Disabled'
 * '<S59>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/P Copy/Disabled'
 * '<S60>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Parallel P Gain/Internal Parameters'
 * '<S61>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Reset Signal/External Reset'
 * '<S62>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Saturation/Enabled'
 * '<S63>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Saturation Fdbk/Disabled'
 * '<S64>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Sum/Sum_PI'
 * '<S65>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Sum Fdbk/Disabled'
 * '<S66>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Tracking Mode/Disabled'
 * '<S67>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Tracking Mode Sum/Passthrough'
 * '<S68>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Tsamp - Integral/Passthrough'
 * '<S69>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/Tsamp - Ngain/Passthrough'
 * '<S70>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/postSat Signal/Forward_Path'
 * '<S71>'  : 'mmcs_s2f/HFTask/CurrentLoop/IdControler/preSat Signal/Forward_Path'
 * '<S72>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Anti-windup'
 * '<S73>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/D Gain'
 * '<S74>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Filter'
 * '<S75>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Filter ICs'
 * '<S76>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/I Gain'
 * '<S77>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Ideal P Gain'
 * '<S78>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Ideal P Gain Fdbk'
 * '<S79>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Integrator'
 * '<S80>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Integrator ICs'
 * '<S81>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/N Copy'
 * '<S82>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/N Gain'
 * '<S83>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/P Copy'
 * '<S84>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Parallel P Gain'
 * '<S85>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Reset Signal'
 * '<S86>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Saturation'
 * '<S87>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Saturation Fdbk'
 * '<S88>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Sum'
 * '<S89>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Sum Fdbk'
 * '<S90>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Tracking Mode'
 * '<S91>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Tracking Mode Sum'
 * '<S92>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Tsamp - Integral'
 * '<S93>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Tsamp - Ngain'
 * '<S94>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/postSat Signal'
 * '<S95>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/preSat Signal'
 * '<S96>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Anti-windup/Disc. Clamping Parallel'
 * '<S97>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S98>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S99>'  : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/D Gain/Disabled'
 * '<S100>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Filter/Disabled'
 * '<S101>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Filter ICs/Disabled'
 * '<S102>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/I Gain/Internal Parameters'
 * '<S103>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Ideal P Gain/Passthrough'
 * '<S104>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Ideal P Gain Fdbk/Disabled'
 * '<S105>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Integrator/Discrete'
 * '<S106>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Integrator ICs/Internal IC'
 * '<S107>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/N Copy/Disabled wSignal Specification'
 * '<S108>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/N Gain/Disabled'
 * '<S109>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/P Copy/Disabled'
 * '<S110>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Parallel P Gain/Internal Parameters'
 * '<S111>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Reset Signal/External Reset'
 * '<S112>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Saturation/Enabled'
 * '<S113>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Saturation Fdbk/Disabled'
 * '<S114>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Sum/Sum_PI'
 * '<S115>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Sum Fdbk/Disabled'
 * '<S116>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Tracking Mode/Disabled'
 * '<S117>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Tracking Mode Sum/Passthrough'
 * '<S118>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Tsamp - Integral/Passthrough'
 * '<S119>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/Tsamp - Ngain/Passthrough'
 * '<S120>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/postSat Signal/Forward_Path'
 * '<S121>' : 'mmcs_s2f/HFTask/CurrentLoop/IqControler/preSat Signal/Forward_Path'
 * '<S122>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem'
 * '<S123>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/Observer'
 * '<S124>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL'
 * '<S125>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller'
 * '<S126>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Anti-windup'
 * '<S127>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/D Gain'
 * '<S128>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Filter'
 * '<S129>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Filter ICs'
 * '<S130>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/I Gain'
 * '<S131>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Ideal P Gain'
 * '<S132>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Ideal P Gain Fdbk'
 * '<S133>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Integrator'
 * '<S134>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Integrator ICs'
 * '<S135>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/N Copy'
 * '<S136>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/N Gain'
 * '<S137>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/P Copy'
 * '<S138>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Parallel P Gain'
 * '<S139>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Reset Signal'
 * '<S140>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Saturation'
 * '<S141>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Saturation Fdbk'
 * '<S142>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Sum'
 * '<S143>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Sum Fdbk'
 * '<S144>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Tracking Mode'
 * '<S145>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Tracking Mode Sum'
 * '<S146>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Tsamp - Integral'
 * '<S147>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Tsamp - Ngain'
 * '<S148>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/postSat Signal'
 * '<S149>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/preSat Signal'
 * '<S150>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel'
 * '<S151>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S152>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S153>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/D Gain/Disabled'
 * '<S154>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Filter/Disabled'
 * '<S155>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Filter ICs/Disabled'
 * '<S156>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/I Gain/Internal Parameters'
 * '<S157>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Ideal P Gain/Passthrough'
 * '<S158>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S159>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Integrator/Discrete'
 * '<S160>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Integrator ICs/Internal IC'
 * '<S161>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/N Copy/Disabled wSignal Specification'
 * '<S162>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/N Gain/Disabled'
 * '<S163>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/P Copy/Disabled'
 * '<S164>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Parallel P Gain/Internal Parameters'
 * '<S165>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Reset Signal/Disabled'
 * '<S166>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Saturation/Enabled'
 * '<S167>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Saturation Fdbk/Disabled'
 * '<S168>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Sum/Sum_PI'
 * '<S169>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Sum Fdbk/Disabled'
 * '<S170>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Tracking Mode/Disabled'
 * '<S171>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Tracking Mode Sum/Passthrough'
 * '<S172>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Tsamp - Integral/Passthrough'
 * '<S173>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/Tsamp - Ngain/Passthrough'
 * '<S174>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/postSat Signal/Forward_Path'
 * '<S175>' : 'mmcs_s2f/HFTask/ObserverPLL/Resettable Subsystem/PLL/Discrete PID Controller/preSat Signal/Forward_Path'
 * '<S176>' : 'mmcs_s2f/MFTask/Chart1'
 * '<S177>' : 'mmcs_s2f/MFTask/IsTransition'
 * '<S178>' : 'mmcs_s2f/MFTask/PosCtrl'
 * '<S179>' : 'mmcs_s2f/MFTask/PosCtrlInit'
 * '<S180>' : 'mmcs_s2f/MFTask/PosCtrlPlan'
 * '<S181>' : 'mmcs_s2f/MFTask/SpdCtrl'
 * '<S182>' : 'mmcs_s2f/MFTask/SysCtrlModeUpdDet'
 * '<S183>' : 'mmcs_s2f/MFTask/TorqCtrl'
 * '<S184>' : 'mmcs_s2f/MFTask/IsTransition/Compare To Constant'
 * '<S185>' : 'mmcs_s2f/MFTask/IsTransition/If Action Subsystem'
 * '<S186>' : 'mmcs_s2f/MFTask/PosCtrl/Compare To Constant'
 * '<S187>' : 'mmcs_s2f/MFTask/PosCtrl/Compare To Constant1'
 * '<S188>' : 'mmcs_s2f/MFTask/PosCtrl/If Action Subsystem'
 * '<S189>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler'
 * '<S190>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler'
 * '<S191>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Anti-windup'
 * '<S192>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/D Gain'
 * '<S193>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Filter'
 * '<S194>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Filter ICs'
 * '<S195>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/I Gain'
 * '<S196>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Ideal P Gain'
 * '<S197>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Ideal P Gain Fdbk'
 * '<S198>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Integrator'
 * '<S199>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Integrator ICs'
 * '<S200>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/N Copy'
 * '<S201>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/N Gain'
 * '<S202>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/P Copy'
 * '<S203>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Parallel P Gain'
 * '<S204>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Reset Signal'
 * '<S205>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Saturation'
 * '<S206>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Saturation Fdbk'
 * '<S207>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Sum'
 * '<S208>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Sum Fdbk'
 * '<S209>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Tracking Mode'
 * '<S210>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Tracking Mode Sum'
 * '<S211>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Tsamp - Integral'
 * '<S212>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Tsamp - Ngain'
 * '<S213>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/postSat Signal'
 * '<S214>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/preSat Signal'
 * '<S215>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Anti-windup/Disc. Clamping Parallel'
 * '<S216>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S217>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S218>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/D Gain/Disabled'
 * '<S219>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Filter/Disabled'
 * '<S220>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Filter ICs/Disabled'
 * '<S221>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/I Gain/Internal Parameters'
 * '<S222>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Ideal P Gain/Passthrough'
 * '<S223>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Ideal P Gain Fdbk/Disabled'
 * '<S224>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Integrator/Discrete'
 * '<S225>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Integrator ICs/Internal IC'
 * '<S226>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/N Copy/Disabled wSignal Specification'
 * '<S227>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/N Gain/Disabled'
 * '<S228>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/P Copy/Disabled'
 * '<S229>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Parallel P Gain/Internal Parameters'
 * '<S230>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Reset Signal/External Reset'
 * '<S231>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Saturation/Enabled'
 * '<S232>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Saturation Fdbk/Disabled'
 * '<S233>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Sum/Sum_PI'
 * '<S234>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Sum Fdbk/Disabled'
 * '<S235>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Tracking Mode/Disabled'
 * '<S236>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Tracking Mode Sum/Passthrough'
 * '<S237>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Tsamp - Integral/Passthrough'
 * '<S238>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/Tsamp - Ngain/Passthrough'
 * '<S239>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/postSat Signal/Forward_Path'
 * '<S240>' : 'mmcs_s2f/MFTask/PosCtrl/PosControler/PosControler/preSat Signal/Forward_Path'
 * '<S241>' : 'mmcs_s2f/MFTask/PosCtrlInit/Compare To Constant1'
 * '<S242>' : 'mmcs_s2f/MFTask/PosCtrlInit/PosCtrlInit'
 * '<S243>' : 'mmcs_s2f/MFTask/PosCtrlPlan/Compare To Constant3'
 * '<S244>' : 'mmcs_s2f/MFTask/PosCtrlPlan/PosCtrlPlan'
 * '<S245>' : 'mmcs_s2f/MFTask/PosCtrlPlan/PosCtrlPlan/UpdatePosCtrl'
 * '<S246>' : 'mmcs_s2f/MFTask/SpdCtrl/Compare To Constant'
 * '<S247>' : 'mmcs_s2f/MFTask/SpdCtrl/Compare To Constant1'
 * '<S248>' : 'mmcs_s2f/MFTask/SpdCtrl/Compare To Constant2'
 * '<S249>' : 'mmcs_s2f/MFTask/SpdCtrl/Compare To Constant4'
 * '<S250>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler'
 * '<S251>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler'
 * '<S252>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Anti-windup'
 * '<S253>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/D Gain'
 * '<S254>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Filter'
 * '<S255>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Filter ICs'
 * '<S256>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/I Gain'
 * '<S257>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Ideal P Gain'
 * '<S258>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Ideal P Gain Fdbk'
 * '<S259>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Integrator'
 * '<S260>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Integrator ICs'
 * '<S261>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/N Copy'
 * '<S262>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/N Gain'
 * '<S263>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/P Copy'
 * '<S264>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Parallel P Gain'
 * '<S265>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Reset Signal'
 * '<S266>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Saturation'
 * '<S267>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Saturation Fdbk'
 * '<S268>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Sum'
 * '<S269>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Sum Fdbk'
 * '<S270>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Tracking Mode'
 * '<S271>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Tracking Mode Sum'
 * '<S272>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Tsamp - Integral'
 * '<S273>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Tsamp - Ngain'
 * '<S274>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/postSat Signal'
 * '<S275>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/preSat Signal'
 * '<S276>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Anti-windup/Disc. Clamping Parallel'
 * '<S277>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Anti-windup/Disc. Clamping Parallel/Dead Zone'
 * '<S278>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Anti-windup/Disc. Clamping Parallel/Dead Zone/Enabled'
 * '<S279>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/D Gain/Disabled'
 * '<S280>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Filter/Disabled'
 * '<S281>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Filter ICs/Disabled'
 * '<S282>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/I Gain/Internal Parameters'
 * '<S283>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Ideal P Gain/Passthrough'
 * '<S284>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Ideal P Gain Fdbk/Disabled'
 * '<S285>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Integrator/Discrete'
 * '<S286>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Integrator ICs/Internal IC'
 * '<S287>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/N Copy/Disabled wSignal Specification'
 * '<S288>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/N Gain/Disabled'
 * '<S289>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/P Copy/Disabled'
 * '<S290>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Parallel P Gain/Internal Parameters'
 * '<S291>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Reset Signal/External Reset'
 * '<S292>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Saturation/Enabled'
 * '<S293>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Saturation Fdbk/Disabled'
 * '<S294>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Sum/Sum_PI'
 * '<S295>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Sum Fdbk/Disabled'
 * '<S296>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Tracking Mode/Disabled'
 * '<S297>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Tracking Mode Sum/Passthrough'
 * '<S298>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Tsamp - Integral/Passthrough'
 * '<S299>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/Tsamp - Ngain/Passthrough'
 * '<S300>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/postSat Signal/Forward_Path'
 * '<S301>' : 'mmcs_s2f/MFTask/SpdCtrl/SpdControler/SpdControler/preSat Signal/Forward_Path'
 * '<S302>' : 'mmcs_s2f/MFTask/SysCtrlModeUpdDet/Compare To Constant'
 * '<S303>' : 'mmcs_s2f/MFTask/SysCtrlModeUpdDet/Compare To Constant1'
 * '<S304>' : 'mmcs_s2f/MFTask/SysCtrlModeUpdDet/Compare To Constant4'
 * '<S305>' : 'mmcs_s2f/MFTask/SysCtrlModeUpdDet/Compare To Constant5'
 * '<S306>' : 'mmcs_s2f/MFTask/SysCtrlModeUpdDet/Compare To Constant6'
 * '<S307>' : 'mmcs_s2f/MFTask/SysCtrlModeUpdDet/If Action Subsystem'
 * '<S308>' : 'mmcs_s2f/MFTask/TorqCtrl/AlignRamp'
 * '<S309>' : 'mmcs_s2f/MFTask/TorqCtrl/AligntAction'
 * '<S310>' : 'mmcs_s2f/MFTask/TorqCtrl/Compare To Constant'
 * '<S311>' : 'mmcs_s2f/MFTask/TorqCtrl/DefAction'
 * '<S312>' : 'mmcs_s2f/MFTask/TorqCtrl/IFRamp'
 * '<S313>' : 'mmcs_s2f/MFTask/TorqCtrl/IFStart'
 * '<S314>' : 'mmcs_s2f/MFTask/TorqCtrl/AlignRamp/IfControler'
 * '<S315>' : 'mmcs_s2f/MFTask/TorqCtrl/IFRamp/IfControler'
 * '<S316>' : 'mmcs_s2f/SpeedConvert/GetAvgVal'
 * '<S317>' : 'mmcs_s2f/SpeedConvert/SpdConvSto'
 */
#endif                                 /* RTW_HEADER_mmcs_s2f_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
