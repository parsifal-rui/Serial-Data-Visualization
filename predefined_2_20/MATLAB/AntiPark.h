/*
 * File: AntiPark.h
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

#ifndef RTW_HEADER_AntiPark_h_
#define RTW_HEADER_AntiPark_h_
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

/* Block signals for system '<S9>/AntiPark' */
typedef struct {
  int32_T Product;                     /* '<S17>/Product' */
  int32_T Product1;                    /* '<S17>/Product1' */
  int32_T Add;                         /* '<S17>/Add' */
  int32_T Product2;                    /* '<S17>/Product2' */
  int32_T Product3;                    /* '<S17>/Product3' */
  int32_T Add1;                        /* '<S17>/Add1' */
  int32_T ShiftArithmetic;             /* '<S17>/Shift Arithmetic' */
  int32_T Saturation;                  /* '<S17>/Saturation' */
  int32_T ShiftArithmetic1;            /* '<S17>/Shift Arithmetic1' */
  int32_T Saturation1;                 /* '<S17>/Saturation1' */
} B_AntiPark_mmcs_s2f_T;

extern void mmcs_s2f_AntiPark(int16_T rtu_d, int16_T rtu_q, int16_T rtu_sin,
  int16_T rtu_cos, int16_T *rty_u, int16_T *rty_u_p, B_AntiPark_mmcs_s2f_T
  *localB);

#endif                                 /* RTW_HEADER_AntiPark_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
