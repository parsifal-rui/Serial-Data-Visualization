/*
 * File: Park.h
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

#ifndef RTW_HEADER_Park_h_
#define RTW_HEADER_Park_h_
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

/* Block signals for system '<S9>/Park' */
typedef struct {
  int32_T Product;                     /* '<S21>/Product' */
  int32_T Product1;                    /* '<S21>/Product1' */
  int32_T Add;                         /* '<S21>/Add' */
  int32_T Product2;                    /* '<S21>/Product2' */
  int32_T Product3;                    /* '<S21>/Product3' */
  int32_T Add1;                        /* '<S21>/Add1' */
  int32_T ShiftArithmetic;             /* '<S21>/Shift Arithmetic' */
  int32_T Saturation;                  /* '<S21>/Saturation' */
  int32_T ShiftArithmetic1;            /* '<S21>/Shift Arithmetic1' */
  int32_T Saturation1;                 /* '<S21>/Saturation1' */
} B_Park_mmcs_s2f_T;

/* Block states (default storage) for system '<S9>/Park' */
typedef struct {
  int32_T Add1_DWORK1;                 /* '<S21>/Add1' */
} DW_Park_mmcs_s2f_T;

extern void mmcs_s2f_Park(int16_T rtu_u, int16_T rtu_u_b, int16_T rtu_sin,
  int16_T rtu_cos, int16_T *rty_d, int16_T *rty_q, B_Park_mmcs_s2f_T *localB);

#endif                                 /* RTW_HEADER_Park_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
