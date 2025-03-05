/*
 * File: ObserverPLL.h
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

#ifndef RTW_HEADER_ObserverPLL_h_
#define RTW_HEADER_ObserverPLL_h_
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

/* Block signals for system '<S3>/ObserverPLL' */
typedef struct {
  int32_T ProportionalGain;            /* '<S164>/Proportional Gain' */
  int32_T Integrator;                  /* '<S159>/Integrator' */
  int32_T IntegralGain;                /* '<S156>/Integral Gain' */
  int32_T Switch;                      /* '<S150>/Switch' */
  int32_T Constant3;                   /* '<S124>/Constant3' */
  int32_T e_dot;                       /* '<S123>/Unit Delay1' */
  int32_T i_dot;                       /* '<S123>/Unit Delay' */
  int32_T i_dotF1;                     /* '<S123>/Divide2' */
  int32_T i_dotF1i;                    /* '<S123>/Subtract1' */
  int32_T Gain9;                       /* '<S123>/Gain9' */
  int32_T e_dot_i;                     /* '<S123>/Unit Delay3' */
  int32_T Divide4;                     /* '<S123>/Divide4' */
  int32_T Divide3;                     /* '<S123>/Divide3' */
  int32_T Divide6;                     /* '<S123>/Divide6' */
  int32_T Add2;                        /* '<S123>/Add2' */
  int32_T Product;                     /* '<S124>/Product' */
  int32_T ShiftArithmetic;             /* '<S124>/Shift Arithmetic' */
  int32_T i_dot_h;                     /* '<S123>/Unit Delay2' */
  int32_T i_dotF1_i;                   /* '<S123>/Divide5' */
  int32_T i_dotF1i_b;                  /* '<S123>/Subtract3' */
  int32_T Gain10;                      /* '<S123>/Gain10' */
  int32_T Divide1;                     /* '<S123>/Divide1' */
  int32_T Divide8;                     /* '<S123>/Divide8' */
  int32_T Divide7;                     /* '<S123>/Divide7' */
  int32_T Add3;                        /* '<S123>/Add3' */
  int32_T Product1;                    /* '<S124>/Product1' */
  int32_T ShiftArithmetic1;            /* '<S124>/Shift Arithmetic1' */
  int32_T theattheat_dot;              /* '<S124>/Sum' */
  int32_T Switch_e;                    /* '<S124>/Switch' */
  int32_T Sum;                         /* '<S168>/Sum' */
  int32_T Saturation;                  /* '<S166>/Saturation' */
  int32_T Product2;                    /* '<S124>/Product2' */
  int32_T Gain1;                       /* '<S123>/Gain1' */
  int32_T Subtract;                    /* '<S123>/Subtract' */
  int32_T Gain4;                       /* '<S123>/Gain4' */
  int32_T Gain3;                       /* '<S123>/Gain3' */
  int32_T Gain2;                       /* '<S123>/Gain2' */
  int32_T Add;                         /* '<S123>/Add' */
  int32_T Gain5;                       /* '<S123>/Gain5' */
  int32_T Subtract2;                   /* '<S123>/Subtract2' */
  int32_T Gain8;                       /* '<S123>/Gain8' */
  int32_T Gain7;                       /* '<S123>/Gain7' */
  int32_T Gain6;                       /* '<S123>/Gain6' */
  int32_T Add1;                        /* '<S123>/Add1' */
  int32_T DiscreteTimeIntegrator;      /* '<S124>/Discrete-Time Integrator' */
  int32_T MathFunction;                /* '<S124>/Math Function' */
  int32_T ZeroGain;                    /* '<S150>/ZeroGain' */
  int32_T DeadZone;                    /* '<S152>/DeadZone' */
  int32_T SignPreSat;                  /* '<S150>/SignPreSat' */
  int32_T SignPreIntegrator;           /* '<S150>/SignPreIntegrator' */
  int32_T Gain;                        /* '<S124>/Gain' */
  int16_T i;                           /* '<S123>/Unit Delay6' */
  int16_T UnitDelay8;                  /* '<S122>/Unit Delay8' */
  int16_T Divide1_k;                   /* '<S124>/Divide1' */
  int16_T UnitDelay8_m;                /* '<S124>/Unit Delay8' */
  int16_T cos_m;                       /* '<S124>/sfun_EmCos' */
  int16_T i_a;                         /* '<S123>/Unit Delay7' */
  int16_T Divide2;                     /* '<S124>/Divide2' */
  int16_T sin_a;                       /* '<S124>/sfun_EmSin' */
  int16_T dpp;                         /* '<S124>/Data Type Conversion1' */
  int16_T we_dot;                      /* '<S124>/Divide3' */
  int16_T u;                           /* '<S123>/Unit Delay4' */
  int16_T u_c;                         /* '<S123>/Unit Delay5' */
  int8_T DataTypeConv1;                /* '<S150>/DataTypeConv1' */
  int8_T DataTypeConv2;                /* '<S150>/DataTypeConv2' */
  boolean_T NotEqual;                  /* '<S150>/NotEqual' */
  boolean_T Equal1;                    /* '<S150>/Equal1' */
  boolean_T AND3;                      /* '<S150>/AND3' */
} B_ObserverPLL_mmcs_s2f_T;

