/*
 * File: CurrentLoop.h
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

#ifndef RTW_HEADER_CurrentLoop_h_
#define RTW_HEADER_CurrentLoop_h_
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
#include "AntiPark.h"
#include "Clark.h"
#include "Park.h"

/* Block signals for system '<S3>/CurrentLoop' */
typedef struct {
  int32_T ProportionalGain;            /* '<S60>/Proportional Gain' */
  int32_T Integrator;                  /* '<S55>/Integrator' */
  int32_T ProportionalGain_o;          /* '<S110>/Proportional Gain' */
  int32_T Integrator_f;                /* '<S105>/Integrator' */
  int32_T IntegralGain;                /* '<S52>/Integral Gain' */
  int32_T Switch;                      /* '<S46>/Switch' */
  int32_T IntegralGain_c;              /* '<S102>/Integral Gain' */
  int32_T Switch_g;                    /* '<S96>/Switch' */
  int32_T Sum;                         /* '<S64>/Sum' */
  int32_T Saturation;                  /* '<S62>/Saturation' */
  int32_T Sum_c;                       /* '<S114>/Sum' */
  int32_T Saturation_d;                /* '<S112>/Saturation' */
  int32_T ZeroGain;                    /* '<S46>/ZeroGain' */
  int32_T DeadZone;                    /* '<S48>/DeadZone' */
  int32_T SignPreSat;                  /* '<S46>/SignPreSat' */
  int32_T SignPreIntegrator;           /* '<S46>/SignPreIntegrator' */
  int32_T ZeroGain_a;                  /* '<S96>/ZeroGain' */
  int32_T DeadZone_g;                  /* '<S98>/DeadZone' */
  int32_T SignPreSat_m;                /* '<S96>/SignPreSat' */
  int32_T SignPreIntegrator_e;         /* '<S96>/SignPreIntegrator' */
  uint16_T sfun_EmSvpwm_o4;            /* '<S9>/sfun_EmSvpwm' */
  int16_T Saturation1[2];              /* '<S9>/Saturation1' */
  int16_T sin_o;                       /* '<S9>/sfun_EmSin' */
  int16_T cos_n;                       /* '<S9>/sfun_EmCos' */
  int16_T DataTypeConversion2;         /* '<S9>/Data Type Conversion2' */
  int16_T DataTypeConversion3;         /* '<S9>/Data Type Conversion3' */
  int16_T DataTypeConversion;          /* '<S21>/Data Type Conversion' */
  int16_T DataTypeConversion1;         /* '<S21>/Data Type Conversion1' */
  int16_T ia_a;                        /* '<S18>/ia' */
  int16_T DataTypeConversion_m;        /* '<S18>/Data Type Conversion' */
  int16_T DataTypeConversion_f;        /* '<S17>/Data Type Conversion' */
  int16_T DataTypeConversion1_f;       /* '<S17>/Data Type Conversion1' */
  int8_T DataTypeConv1;                /* '<S46>/DataTypeConv1' */
  int8_T DataTypeConv2;                /* '<S46>/DataTypeConv2' */
  int8_T DataTypeConv1_f;              /* '<S96>/DataTypeConv1' */
  int8_T DataTypeConv2_l;              /* '<S96>/DataTypeConv2' */
  boolean_T NotEqual;                  /* '<S46>/NotEqual' */
  boolean_T Equal1;                    /* '<S46>/Equal1' */
  boolean_T AND3;                      /* '<S46>/AND3' */
  boolean_T NotEqual_c;                /* '<S96>/NotEqual' */
  boolean_T Equal1_p;                  /* '<S96>/Equal1' */
  boolean_T AND3_i;                    /* '<S96>/AND3' */
  B_Park_mmcs_s2f_T Park;              /* '<S9>/Park' */
  B_Clark_mmcs_s2f_T Clark;            /* '<S9>/Clark' */
  B_AntiPark_mmcs_s2f_T AntiPark;      /* '<S9>/AntiPark' */
} B_CurrentLoop_mmcs_s2f_T;

/* Block states (default storage) for system '<S3>/CurrentLoop' */
typedef struct {
  int32_T Integrator_DSTATE;           /* '<S55>/Integrator' */
  int32_T Integrator_DSTATE_f;         /* '<S105>/Integrator' */
  int32_T Sum_DWORK1;                  /* '<S64>/Sum' */
  int8_T Integrator_PrevResetState;    /* '<S55>/Integrator' */
  int8_T Integrator_PrevResetState_i;  /* '<S105>/Integrator' */
  DW_Park_mmcs_s2f_T Park;             /* '<S9>/Park' */
  DW_Clark_mmcs_s2f_T Clark;           /* '<S9>/Clark' */
} DW_CurrentLoop_mmcs_s2f_T;

extern void mmcs_s2f_CurrentLoop_Init(DW_CurrentLoop_mmcs_s2f_T *localDW);
extern void mmcs_s2f_CurrentLoop(uint8_T rtu_reset, const int16_T rtu_idq_ref[2],
  int16_T rtu_theta_e, const int16_T rtu_iab[2], uint16_T *rty_ccrx, uint16_T
  *rty_ccrx_f, uint16_T *rty_ccrx_m, int16_T *rty_u_alhpa_beta, int16_T
  *rty_u_alhpa_beta_a, int16_T *rty_i_alhpa_beta, int16_T *rty_i_alhpa_beta_a,
  B_CurrentLoop_mmcs_s2f_T *localB, DW_CurrentLoop_mmcs_s2f_T *localDW);

#endif                                 /* RTW_HEADER_CurrentLoop_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
