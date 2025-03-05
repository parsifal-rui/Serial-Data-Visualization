/*
 * File: ObserverPLL.c
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

#include "ObserverPLL.h"

/* Include model header file for global data */
#include "mmcs_s2f.h"
#include "mmcs_s2f_private.h"

/* System initialize for action system: '<S3>/ObserverPLL' */
void mmcs_s2f_ObserverPLL_Init(int16_T *rty_w_dot, DW_ObserverPLL_mmcs_s2f_T
  *localDW)
{
  /* SystemInitialize for Resettable SubSystem: '<S10>/Resettable Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S124>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_PrevRese = 2;

  /* End of SystemInitialize for SubSystem: '<S10>/Resettable Subsystem' */

  /* SystemInitialize for Outport: '<S10>/w_dot' */
  *rty_w_dot = 0;
}

/* Outputs for action system: '<S3>/ObserverPLL' */
void mmcs_s2f_ObserverPLL(uint8_T rtu_reset_all, uint8_T rtu_reset, int16_T
  rtu_spd_ref, int16_T *rty_theta_e_dot, int16_T *rty_w_dot, int32_T
  *rty_i_dot_next, int32_T *rty_i_dot_next_a, B_ObserverPLL_mmcs_s2f_T *localB,
  DW_ObserverPLL_mmcs_s2f_T *localDW, ZCE_ObserverPLL_mmcs_s2f_T *localZCE)
{
  int32_T u0;
  int32_T u1;
  int32_T u2;
  boolean_T zcEvent;

  /* Outputs for Resettable SubSystem: '<S10>/Resettable Subsystem' incorporates:
   *  ResetPort: '<S122>/Reset'
   */
  zcEvent = ((rtu_reset_all > 0) && (localZCE->ResettableSubsystem_Reset_ZCE !=
              1));
  if (zcEvent) {
    /* InitializeConditions for UnitDelay: '<S123>/Unit Delay1' */
    localDW->UnitDelay1_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S123>/Unit Delay' */
    localDW->UnitDelay_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S123>/Unit Delay6' */
    localDW->UnitDelay6_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S123>/Unit Delay3' */
    localDW->UnitDelay3_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S122>/Unit Delay8' */
    localDW->UnitDelay8_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S124>/Unit Delay8' */
    localDW->UnitDelay8_DSTATE_g = 0;

    /* InitializeConditions for UnitDelay: '<S123>/Unit Delay2' */
    localDW->UnitDelay2_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S123>/Unit Delay7' */
    localDW->UnitDelay7_DSTATE = 0;

    /* InitializeConditions for DiscreteIntegrator: '<S159>/Integrator' */
    localDW->Integrator_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S123>/Unit Delay4' */
    localDW->UnitDelay4_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S123>/Unit Delay5' */
    localDW->UnitDelay5_DSTATE = 0;

    /* InitializeConditions for DiscreteIntegrator: '<S124>/Discrete-Time Integrator' */
    localDW->DiscreteTimeIntegrator_DSTATE = 0;
    localDW->DiscreteTimeIntegrator_PrevRese = 2;
  }

  localZCE->ResettableSubsystem_Reset_ZCE = (ZCSigState)(rtu_reset_all > 0);

  /* Constant: '<S124>/Constant3' */
  localB->Constant3 = ((uint16_T)PWM_FREQUENCY);

  /* UnitDelay: '<S123>/Unit Delay1' */
  localB->e_dot = localDW->UnitDelay1_DSTATE;

  /* UnitDelay: '<S123>/Unit Delay' */
  localB->i_dot = localDW->UnitDelay_DSTATE;

  /* Product: '<S123>/Divide2' incorporates:
   *  Constant: '<S123>/Constant3'
   */
  localB->i_dotF1 = div_s32(localB->i_dot, ((int16_T)STO_F1));

  /* UnitDelay: '<S123>/Unit Delay6' */
  localB->i = localDW->UnitDelay6_DSTATE;

  /* Sum: '<S123>/Subtract1' */
  localB->i_dotF1i = localB->i_dotF1 - localB->i;

  /* Gain: '<S123>/Gain9' */
  localB->Gain9 = STO_C4 * localB->i_dotF1i;

  /* UnitDelay: '<S123>/Unit Delay3' */
  localB->e_dot_i = localDW->UnitDelay3_DSTATE;

  /* Product: '<S123>/Divide4' incorporates:
   *  Constant: '<S123>/Constant5'
   */
  localB->Divide4 = div_s32(localB->e_dot_i, ((int16_T)STO_F2));

  /* Product: '<S123>/Divide3' incorporates:
   *  Constant: '<S123>/Constant4'
   */
  localB->Divide3 = localB->Divide4 / 256;

  /* UnitDelay: '<S122>/Unit Delay8' */
  localB->UnitDelay8 = localDW->UnitDelay8_DSTATE;

  /* Product: '<S123>/Divide6' incorporates:
   *  Constant: '<S123>/Constant7'
   */
  localB->Divide6 = localB->Divide3 * 100 * localB->UnitDelay8;

  /* Sum: '<S123>/Add2' */
  localB->Add2 = (localB->e_dot + localB->Gain9) - localB->Divide6;

  /* Saturate: '<S123>/Saturation2' */
  u0 = localB->Add2;
  u1 = STO_EST_MIN;
  u2 = STO_EST_MAX;
  if (u0 > u2) {
    /* Saturate: '<S123>/Saturation2' */
    e_alpha_dot = u2;
  } else if (u0 < u1) {
    /* Saturate: '<S123>/Saturation2' */
    e_alpha_dot = u1;
  } else {
    /* Saturate: '<S123>/Saturation2' */
    e_alpha_dot = u0;
  }

  /* End of Saturate: '<S123>/Saturation2' */

  /* Product: '<S124>/Divide1' incorporates:
   *  Constant: '<S124>/Constant4'
   */
  localB->Divide1_k = div_s16s32(e_alpha_dot, ((int16_T)STO_F2));

  /* UnitDelay: '<S124>/Unit Delay8' */
  localB->UnitDelay8_m = localDW->UnitDelay8_DSTATE_g;

  /* S-Function (sfun_EmCos): '<S124>/sfun_EmCos' */
  localB->cos_m = EmCos(localB->UnitDelay8_m);

  /* Product: '<S124>/Product' */
  localB->Product = localB->Divide1_k * localB->cos_m;

  /* ArithShift: '<S124>/Shift Arithmetic' incorporates:
   *  Constant: '<S124>/Constant'
   *  Product: '<S124>/Product'
   */
  localB->ShiftArithmetic = localB->Product >> 15U;

  /* UnitDelay: '<S123>/Unit Delay2' */
  localB->i_dot_h = localDW->UnitDelay2_DSTATE;

  /* Product: '<S123>/Divide5' incorporates:
   *  Constant: '<S123>/Constant6'
   */
  localB->i_dotF1_i = div_s32(localB->i_dot_h, ((int16_T)STO_F1));

  /* UnitDelay: '<S123>/Unit Delay7' */
  localB->i_a = localDW->UnitDelay7_DSTATE;

  /* Sum: '<S123>/Subtract3' */
  localB->i_dotF1i_b = localB->i_dotF1_i - localB->i_a;

  /* Gain: '<S123>/Gain10' */
  localB->Gain10 = STO_C4 * localB->i_dotF1i_b;

  /* Product: '<S123>/Divide1' incorporates:
   *  Constant: '<S123>/Constant2'
   */
  localB->Divide1 = div_s32(localB->e_dot, ((int16_T)STO_F2));

  /* Product: '<S123>/Divide8' incorporates:
   *  Constant: '<S123>/Constant8'
   */
  localB->Divide8 = localB->Divide1 / 256;

  /* Product: '<S123>/Divide7' incorporates:
   *  Constant: '<S123>/Constant9'
   */
  localB->Divide7 = localB->Divide8 * 100 * localB->UnitDelay8;

  /* Sum: '<S123>/Add3' */
  localB->Add3 = (localB->e_dot_i + localB->Gain10) + localB->Divide7;

  /* Saturate: '<S123>/Saturation3' */
  u0 = localB->Add3;
  u1 = STO_EST_MIN;
  u2 = STO_EST_MAX;
  if (u0 > u2) {
    /* Saturate: '<S123>/Saturation3' */
    e_beta_dot = u2;
  } else if (u0 < u1) {
    /* Saturate: '<S123>/Saturation3' */
    e_beta_dot = u1;
  } else {
    /* Saturate: '<S123>/Saturation3' */
    e_beta_dot = u0;
  }

  /* End of Saturate: '<S123>/Saturation3' */

  /* Product: '<S124>/Divide2' incorporates:
   *  Constant: '<S124>/Constant4'
   */
  localB->Divide2 = div_s16s32(e_beta_dot, ((int16_T)STO_F2));

  /* S-Function (sfun_EmSin): '<S124>/sfun_EmSin' */
  localB->sin_a = EmSin(localB->UnitDelay8_m);

  /* Product: '<S124>/Product1' */
  localB->Product1 = localB->Divide2 * localB->sin_a;

  /* ArithShift: '<S124>/Shift Arithmetic1' incorporates:
   *  Constant: '<S124>/Constant'
   *  Product: '<S124>/Product1'
   */
  localB->ShiftArithmetic1 = localB->Product1 >> 15U;

  /* Sum: '<S124>/Sum' */
  localB->theattheat_dot = -localB->ShiftArithmetic - localB->ShiftArithmetic1;

  /* Switch: '<S124>/Switch' */
  if (rtu_spd_ref >= 0) {
    /* Switch: '<S124>/Switch' */
    localB->Switch_e = localB->theattheat_dot;
  } else {
    /* Gain: '<S124>/Gain' */
    localB->Gain = -localB->theattheat_dot;

    /* Switch: '<S124>/Switch' */
    localB->Switch_e = localB->Gain;
  }

  /* End of Switch: '<S124>/Switch' */

  /* Gain: '<S164>/Proportional Gain' */
  localB->ProportionalGain = mul_s32_sat(PI_KP_PLL, localB->Switch_e);

  /* DiscreteIntegrator: '<S159>/Integrator' */
  localB->Integrator = localDW->Integrator_DSTATE;

  /* Sum: '<S168>/Sum' incorporates:
   *  DiscreteIntegrator: '<S159>/Integrator'
   *  Gain: '<S164>/Proportional Gain'
   */
  u0 = localB->ProportionalGain;
  u1 = localB->Integrator;
  if ((u0 < 0) && (u1 < MIN_int32_T - u0)) {
    u0 = MIN_int32_T;
  } else if ((u0 > 0) && (u1 > MAX_int32_T - u0)) {
    u0 = MAX_int32_T;
  } else {
    u0 += u1;
  }

  /* Sum: '<S168>/Sum' */
  localB->Sum = ((u0 < 0 ? 65535 : 0) + u0) >> 16;

  /* Saturate: '<S166>/Saturation' */
  u0 = localB->Sum;
  if (u0 > 1250) {
    /* Saturate: '<S166>/Saturation' */
    localB->Saturation = 1250;
  } else if (u0 < -1250) {
    /* Saturate: '<S166>/Saturation' */
    localB->Saturation = -1250;
  } else {
    /* Saturate: '<S166>/Saturation' */
    localB->Saturation = u0;
  }

  /* End of Saturate: '<S166>/Saturation' */

  /* DataTypeConversion: '<S124>/Data Type Conversion1' */
  localB->dpp = (int16_T)localB->Saturation;

  /* Product: '<S124>/Product2' */
  localB->Product2 = localB->Constant3 * localB->dpp;

  /* Product: '<S124>/Divide3' incorporates:
   *  Constant: '<S124>/Constant5'
   */
  localB->we_dot = div_s16s32(localB->Product2, ((uint16_T)RADTOS16_I));

  /* Product: '<S122>/Divide' incorporates:
   *  Constant: '<S122>/Constant'
   */
  *rty_w_dot = div_s16s32(localB->we_dot, ((uint8_T)MOTOR_PN));

  /* Gain: '<S123>/Gain1' */
  localB->Gain1 = STO_C1 * localB->i_dotF1;

  /* Sum: '<S123>/Subtract' */
  localB->Subtract = localB->i_dot - localB->Gain1;

  /* Gain: '<S123>/Gain4' */
  localB->Gain4 = STO_C2 * localB->i_dotF1i;

  /* Gain: '<S123>/Gain3' */
  localB->Gain3 = STO_C3 * localB->Divide1;

  /* UnitDelay: '<S123>/Unit Delay4' */
  localB->u = localDW->UnitDelay4_DSTATE;

  /* Gain: '<S123>/Gain2' */
  localB->Gain2 = STO_C5 * localB->u;

  /* Sum: '<S123>/Add' */
  localB->Add = ((localB->Subtract + localB->Gain4) - localB->Gain3) +
    localB->Gain2;

  /* Gain: '<S123>/Gain5' */
  localB->Gain5 = STO_C1 * localB->i_dotF1_i;

  /* Sum: '<S123>/Subtract2' */
  localB->Subtract2 = localB->i_dot_h - localB->Gain5;

  /* Gain: '<S123>/Gain8' */
  localB->Gain8 = STO_C2 * localB->i_dotF1i_b;

  /* Gain: '<S123>/Gain7' */
  localB->Gain7 = STO_C3 * localB->Divide4;

  /* UnitDelay: '<S123>/Unit Delay5' */
  localB->u_c = localDW->UnitDelay5_DSTATE;

  /* Gain: '<S123>/Gain6' */
  localB->Gain6 = STO_C5 * localB->u_c;

  /* Sum: '<S123>/Add1' */
  localB->Add1 = ((localB->Subtract2 + localB->Gain8) - localB->Gain7) +
    localB->Gain6;

  /* Saturate: '<S123>/Saturation' */
  u0 = localB->Add;
  u1 = STO_EST_MIN;
  u2 = STO_EST_MAX;
  if (u0 > u2) {
    u0 = u2;
  } else if (u0 < u1) {
    u0 = u1;
  }

  *rty_i_dot_next = u0;

  /* End of Saturate: '<S123>/Saturation' */

  /* Saturate: '<S123>/Saturation1' */
  u0 = localB->Add1;
  u1 = STO_EST_MIN;
  u2 = STO_EST_MAX;
  if (u0 > u2) {
    u0 = u2;
  } else if (u0 < u1) {
    u0 = u1;
  }

  *rty_i_dot_next_a = u0;

  /* End of Saturate: '<S123>/Saturation1' */

  /* DiscreteIntegrator: '<S124>/Discrete-Time Integrator' */
  if ((rtu_reset > 0) && (localDW->DiscreteTimeIntegrator_PrevRese <= 0)) {
    localDW->DiscreteTimeIntegrator_DSTATE = 0;
  }

  /* DiscreteIntegrator: '<S124>/Discrete-Time Integrator' */
  localB->DiscreteTimeIntegrator = localDW->DiscreteTimeIntegrator_DSTATE;

  /* Math: '<S124>/Math Function' */
  u0 = localB->DiscreteTimeIntegrator;

  /* Math: '<S124>/Math Function' */
  localB->MathFunction = u0 - (div_s32(u0, 65536) << 16);

  /* DataTypeConversion: '<S124>/Data Type Conversion' */
  *rty_theta_e_dot = (int16_T)localB->MathFunction;

  /* Gain: '<S150>/ZeroGain' */
  localB->ZeroGain = 0;

  /* DeadZone: '<S152>/DeadZone' */
  if (localB->Sum > 1250) {
    u0 = localB->Sum;
    if (u0 < -2147482398) {
      u0 = MIN_int32_T;
    } else {
      u0 -= 1250;
    }

    /* DeadZone: '<S152>/DeadZone' */
    localB->DeadZone = u0;
  } else if (localB->Sum >= -1250) {
    /* DeadZone: '<S152>/DeadZone' */
    localB->DeadZone = 0;
  } else {
    u0 = localB->Sum;
    if (u0 > 2147482397) {
      u0 = MAX_int32_T;
    } else {
      u0 -= -1250;
    }

    /* DeadZone: '<S152>/DeadZone' */
    localB->DeadZone = u0;
  }

  /* End of DeadZone: '<S152>/DeadZone' */

  /* RelationalOperator: '<S150>/NotEqual' */
  localB->NotEqual = (localB->ZeroGain != localB->DeadZone);

  /* Signum: '<S150>/SignPreSat' */
  u0 = localB->DeadZone;
  if (u0 < 0) {
    /* Signum: '<S150>/SignPreSat' */
    localB->SignPreSat = -1;
  } else {
    /* Signum: '<S150>/SignPreSat' */
    localB->SignPreSat = (u0 > 0);
  }

  /* End of Signum: '<S150>/SignPreSat' */

  /* DataTypeConversion: '<S150>/DataTypeConv1' */
  u0 = localB->SignPreSat;
  if (u0 > 127) {
    u0 = 127;
  } else if (u0 < -128) {
    u0 = -128;
  }

  /* DataTypeConversion: '<S150>/DataTypeConv1' */
  localB->DataTypeConv1 = (int8_T)u0;

  /* Gain: '<S156>/Integral Gain' */
  localB->IntegralGain = mul_s32_sat(PI_KI_PLL, localB->Switch_e);

  /* Signum: '<S150>/SignPreIntegrator' incorporates:
   *  Gain: '<S156>/Integral Gain'
   */
  u0 = localB->IntegralGain;
  if (u0 < 0) {
    /* Signum: '<S150>/SignPreIntegrator' */
    localB->SignPreIntegrator = -1;
  } else {
    /* Signum: '<S150>/SignPreIntegrator' */
    localB->SignPreIntegrator = (u0 > 0);
  }

  /* End of Signum: '<S150>/SignPreIntegrator' */

  /* DataTypeConversion: '<S150>/DataTypeConv2' */
  u0 = localB->SignPreIntegrator;
  if (u0 > 127) {
    u0 = 127;
  } else if (u0 < -128) {
    u0 = -128;
  }

  /* DataTypeConversion: '<S150>/DataTypeConv2' */
  localB->DataTypeConv2 = (int8_T)u0;

  /* RelationalOperator: '<S150>/Equal1' */
  localB->Equal1 = (localB->DataTypeConv1 == localB->DataTypeConv2);

  /* Logic: '<S150>/AND3' */
  localB->AND3 = (localB->NotEqual && localB->Equal1);

  /* Switch: '<S150>/Switch' */
  if (localB->AND3) {
    /* Switch: '<S150>/Switch' incorporates:
     *  Constant: '<S150>/Constant1'
     */
    localB->Switch = 0;
  } else {
    /* Switch: '<S150>/Switch' incorporates:
     *  Gain: '<S156>/Integral Gain'
     */
    localB->Switch = localB->IntegralGain;
  }

  /* End of Switch: '<S150>/Switch' */
  /* End of Outputs for SubSystem: '<S10>/Resettable Subsystem' */
}