/* Block states (default storage) for system '<S3>/ObserverPLL' */
typedef struct {
  int32_T UnitDelay1_DSTATE;           /* '<S123>/Unit Delay1' */
  int32_T UnitDelay_DSTATE;            /* '<S123>/Unit Delay' */
  int32_T UnitDelay3_DSTATE;           /* '<S123>/Unit Delay3' */
  int32_T UnitDelay2_DSTATE;           /* '<S123>/Unit Delay2' */
  int32_T DiscreteTimeIntegrator_DSTATE;/* '<S124>/Discrete-Time Integrator' */
  int32_T Integrator_DSTATE;           /* '<S159>/Integrator' */
  int32_T Subtract1_DWORK1;            /* '<S123>/Subtract1' */
  int32_T Sum_DWORK1;                  /* '<S168>/Sum' */
  int16_T UnitDelay6_DSTATE;           /* '<S123>/Unit Delay6' */
  int16_T UnitDelay8_DSTATE;           /* '<S122>/Unit Delay8' */
  int16_T UnitDelay8_DSTATE_g;         /* '<S124>/Unit Delay8' */
  int16_T UnitDelay7_DSTATE;           /* '<S123>/Unit Delay7' */
  int16_T UnitDelay4_DSTATE;           /* '<S123>/Unit Delay4' */
  int16_T UnitDelay5_DSTATE;           /* '<S123>/Unit Delay5' */
  int8_T DiscreteTimeIntegrator_PrevRese;/* '<S124>/Discrete-Time Integrator' */
} DW_ObserverPLL_mmcs_s2f_T;

/* Zero-crossing (trigger) state for system '<S3>/ObserverPLL' */
typedef struct {
  ZCSigState ResettableSubsystem_Reset_ZCE;/* '<S10>/Resettable Subsystem' */
} ZCE_ObserverPLL_mmcs_s2f_T;

extern void mmcs_s2f_ObserverPLL_Init(int16_T *rty_w_dot,
  DW_ObserverPLL_mmcs_s2f_T *localDW);
extern void mmcs_s2f_ObserverPLL_Update(int16_T rtu_u_alpha_beta, int16_T
  rtu_u_alpha_beta_g, int16_T rtu_i_alpha_beta, int16_T rtu_i_alpha_beta_f,
  uint8_T rtu_reset, int16_T *rty_theta_e_dot, int32_T *rty_i_dot_next, int32_T *
  rty_i_dot_next_a, B_ObserverPLL_mmcs_s2f_T *localB, DW_ObserverPLL_mmcs_s2f_T *
  localDW);
extern void mmcs_s2f_ObserverPLL(uint8_T rtu_reset_all, uint8_T rtu_reset,
  int16_T rtu_spd_ref, int16_T *rty_theta_e_dot, int16_T *rty_w_dot, int32_T
  *rty_i_dot_next, int32_T *rty_i_dot_next_a, B_ObserverPLL_mmcs_s2f_T *localB,
  DW_ObserverPLL_mmcs_s2f_T *localDW, ZCE_ObserverPLL_mmcs_s2f_T *localZCE);

#endif                                 /* RTW_HEADER_ObserverPLL_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
