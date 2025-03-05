/*
 * File: Clark.h
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

#ifndef RTW_HEADER_Clark_h_
#define RTW_HEADER_Clark_h_
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

/* Block signals for system '<S9>/Clark' */
typedef struct {
  int32_T Add;                         /* '<S18>/Add' */
  int32_T Gain4;                       /* '<S18>/Gain4' */
  int32_T ShiftArithmetic;             /* '<S18>/Shift Arithmetic' */
  int32_T Saturation;                  /* '<S18>/Saturation' */
} B_Clark_mmcs_s2f_T;

/* Block states (default storage) for system '<S9>/Clark' */
typedef struct {
  int32_T Add_DWORK1;                  /* '<S18>/Add' */
} DW_Clark_mmcs_s2f_T;

extern void mmcs_s2f_Clark(int16_T rtu_ia, int16_T rtu_ib, int16_T *rty_i_alpha,
  int16_T *rty_i_beta, B_Clark_mmcs_s2f_T *localB);

#endif                                 /* RTW_HEADER_Clark_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
