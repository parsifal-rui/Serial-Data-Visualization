/*
 * File: HFTask.c
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

#include "HFTask.h"

/* Include model header file for global data */
#include "mmcs_s2f.h"
#include "mmcs_s2f_private.h"

/* System initialize for atomic system: '<Root>/HFTask' */
void mmcs_s2f_HFTask_Init(int16_T *rty_w_dot, DW_HFTask_mmcs_s2f_T *localDW)
{
  /* Start for If: '<S3>/If' */
  localDW->If_ActiveSubsystem = -1;

  /* SystemInitialize for Atomic SubSystem: '<S3>/CurrentLoop' */
  mmcs_s2f_CurrentLoop_Init(&localDW->CurrentLoop);

  /* End of SystemInitialize for SubSystem: '<S3>/CurrentLoop' */

  /* SystemInitialize for IfAction SubSystem: '<S3>/ObserverPLL' */
  mmcs_s2f_ObserverPLL_Init(rty_w_dot, &localDW->ObserverPLL);

  /* End of SystemInitialize for SubSystem: '<S3>/ObserverPLL' */
}

/* Output and update for atomic system: '<Root>/HFTask' */
void mmcs_s2f_HFTask(uint8_T rtu_sys_ctrl_mode, uint8_T rtu_ct_ctrl_mode,
                     uint8_T rtu_stm_state, const int16_T rtu_idq_ref[2],
                     int16_T rtu_spd_ramp, const int16_T rtu_iab[2], int16_T
                     rtu_theta_sensor, int16_T rtu_spd_ref, uint16_T *rty_ccrx,
                     uint16_T *rty_ccrx_e, uint16_T *rty_ccrx_o, int16_T
                     *rty_theta_e_dot, int16_T *rty_w_dot, B_HFTask_mmcs_s2f_T
                     *localB, DW_HFTask_mmcs_s2f_T *localDW,
                     ZCE_HFTask_mmcs_s2f_T *localZCE)
{
  int64m_T tmp_3;
  int64m_T tmp_5;
  int64m_T tmp_6;
  int64m_T tmp_7;
  int64m_T tmp_8;
  int96m_T tmp_4;
  uint32_T tmp_1;
  uint32_T tmp_2;
  int8_T rtAction;

  /* RelationalOperator: '<S6>/Relational Operator1' incorporates:
   *  Constant: '<S6>/Constant1'
   */
  localB->RelationalOperator1 = (rtu_ct_ctrl_mode == ((uint8_T)TORQ_CTRL));

  /* RelationalOperator: '<S8>/Compare' incorporates:
   *  Constant: '<S8>/Constant'
   */
  localB->Compare = (uint8_T)(rtu_sys_ctrl_mode == ((uint8_T)STO_ST_CTRL));

  /* RelationalOperator: '<S7>/Compare' incorporates:
   *  Constant: '<S7>/Constant'
   */
  localB->Compare_f = (uint8_T)(rtu_stm_state == ((uint8_T)STM_START));

  /* If: '<S3>/If' incorporates:
   *  Constant: '<S3>/Constant'
   */
  rtAction = -1;
  if (localB->Compare > 0) {
    rtAction = 0;

    /* Outputs for IfAction SubSystem: '<S3>/ObserverPLL' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    mmcs_s2f_ObserverPLL(localB->Compare_f, 0, rtu_spd_ref, rty_theta_e_dot,
                         rty_w_dot, &i_alpha_dot, &i_beta_dot,
                         &localB->ObserverPLL, &localDW->ObserverPLL,
                         &localZCE->ObserverPLL);

    /* End of Outputs for SubSystem: '<S3>/ObserverPLL' */
  }

  localDW->If_ActiveSubsystem = rtAction;

  /* End of If: '<S3>/If' */

  /* RelationalOperator: '<S13>/Compare' incorporates:
   *  Constant: '<S13>/Constant'
   */
  localB->Compare_m = (uint8_T)(rtu_stm_state == ((uint8_T)STM_ALIGN));

  /* DiscreteIntegrator: '<S16>/Discrete-Time Integrator1' */
  if ((localB->Compare_m != 0) || (localDW->DiscreteTimeIntegrator1_PrevRes != 0))
  {
    localDW->DiscreteTimeIntegrator1_DSTATE = 0;
  }

  /* DiscreteIntegrator: '<S16>/Discrete-Time Integrator1' */
  localB->DiscreteTimeIntegrator1 = localDW->DiscreteTimeIntegrator1_DSTATE;

  /* Constant: '<S16>/Constant7' */
  localB->Constant7 = ((uint16_T)ENC_PULSE_NUM);

  /* Switch: '<S6>/Switch1' */
  if (localB->RelationalOperator1) {
    /* Switch: '<S11>/Switch1' */
    if (localB->Compare_m > 0) {
      /* RelationalOperator: '<S12>/Compare' incorporates:
       *  Constant: '<S12>/Constant'
       */
      localB->Compare_p = (uint8_T)(rtu_sys_ctrl_mode == ((uint8_T)ENC_PT_CTRL));

      /* RelationalOperator: '<S14>/Compare' incorporates:
       *  Constant: '<S14>/Constant'
       */
      localB->Compare_d = (uint8_T)(rtu_sys_ctrl_mode == ((uint8_T)ENC_ST_CTRL));

      /* Logic: '<S11>/Logical Operator' */
      localB->LogicalOperator = ((localB->Compare_d != 0) || (localB->Compare_p
        != 0));

      /* Switch: '<S11>/Switch2' */
      if (localB->LogicalOperator) {
        /* Switch: '<S11>/Switch2' incorporates:
         *  Constant: '<S11>/Constant3'
         */
        localB->Switch2 = ((int16_T)ALIGN_THETA);
      } else {
        /* Switch: '<S11>/Switch2' incorporates:
         *  Constant: '<S11>/Constant4'
         */
        localB->Switch2 = 0;
      }

      /* End of Switch: '<S11>/Switch2' */

      /* Switch: '<S11>/Switch1' */
      localB->Switch1 = localB->Switch2;
    } else {
      int32_T u0;
      int32_T u1;
      int16_T tmp_0;
      uint8_T tmp;

      /* Product: '<S16>/Divide' incorporates:
       *  Constant: '<S16>/Constant1'
       */
      localB->Divide = localB->DiscreteTimeIntegrator1 / 60;

      /* Sum: '<S16>/Add' */
      localB->Add = localB->Divide;

      /* Math: '<S16>/Math Function' */
      u0 = localB->Add;
      u1 = localB->Constant7;
      if (u1 == 0) {
        /* Math: '<S16>/Math Function' */
        localB->MathFunction = 0;
      } else {
        /* Math: '<S16>/Math Function' */
        localB->MathFunction = u0 - u1 * div_s32(u0, u1);
      }

      /* End of Math: '<S16>/Math Function' */

      /* Product: '<S15>/Product2' incorporates:
       *  Constant: '<S15>/Constant6'
       */
      tmp_1 = (uint32_T)localB->MathFunction;
      tmp_2 = U32MAXdivPulseNumber;
      ssuMultiWordMul(&tmp_1, 1, &tmp_2, 1, &tmp_3.chunks[0U], 2);

      /* Product: '<S15>/Product2' */
      localB->Product2 = tmp_3;

      /* Product: '<S15>/Divide' incorporates:
       *  Product: '<S15>/Product2'
       */
      tmp_3 = localB->Product2;
      sLong2MultiWord(65536, &tmp_5.chunks[0U], 2);
      sMultiWordDivZero(&tmp_3.chunks[0U], 2, &tmp_5.chunks[0U], 2,
                        &tmp_4.chunks[0U], 3, &tmp_6.chunks[0U], 2,
                        &tmp_7.chunks[0U], 2, &tmp_8.chunks[0U], 2);
      u0 = MultiWord2sLong(&tmp_4.chunks[0U]);

      /* Product: '<S15>/Divide' */
      localB->Divide_o = u0;

      /* DataTypeConversion: '<S15>/Data Type Conversion1' */
      localB->theta_m = (int16_T)localB->Divide_o;

      /* Gain: '<S15>/Gain5' */
      tmp = ((uint8_T)MOTOR_PN);
      if (tmp > 7) {
        tmp_0 = MAX_int16_T;
      } else {
        tmp_0 = (int16_T)(tmp << 12);
      }

      u0 = tmp_0 * localB->theta_m;

      /* Gain: '<S15>/Gain5' */
      localB->Gain5 = ((u0 < 0 ? 4095 : 0) + u0) >> 12;

      /* DataTypeConversion: '<S15>/Data Type Conversion2' */
      localB->theta_e_c = (int16_T)localB->Gain5;

      /* Switch: '<S11>/Switch1' */
      localB->Switch1 = localB->theta_e_c;
    }

    /* End of Switch: '<S11>/Switch1' */

    /* Switch: '<S6>/Switch1' */
    theta_e = localB->Switch1;
  } else {
    /* RelationalOperator: '<S6>/Relational Operator2' incorporates:
     *  Constant: '<S6>/Constant2'
     */
    localB->RelationalOperator2 = (rtu_sys_ctrl_mode == ((uint8_T)STO_ST_CTRL));

    /* Switch: '<S6>/Switch' */
    if (localB->RelationalOperator2) {
      /* Switch: '<S6>/Switch' */
      localB->Switch = *rty_theta_e_dot;
    } else {
      /* Switch: '<S6>/Switch' */
      localB->Switch = rtu_theta_sensor;
    }

    /* End of Switch: '<S6>/Switch' */

    /* Switch: '<S6>/Switch1' */
    theta_e = localB->Switch;
  }

  /* End of Switch: '<S6>/Switch1' */

  /* Product: '<S16>/Product1' */
  localB->Product1 = rtu_spd_ramp * localB->Constant7;

  /* Outputs for Atomic SubSystem: '<S3>/CurrentLoop' */
  mmcs_s2f_CurrentLoop(localB->Compare_f, rtu_idq_ref, theta_e, rtu_iab,
                       rty_ccrx, rty_ccrx_e, rty_ccrx_o, &u_alpha, &u_beta,
                       &i_alpha, &i_beta, &localB->CurrentLoop,
                       &localDW->CurrentLoop);

  /* End of Outputs for SubSystem: '<S3>/CurrentLoop' */

  /* Update for If: '<S3>/If' incorporates:
   *  Constant: '<S3>/Constant'
   */
  if (localDW->If_ActiveSubsystem == 0) {
    /* Update for IfAction SubSystem: '<S3>/ObserverPLL' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    mmcs_s2f_ObserverPLL_Update(u_alpha, u_beta, i_alpha, i_beta, 0,
      rty_theta_e_dot, &i_alpha_dot, &i_beta_dot, &localB->ObserverPLL,
      &localDW->ObserverPLL);

    /* End of Update for SubSystem: '<S3>/ObserverPLL' */
  }

  /* End of Update for If: '<S3>/If' */

  /* Update for DiscreteIntegrator: '<S16>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE += mul_s32_hiSR_zero(439804651,
    localB->Product1, 10U);
  localDW->DiscreteTimeIntegrator1_PrevRes = (int8_T)(localB->Compare_m > 0);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
