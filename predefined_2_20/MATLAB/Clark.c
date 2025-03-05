/*
 * File: Clark.c
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

#include "Clark.h"

/* Include model header file for global data */
#include "mmcs_s2f.h"
#include "mmcs_s2f_private.h"

/* Output and update for atomic system: '<S9>/Clark' */
void mmcs_s2f_Clark(int16_T rtu_ia, int16_T rtu_ib, int16_T *rty_i_alpha,
                    int16_T *rty_i_beta, B_Clark_mmcs_s2f_T *localB)
{
  int32_T u0;
  uint32_T tmp;

  /* Inport: '<S18>/ia' */
  *rty_i_alpha = rtu_ia;

  /* Sum: '<S18>/Add' */
  localB->Add = (*rty_i_alpha + rtu_ib) + rtu_ib;

  /* Gain: '<S18>/Gain4' */
  tmp = DIVSQRT_3;
  if (tmp > 32767U) {
    u0 = MAX_int32_T;
  } else {
    u0 = (int32_T)tmp << 16;
  }

  /* Gain: '<S18>/Gain4' */
  localB->Gain4 = mul_s32_loSR_zero(u0, localB->Add, 16U);

  /* ArithShift: '<S18>/Shift Arithmetic' incorporates:
   *  Constant: '<S18>/Constant'
   *  Gain: '<S18>/Gain4'
   */
  localB->ShiftArithmetic = localB->Gain4 >> 15U;

  /* Saturate: '<S18>/Saturation' */
  u0 = localB->ShiftArithmetic;
  if (u0 > 32767) {
    /* Saturate: '<S18>/Saturation' */
    localB->Saturation = 32767;
  } else if (u0 < -32768) {
    /* Saturate: '<S18>/Saturation' */
    localB->Saturation = -32768;
  } else {
    /* Saturate: '<S18>/Saturation' */
    localB->Saturation = u0;
  }

  /* End of Saturate: '<S18>/Saturation' */

  /* DataTypeConversion: '<S18>/Data Type Conversion' */
  *rty_i_beta = (int16_T)localB->Saturation;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
