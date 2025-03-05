/*
 * File: AntiPark.c
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

#include "AntiPark.h"

/* Include model header file for global data */
#include "mmcs_s2f.h"
#include "mmcs_s2f_private.h"

/* Output and update for atomic system: '<S9>/AntiPark' */
void mmcs_s2f_AntiPark(int16_T rtu_d, int16_T rtu_q, int16_T rtu_sin, int16_T
  rtu_cos, int16_T *rty_u, int16_T *rty_u_p, B_AntiPark_mmcs_s2f_T *localB)
{
  int32_T u0;

  /* Product: '<S17>/Product' */
  localB->Product = rtu_d * rtu_cos;

  /* Product: '<S17>/Product1' */
  localB->Product1 = rtu_q * rtu_sin;

  /* Sum: '<S17>/Add' */
  localB->Add = localB->Product - localB->Product1;

  /* Product: '<S17>/Product2' */
  localB->Product2 = rtu_d * rtu_sin;

  /* Product: '<S17>/Product3' */
  localB->Product3 = rtu_q * rtu_cos;

  /* Sum: '<S17>/Add1' */
  localB->Add1 = localB->Product2 + localB->Product3;

  /* ArithShift: '<S17>/Shift Arithmetic' incorporates:
   *  Constant: '<S17>/Constant'
   *  Sum: '<S17>/Add'
   */
  localB->ShiftArithmetic = localB->Add >> 15U;

  /* Saturate: '<S17>/Saturation' */
  u0 = localB->ShiftArithmetic;
  if (u0 > 32767) {
    /* Saturate: '<S17>/Saturation' */
    localB->Saturation = 32767;
  } else if (u0 < -32768) {
    /* Saturate: '<S17>/Saturation' */
    localB->Saturation = -32768;
  } else {
    /* Saturate: '<S17>/Saturation' */
    localB->Saturation = u0;
  }

  /* End of Saturate: '<S17>/Saturation' */

  /* DataTypeConversion: '<S17>/Data Type Conversion' */
  *rty_u = (int16_T)localB->Saturation;

  /* ArithShift: '<S17>/Shift Arithmetic1' incorporates:
   *  Constant: '<S17>/Constant1'
   *  Sum: '<S17>/Add1'
   */
  localB->ShiftArithmetic1 = localB->Add1 >> 15U;

  /* Saturate: '<S17>/Saturation1' */
  u0 = localB->ShiftArithmetic1;
  if (u0 > 32767) {
    /* Saturate: '<S17>/Saturation1' */
    localB->Saturation1 = 32767;
  } else if (u0 < -32768) {
    /* Saturate: '<S17>/Saturation1' */
    localB->Saturation1 = -32768;
  } else {
    /* Saturate: '<S17>/Saturation1' */
    localB->Saturation1 = u0;
  }

  /* End of Saturate: '<S17>/Saturation1' */

  /* DataTypeConversion: '<S17>/Data Type Conversion1' */
  *rty_u_p = (int16_T)localB->Saturation1;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
