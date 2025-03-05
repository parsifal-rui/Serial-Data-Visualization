/*
 * File: HFTask.h
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

#ifndef RTW_HEADER_HFTask_h_
#define RTW_HEADER_HFTask_h_
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
#include "CurrentLoop.h"
#include "ObserverPLL.h"

/* Block signals for system '<Root>/HFTask' */
typedef struct {
  int64m_T Product2;                   /* '<S15>/Product2' */
  int32_T DiscreteTimeIntegrator1;     /* '<S16>/Discrete-Time Integrator1' */
  int32_T Constant7;                   /* '<S16>/Constant7' */
  int32_T Product1;                    /* '<S16>/Product1' */
  int32_T Divide;                      /* '<S16>/Divide' */
  int32_T Add;                         /* '<S16>/Add' */
  int32_T MathFunction;                /* '<S16>/Math Function' */
  int32_T Divide_o;                    /* '<S15>/Divide' */
  int32_T Gain5;                       /* '<S15>/Gain5' */
  int16_T Switch;                      /* '<S6>/Switch' */
  int16_T Switch1;                     /* '<S11>/Switch1' */
  int16_T theta_m;                     /* '<S15>/Data Type Conversion1' */
  int16_T theta_e_c;                   /* '<S15>/Data Type Conversion2' */
  int16_T Switch2;                     /* '<S11>/Switch2' */
  uint8_T Compare;                     /* '<S8>/Compare' */
  uint8_T Compare_f;                   /* '<S7>/Compare' */
  uint8_T Compare_m;                   /* '<S13>/Compare' */
  uint8_T Compare_p;                   /* '<S12>/Compare' */
  uint8_T Compare_d;                   /* '<S14>/Compare' */
  boolean_T RelationalOperator1;       /* '<S6>/Relational Operator1' */
  boolean_T RelationalOperator2;       /* '<S6>/Relational Operator2' */
  boolean_T LogicalOperator;           /* '<S11>/Logical Operator' */
  B_ObserverPLL_mmcs_s2f_T ObserverPLL;/* '<S3>/ObserverPLL' */
  B_CurrentLoop_mmcs_s2f_T CurrentLoop;/* '<S3>/CurrentLoop' */
} B_HFTask_mmcs_s2f_T;

/* Block states (default storage) for system '<Root>/HFTask' */
typedef struct {
  int32_T DiscreteTimeIntegrator1_DSTATE;/* '<S16>/Discrete-Time Integrator1' */
  int32_T Add_DWORK1;                  /* '<S16>/Add' */
  int8_T If_ActiveSubsystem;           /* '<S3>/If' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S16>/Discrete-Time Integrator1' */
  DW_ObserverPLL_mmcs_s2f_T ObserverPLL;/* '<S3>/ObserverPLL' */
  DW_CurrentLoop_mmcs_s2f_T CurrentLoop;/* '<S3>/CurrentLoop' */
} DW_HFTask_mmcs_s2f_T;

/* Zero-crossing (trigger) state for system '<Root>/HFTask' */
typedef struct {
  ZCE_ObserverPLL_mmcs_s2f_T ObserverPLL;/* '<S3>/ObserverPLL' */
} ZCE_HFTask_mmcs_s2f_T;

extern void mmcs_s2f_HFTask_Init(int16_T *rty_w_dot, DW_HFTask_mmcs_s2f_T
  *localDW);
extern void mmcs_s2f_HFTask(uint8_T rtu_sys_ctrl_mode, uint8_T rtu_ct_ctrl_mode,
  uint8_T rtu_stm_state, const int16_T rtu_idq_ref[2], int16_T rtu_spd_ramp,
  const int16_T rtu_iab[2], int16_T rtu_theta_sensor, int16_T rtu_spd_ref,
  uint16_T *rty_ccrx, uint16_T *rty_ccrx_e, uint16_T *rty_ccrx_o, int16_T
  *rty_theta_e_dot, int16_T *rty_w_dot, B_HFTask_mmcs_s2f_T *localB,
  DW_HFTask_mmcs_s2f_T *localDW, ZCE_HFTask_mmcs_s2f_T *localZCE);

#endif                                 /* RTW_HEADER_HFTask_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
