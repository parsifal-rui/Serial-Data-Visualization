/*
 * File: SpeedConvert.h
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

#ifndef RTW_HEADER_SpeedConvert_h_
#define RTW_HEADER_SpeedConvert_h_
#include <math.h>
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

/* Block signals for system '<Root>/SpeedConvert' */
typedef struct {
  int32_T Product;                     /* '<S317>/Product' */
  int16_T Switch;                      /* '<S5>/Switch' */
  int16_T Divide;                      /* '<S317>/Divide' */
  boolean_T RelationalOperator2;       /* '<S5>/Relational Operator2' */
} B_SpeedConvert_mmcs_s2f_T;

/* Block states (default storage) for system '<Root>/SpeedConvert' */
typedef struct {
  real_T index;                        /* '<S5>/GetAvgVal' */
  int16_T buff[16];                    /* '<S5>/GetAvgVal' */
} DW_SpeedConvert_mmcs_s2f_T;

extern void mmcs_s2f_SpeedConvert_Init(DW_SpeedConvert_mmcs_s2f_T *localDW);
extern void mmcs_s2f_SpeedConvert(uint8_T rtu_sys_ctrl_mode, int16_T
  rtu_spd_sensor, int16_T rtu_w_dot, int16_T *rty_spd_fed,
  B_SpeedConvert_mmcs_s2f_T *localB, DW_SpeedConvert_mmcs_s2f_T *localDW);

#endif                                 /* RTW_HEADER_SpeedConvert_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