/* Update for action system: '<S3>/ObserverPLL' */
void mmcs_s2f_ObserverPLL_Update(int16_T rtu_u_alpha_beta, int16_T
  rtu_u_alpha_beta_g, int16_T rtu_i_alpha_beta, int16_T rtu_i_alpha_beta_f,
  uint8_T rtu_reset, int16_T *rty_theta_e_dot, int32_T *rty_i_dot_next, int32_T *
  rty_i_dot_next_a, B_ObserverPLL_mmcs_s2f_T *localB, DW_ObserverPLL_mmcs_s2f_T *
  localDW)
{
  int32_T q0;
  int32_T q1;

  /* Update for Resettable SubSystem: '<S10>/Resettable Subsystem' incorporates:
   *  ResetPort: '<S122>/Reset'
   */
  /* Update for UnitDelay: '<S123>/Unit Delay1' */
  localDW->UnitDelay1_DSTATE = e_alpha_dot;

  /* Update for UnitDelay: '<S123>/Unit Delay' */
  localDW->UnitDelay_DSTATE = *rty_i_dot_next;

  /* Update for UnitDelay: '<S123>/Unit Delay6' */
  localDW->UnitDelay6_DSTATE = rtu_i_alpha_beta;

  /* Update for UnitDelay: '<S123>/Unit Delay3' */
  localDW->UnitDelay3_DSTATE = e_beta_dot;

  /* Update for UnitDelay: '<S122>/Unit Delay8' */
  localDW->UnitDelay8_DSTATE = localB->we_dot;

  /* Update for UnitDelay: '<S124>/Unit Delay8' */
  localDW->UnitDelay8_DSTATE_g = *rty_theta_e_dot;

  /* Update for UnitDelay: '<S123>/Unit Delay2' */
  localDW->UnitDelay2_DSTATE = *rty_i_dot_next_a;

  /* Update for UnitDelay: '<S123>/Unit Delay7' */
  localDW->UnitDelay7_DSTATE = rtu_i_alpha_beta_f;

  /* Update for DiscreteIntegrator: '<S159>/Integrator' incorporates:
   *  Switch: '<S150>/Switch'
   */
  q0 = localDW->Integrator_DSTATE;
  q1 = mul_s32_hiSR_zero(439804651, localB->Switch, 10U);
  if ((q0 < 0) && (q1 < MIN_int32_T - q0)) {
    q0 = MIN_int32_T;
  } else if ((q0 > 0) && (q1 > MAX_int32_T - q0)) {
    q0 = MAX_int32_T;
  } else {
    q0 += q1;
  }

  localDW->Integrator_DSTATE = q0;

  /* End of Update for DiscreteIntegrator: '<S159>/Integrator' */

  /* Update for UnitDelay: '<S123>/Unit Delay4' */
  localDW->UnitDelay4_DSTATE = rtu_u_alpha_beta;

  /* Update for UnitDelay: '<S123>/Unit Delay5' */
  localDW->UnitDelay5_DSTATE = rtu_u_alpha_beta_g;

  /* Update for DiscreteIntegrator: '<S124>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE += localB->dpp;
  localDW->DiscreteTimeIntegrator_PrevRese = (int8_T)(rtu_reset > 0);

  /* End of Update for SubSystem: '<S10>/Resettable Subsystem' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
