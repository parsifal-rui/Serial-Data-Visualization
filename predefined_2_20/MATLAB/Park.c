/*
 * File: Park.c
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

#include "Park.h"

/* Include model header file for global data */
#include "mmcs_s2f.h"
#include "mmcs_s2f_private.h"

/* Output and update for atomic system: '<S9>/Park' */
void mmcs_s2f_Park(int16_T rtu_u, int16_T rtu_u_b, int16_T rtu_sin, int16_T
                   rtu_cos, int16_T *rty_d, int16_T *rty_q, B_Park_mmcs_s2f_T
                   *localB)
{
  int32_T u0;

  /* Product: '<S21>/Product' */
  localB->Product = rtu_u * rtu_cos;

  /* Product: '<S21>/Product1' */
  localB->Product1 = rtu_u_b * rtu_sin;

  /* Sum: '<S21>/Add' */
  localB->Add = localB->Product + localB->Product1;

  /* Product: '<S21>/Product2' */
  localB->Product2 = rtu_u * rtu_sin;

  /* Product: '<S21>/Product3' */
  localB->Product3 = rtu_u_b * rtu_cos;

  /* Sum: '<S21>/Add1' */
  localB->Add1 = localB->Product3 - localB->Product2;

  /* ArithShift: '<S21>/Shift Arithmetic' incorporates:
   *  Constant: '<S21>/Constant'
   *  Sum: '<S21>/Add'
   */
  localB->ShiftArithmetic = localB->Add >> 15U;

  /* Saturate: '<S21>/Saturation' */
  u0 = localB->ShiftArithmetic;
  if (u0 > 32767) {
    /* Saturate: '<S21>/Saturation' */
    localB->Saturation = 32767;
  } else if (u0 < -32768) {
    /* Saturate: '<S21>/Saturation' */
    localB->Saturation = -32768;
  } else {
    /* Saturate: '<S21>/Saturation' */
    localB->Saturation = u0;
  }

  /* End of Saturate: '<S21>/Saturation' */

  /* DataTypeConversion: '<S21>/Data Type Conversion' */
  *rty_d = (int16_T)localB->Saturation;

  /* ArithShift: '<S21>/Shift Arithmetic1' incorporates:
   *  Constant: '<S21>/Constant1'
   *  Sum: '<S21>/Add1'
   */
  localB->ShiftArithmetic1 = localB->Add1 >> 15U;

  /* Saturate: '<S21>/Saturation1' */
  u0 = localB->ShiftArithmetic1;
  if (u0 > 32767) {
    /* Saturate: '<S21>/Saturation1' */
    localB->Saturation1 = 32767;
  } else if (u0 < -32768) {
    /* Saturate: '<S21>/Saturation1' */
    localB->Saturation1 = -32768;
  } else {
    /* Saturate: '<S21>/Saturation1' */
    localB->Saturation1 = u0;
  }

  /* End of Saturate: '<S21>/Saturation1' */

  /* DataTypeConversion: '<S21>/Data Type Conversion1' */
  *rty_q = (int16_T)localB->Saturation1;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
