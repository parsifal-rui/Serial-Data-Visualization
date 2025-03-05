/*
 * File: CurrentLoop.c
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

#include "CurrentLoop.h"

/* Include model header file for global data */
#include "mmcs_s2f.h"
#include "mmcs_s2f_private.h"

/* System initialize for atomic system: '<S3>/CurrentLoop' */
void mmcs_s2f_CurrentLoop_Init(DW_CurrentLoop_mmcs_s2f_T *localDW)
{
  /* InitializeConditions for DiscreteIntegrator: '<S55>/Integrator' */
  localDW->Integrator_PrevResetState = 2;

  /* InitializeConditions for DiscreteIntegrator: '<S105>/Integrator' */
  localDW->Integrator_PrevResetState_i = 2;
}

/* Output and update for atomic system: '<S3>/CurrentLoop' */
void mmcs_s2f_CurrentLoop(uint8_T rtu_reset, const int16_T rtu_idq_ref[2],
  int16_T rtu_theta_e, const int16_T rtu_iab[2], uint16_T *rty_ccrx, uint16_T
  *rty_ccrx_f, uint16_T *rty_ccrx_m, int16_T *rty_u_alhpa_beta, int16_T
  *rty_u_alhpa_beta_a, int16_T *rty_i_alhpa_beta, int16_T *rty_i_alhpa_beta_a,
  B_CurrentLoop_mmcs_s2f_T *localB, DW_CurrentLoop_mmcs_s2f_T *localDW)
{
  int32_T q0;
  int32_T q1;
  int16_T u0;

  /* Saturate: '<S9>/Saturation1' */
  u0 = rtu_idq_ref[0];
  if (u0 > ((int16_T)REF_CURRENT_UPL)) {
    u0 = ((int16_T)REF_CURRENT_UPL);
  } else if (u0 < ((int16_T)REF_CURRENT_LOL)) {
    u0 = ((int16_T)REF_CURRENT_LOL);
  }

  /* Saturate: '<S9>/Saturation1' */
  localB->Saturation1[0] = u0;

  /* Saturate: '<S9>/Saturation1' */
  u0 = rtu_idq_ref[1];
  if (u0 > ((int16_T)REF_CURRENT_UPL)) {
    u0 = ((int16_T)REF_CURRENT_UPL);
  } else if (u0 < ((int16_T)REF_CURRENT_LOL)) {
    u0 = ((int16_T)REF_CURRENT_LOL);
  }

  /* Saturate: '<S9>/Saturation1' */
  localB->Saturation1[1] = u0;

  /* DataTypeConversion: '<S9>/Data Type Conversion' */
  ia = rtu_iab[0];

  /* DataTypeConversion: '<S9>/Data Type Conversion1' */
  ib = rtu_iab[1];

  /* Outputs for Atomic SubSystem: '<S9>/Clark' */
  mmcs_s2f_Clark(ia, ib, &localB->ia_a, &localB->DataTypeConversion_m,
                 &localB->Clark);

  /* End of Outputs for SubSystem: '<S9>/Clark' */

  /* SignalConversion generated from: '<S9>/Clark' */
  *rty_i_alhpa_beta = localB->ia_a;

  /* SignalConversion generated from: '<S9>/Clark' */
  *rty_i_alhpa_beta_a = localB->DataTypeConversion_m;

  /* S-Function (sfun_EmSin): '<S9>/sfun_EmSin' */
  localB->sin_o = EmSin(rtu_theta_e);

  /* S-Function (sfun_EmCos): '<S9>/sfun_EmCos' */
  localB->cos_n = EmCos(rtu_theta_e);

  /* Outputs for Atomic SubSystem: '<S9>/Park' */
  mmcs_s2f_Park(*rty_i_alhpa_beta, *rty_i_alhpa_beta_a, localB->sin_o,
                localB->cos_n, &localB->DataTypeConversion,
                &localB->DataTypeConversion1, &localB->Park);

  /* End of Outputs for SubSystem: '<S9>/Park' */

  /* SignalConversion generated from: '<S9>/Park' */
  id = localB->DataTypeConversion;

  /* Sum: '<S9>/Sum3' */
  id_err = (int16_T)(localB->Saturation1[0] - id);

  /* Gain: '<S60>/Proportional Gain' */
  localB->ProportionalGain = mul_s32_loSR_sat_zero(PI_KP_TQ, id_err, 2U);

  /* DiscreteIntegrator: '<S55>/Integrator' */
  if ((rtu_reset > 0) && (localDW->Integrator_PrevResetState <= 0)) {
    localDW->Integrator_DSTATE = 0;
  }

  /* DiscreteIntegrator: '<S55>/Integrator' */
  localB->Integrator = localDW->Integrator_DSTATE;

  /* Sum: '<S64>/Sum' incorporates:
   *  DiscreteIntegrator: '<S55>/Integrator'
   *  Gain: '<S60>/Proportional Gain'
   */
  q0 = localB->ProportionalGain;
  q1 = localB->Integrator;
  if ((q0 < 0) && (q1 < MIN_int32_T - q0)) {
    q0 = MIN_int32_T;
  } else if ((q0 > 0) && (q1 > MAX_int32_T - q0)) {
    q0 = MAX_int32_T;
  } else {
    q0 += q1;
  }

  /* Sum: '<S64>/Sum' */
  localB->Sum = ((q0 < 0 ? 16383 : 0) + q0) >> 14;

  /* Saturate: '<S62>/Saturation' */
  q0 = localB->Sum;
  if (q0 > 32767) {
    /* Saturate: '<S62>/Saturation' */
    localB->Saturation = 32767;
  } else if (q0 < -32768) {
    /* Saturate: '<S62>/Saturation' */
    localB->Saturation = -32768;
  } else {
    /* Saturate: '<S62>/Saturation' */
    localB->Saturation = q0;
  }

  /* End of Saturate: '<S62>/Saturation' */

  /* DataTypeConversion: '<S9>/Data Type Conversion2' */
  localB->DataTypeConversion2 = (int16_T)localB->Saturation;

  /* SignalConversion generated from: '<S9>/Park' */
  iq = localB->DataTypeConversion1;

  /* Sum: '<S9>/Sum1' */
  iq_err = (int16_T)(localB->Saturation1[1] - iq);

  /* Gain: '<S110>/Proportional Gain' */
  localB->ProportionalGain_o = mul_s32_loSR_sat_zero(PI_KP_TQ, iq_err, 2U);

  /* DiscreteIntegrator: '<S105>/Integrator' */
  if ((rtu_reset > 0) && (localDW->Integrator_PrevResetState_i <= 0)) {
    localDW->Integrator_DSTATE_f = 0;
  }

  /* DiscreteIntegrator: '<S105>/Integrator' */
  localB->Integrator_f = localDW->Integrator_DSTATE_f;

  /* Sum: '<S114>/Sum' incorporates:
   *  DiscreteIntegrator: '<S105>/Integrator'
   *  Gain: '<S110>/Proportional Gain'
   */
  q0 = localB->ProportionalGain_o;
  q1 = localB->Integrator_f;
  if ((q0 < 0) && (q1 < MIN_int32_T - q0)) {
    q0 = MIN_int32_T;
  } else if ((q0 > 0) && (q1 > MAX_int32_T - q0)) {
    q0 = MAX_int32_T;
  } else {
    q0 += q1;
  }

  /* Sum: '<S114>/Sum' */
  localB->Sum_c = ((q0 < 0 ? 16383 : 0) + q0) >> 14;

  /* Saturate: '<S112>/Saturation' */
  q0 = localB->Sum_c;
  if (q0 > 32767) {
    /* Saturate: '<S112>/Saturation' */
    localB->Saturation_d = 32767;
  } else if (q0 < -32768) {
    /* Saturate: '<S112>/Saturation' */
    localB->Saturation_d = -32768;
  } else {
    /* Saturate: '<S112>/Saturation' */
    localB->Saturation_d = q0;
  }

  /* End of Saturate: '<S112>/Saturation' */

  /* DataTypeConversion: '<S9>/Data Type Conversion3' */
  localB->DataTypeConversion3 = (int16_T)localB->Saturation_d;

  /* S-Function (sfun_CircleLimit): '<S9>/sfun_CircleLimit' */
  CircleLimit(localB->DataTypeConversion2, localB->DataTypeConversion3, &ud, &uq);

  /* Outputs for Atomic SubSystem: '<S9>/AntiPark' */
  mmcs_s2f_AntiPark(ud, uq, localB->sin_o, localB->cos_n,
                    &localB->DataTypeConversion_f,
                    &localB->DataTypeConversion1_f, &localB->AntiPark);

  /* End of Outputs for SubSystem: '<S9>/AntiPark' */

  /* Gain: '<S46>/ZeroGain' */
  localB->ZeroGain = 0;

  /* DeadZone: '<S48>/DeadZone' */
  if (localB->Sum > 32767) {
    q0 = localB->Sum;
    if (q0 < -2147450881) {
      q0 = MIN_int32_T;
    } else {
      q0 -= 32767;
    }

    /* DeadZone: '<S48>/DeadZone' */
    localB->DeadZone = q0;
  } else if (localB->Sum >= -32768) {
    /* DeadZone: '<S48>/DeadZone' */
    localB->DeadZone = 0;
  } else {
    q0 = localB->Sum;
    if (q0 > 2147450879) {
      q0 = MAX_int32_T;
    } else {
      q0 -= -32768;
    }

    /* DeadZone: '<S48>/DeadZone' */
    localB->DeadZone = q0;
  }

  /* End of DeadZone: '<S48>/DeadZone' */

  /* RelationalOperator: '<S46>/NotEqual' */
  localB->NotEqual = (localB->ZeroGain != localB->DeadZone);

  /* Signum: '<S46>/SignPreSat' */
  q0 = localB->DeadZone;
  if (q0 < 0) {
    /* Signum: '<S46>/SignPreSat' */
    localB->SignPreSat = -1;
  } else {
    /* Signum: '<S46>/SignPreSat' */
    localB->SignPreSat = (q0 > 0);
  }

  /* End of Signum: '<S46>/SignPreSat' */

  /* DataTypeConversion: '<S46>/DataTypeConv1' */
  q0 = localB->SignPreSat;
  if (q0 > 127) {
    q0 = 127;
  } else if (q0 < -128) {
    q0 = -128;
  }

  /* DataTypeConversion: '<S46>/DataTypeConv1' */
  localB->DataTypeConv1 = (int8_T)q0;

  /* Gain: '<S52>/Integral Gain' */
  localB->IntegralGain = mul_s32_loSR_sat_zero(PI_KI_TQ, id_err, 2U);

  /* Signum: '<S46>/SignPreIntegrator' incorporates:
   *  Gain: '<S52>/Integral Gain'
   */
  q0 = localB->IntegralGain;
  if (q0 < 0) {
    /* Signum: '<S46>/SignPreIntegrator' */
    localB->SignPreIntegrator = -1;
  } else {
    /* Signum: '<S46>/SignPreIntegrator' */
    localB->SignPreIntegrator = (q0 > 0);
  }

  /* End of Signum: '<S46>/SignPreIntegrator' */

  /* DataTypeConversion: '<S46>/DataTypeConv2' */
  q0 = localB->SignPreIntegrator;
  if (q0 > 127) {
    q0 = 127;
  } else if (q0 < -128) {
    q0 = -128;
  }

  /* DataTypeConversion: '<S46>/DataTypeConv2' */
  localB->DataTypeConv2 = (int8_T)q0;

  /* RelationalOperator: '<S46>/Equal1' */
  localB->Equal1 = (localB->DataTypeConv1 == localB->DataTypeConv2);

  /* Logic: '<S46>/AND3' */
  localB->AND3 = (localB->NotEqual && localB->Equal1);

  /* Switch: '<S46>/Switch' */
  if (localB->AND3) {
    /* Switch: '<S46>/Switch' incorporates:
     *  Constant: '<S46>/Constant1'
     */
    localB->Switch = 0;
  } else {
    /* Switch: '<S46>/Switch' incorporates:
     *  Gain: '<S52>/Integral Gain'
     */
    localB->Switch = localB->IntegralGain;
  }

  /* End of Switch: '<S46>/Switch' */

  /* Gain: '<S96>/ZeroGain' */
  localB->ZeroGain_a = 0;

  /* DeadZone: '<S98>/DeadZone' */
  if (localB->Sum_c > 32767) {
    q0 = localB->Sum_c;
    if (q0 < -2147450881) {
      q0 = MIN_int32_T;
    } else {
      q0 -= 32767;
    }

    /* DeadZone: '<S98>/DeadZone' */
    localB->DeadZone_g = q0;
  } else if (localB->Sum_c >= -32768) {
    /* DeadZone: '<S98>/DeadZone' */
    localB->DeadZone_g = 0;
  } else {
    q0 = localB->Sum_c;
    if (q0 > 2147450879) {
      q0 = MAX_int32_T;
    } else {
      q0 -= -32768;
    }

    /* DeadZone: '<S98>/DeadZone' */
    localB->DeadZone_g = q0;
  }

  /* End of DeadZone: '<S98>/DeadZone' */

  /* RelationalOperator: '<S96>/NotEqual' */
  localB->NotEqual_c = (localB->ZeroGain_a != localB->DeadZone_g);

  /* Signum: '<S96>/SignPreSat' */
  q0 = localB->DeadZone_g;
  if (q0 < 0) {
    /* Signum: '<S96>/SignPreSat' */
    localB->SignPreSat_m = -1;
  } else {
    /* Signum: '<S96>/SignPreSat' */
    localB->SignPreSat_m = (q0 > 0);
  }

  /* End of Signum: '<S96>/SignPreSat' */

  /* DataTypeConversion: '<S96>/DataTypeConv1' */
  q0 = localB->SignPreSat_m;
  if (q0 > 127) {
    q0 = 127;
  } else if (q0 < -128) {
    q0 = -128;
  }

  /* DataTypeConversion: '<S96>/DataTypeConv1' */
  localB->DataTypeConv1_f = (int8_T)q0;

  /* Gain: '<S102>/Integral Gain' */
  localB->IntegralGain_c = mul_s32_loSR_sat_zero(PI_KI_TQ, iq_err, 2U);

  /* Signum: '<S96>/SignPreIntegrator' incorporates:
   *  Gain: '<S102>/Integral Gain'
   */
  q0 = localB->IntegralGain_c;
  if (q0 < 0) {
    /* Signum: '<S96>/SignPreIntegrator' */
    localB->SignPreIntegrator_e = -1;
  } else {
    /* Signum: '<S96>/SignPreIntegrator' */
    localB->SignPreIntegrator_e = (q0 > 0);
  }

  /* End of Signum: '<S96>/SignPreIntegrator' */

  /* DataTypeConversion: '<S96>/DataTypeConv2' */
  q0 = localB->SignPreIntegrator_e;
  if (q0 > 127) {
    q0 = 127;
  } else if (q0 < -128) {
    q0 = -128;
  }

  /* DataTypeConversion: '<S96>/DataTypeConv2' */
  localB->DataTypeConv2_l = (int8_T)q0;

  /* RelationalOperator: '<S96>/Equal1' */
  localB->Equal1_p = (localB->DataTypeConv1_f == localB->DataTypeConv2_l);

  /* Logic: '<S96>/AND3' */
  localB->AND3_i = (localB->NotEqual_c && localB->Equal1_p);

  /* Switch: '<S96>/Switch' */
  if (localB->AND3_i) {
    /* Switch: '<S96>/Switch' incorporates:
     *  Constant: '<S96>/Constant1'
     */
    localB->Switch_g = 0;
  } else {
    /* Switch: '<S96>/Switch' incorporates:
     *  Gain: '<S102>/Integral Gain'
     */
    localB->Switch_g = localB->IntegralGain_c;
  }

  /* End of Switch: '<S96>/Switch' */

  /* SignalConversion generated from: '<S9>/AntiPark' */
  *rty_u_alhpa_beta = localB->DataTypeConversion_f;

  /* SignalConversion generated from: '<S9>/AntiPark' */
  *rty_u_alhpa_beta_a = localB->DataTypeConversion1_f;

  /* S-Function (sfun_EmSvpwm): '<S9>/sfun_EmSvpwm' */
  EmSvpwm((*rty_u_alhpa_beta), (*rty_u_alhpa_beta_a), rty_ccrx, rty_ccrx_f,
          rty_ccrx_m, &localB->sfun_EmSvpwm_o4);

  /* Update for DiscreteIntegrator: '<S55>/Integrator' incorporates:
   *  Switch: '<S46>/Switch'
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
  localDW->Integrator_PrevResetState = (int8_T)(rtu_reset > 0);

  /* End of Update for DiscreteIntegrator: '<S55>/Integrator' */

  /* Update for DiscreteIntegrator: '<S105>/Integrator' incorporates:
   *  Switch: '<S96>/Switch'
   */
  q0 = localDW->Integrator_DSTATE_f;
  q1 = mul_s32_hiSR_zero(439804651, localB->Switch_g, 10U);
  if ((q0 < 0) && (q1 < MIN_int32_T - q0)) {
    q0 = MIN_int32_T;
  } else if ((q0 > 0) && (q1 > MAX_int32_T - q0)) {
    q0 = MAX_int32_T;
  } else {
    q0 += q1;
  }

  localDW->Integrator_DSTATE_f = q0;
  localDW->Integrator_PrevResetState_i = (int8_T)(rtu_reset > 0);

  /* End of Update for DiscreteIntegrator: '<S105>/Integrator' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
