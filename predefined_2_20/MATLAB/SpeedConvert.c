/*
 * File: SpeedConvert.c
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

#include "SpeedConvert.h"

/* Include model header file for global data */
#include "mmcs_s2f.h"
#include "mmcs_s2f_private.h"

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* System initialize for atomic system: '<Root>/SpeedConvert' */
void mmcs_s2f_SpeedConvert_Init(DW_SpeedConvert_mmcs_s2f_T *localDW)
{
  /* SystemInitialize for MATLAB Function: '<S5>/GetAvgVal' */
  localDW->index = 1.0;
}

/* Output and update for atomic system: '<Root>/SpeedConvert' */
void mmcs_s2f_SpeedConvert(uint8_T rtu_sys_ctrl_mode, int16_T rtu_spd_sensor,
  int16_T rtu_w_dot, int16_T *rty_spd_fed, B_SpeedConvert_mmcs_s2f_T *localB,
  DW_SpeedConvert_mmcs_s2f_T *localDW)
{
  int32_T i;
  int32_T sum;

  /* RelationalOperator: '<S5>/Relational Operator2' incorporates:
   *  Constant: '<S5>/Constant2'
   */
  localB->RelationalOperator2 = (rtu_sys_ctrl_mode == ((uint8_T)STO_ST_CTRL));

  /* Switch: '<S5>/Switch' */
  if (localB->RelationalOperator2) {
    /* Product: '<S317>/Product' incorporates:
     *  Constant: '<S317>/Constant1'
     */
    localB->Product = rtu_w_dot * ((uint16_T)RAD2RPM_F_NUM);

    /* Product: '<S317>/Divide' incorporates:
     *  Constant: '<S317>/Constant3'
     */
    localB->Divide = div_s16s32(localB->Product, ((uint16_T)RAD2RPM_F_DEN));

    /* Switch: '<S5>/Switch' */
    localB->Switch = localB->Divide;
  } else {
    /* Switch: '<S5>/Switch' */
    localB->Switch = rtu_spd_sensor;
  }

  /* End of Switch: '<S5>/Switch' */

  /* MATLAB Function: '<S5>/GetAvgVal' */
  localDW->buff[(int32_T)localDW->index - 1] = localB->Switch;
  localDW->index++;
  if (localDW->index > 16.0) {
    localDW->index = 1.0;
  }

  sum = 0;
  for (i = 0; i < 16; i++) {
    int32_T q1;
    q1 = localDW->buff[i];
    if ((sum < 0) && (q1 < MIN_int32_T - sum)) {
      sum = MIN_int32_T;
    } else if ((sum > 0) && (q1 > MAX_int32_T - sum)) {
      sum = MAX_int32_T;
    } else {
      sum += q1;
    }
  }

  i = (int32_T)rt_roundd_snf((real_T)sum / 16.0);
  if (i > 32767) {
    i = 32767;
  } else if (i < -32768) {
    i = -32768;
  }

  *rty_spd_fed = (int16_T)i;

  /* End of MATLAB Function: '<S5>/GetAvgVal' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
