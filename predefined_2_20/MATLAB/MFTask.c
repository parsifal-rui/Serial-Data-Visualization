/*
 * File: MFTask.c
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

#include "MFTask.h"

/* Include model header file for global data */
#include "mmcs_s2f.h"
#include "mmcs_s2f_private.h"

/* Named constants for Chart: '<S4>/Chart1' */
#define mmcs_s2f_IN_ALIGN              ((uint8_T)1U)
#define mmcs_s2f_IN_ANY_STOP           ((uint8_T)2U)
#define mmcs_s2f_IN_IDLE               ((uint8_T)3U)
#define mmcs_s2f_IN_IF_RUN             ((uint8_T)4U)
#define mmcs_s2f_IN_INIT               ((uint8_T)5U)
#define mmcs_s2f_IN_PREPARE            ((uint8_T)6U)
#define mmcs_s2f_IN_PT_RUN             ((uint8_T)7U)
#define mmcs_s2f_IN_START              ((uint8_T)8U)
#define mmcs_s2f_IN_STOP               ((uint8_T)9U)
#define mmcs_s2f_IN_STOP_IDLE          ((uint8_T)10U)
#define mmcs_s2f_IN_ST_RUN             ((uint8_T)11U)
#define mmcs_s2f_IN_SWITCH             ((uint8_T)12U)

/* System initialize for atomic system: '<Root>/MFTask' */
void mmcs_s2f_MFTask_Init(uint8_T *rty_ct_ctrl_mode, uint8_T *rty_stm_state,
  int16_T *rty_idq_ref, int16_T *rty_idq_ref_l, int16_T *rty_spd_ramp,
  DW_MFTask_mmcs_s2f_T *localDW)
{
  /* SystemInitialize for Chart: '<S4>/Chart1' */
  *rty_stm_state = 1U;
  *rty_ct_ctrl_mode = 0U;

  /* SystemInitialize for IfAction SubSystem: '<S4>/TorqCtrl' */
  /* InitializeConditions for DiscreteIntegrator: '<S314>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_IC_LOAD = 1U;

  /* InitializeConditions for DiscreteIntegrator: '<S315>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_IC_LO_a = 1U;

  /* End of SystemInitialize for SubSystem: '<S4>/TorqCtrl' */

  /* SystemInitialize for Merge: '<S4>/Merge' */
  *rty_idq_ref = 0;

  /* SystemInitialize for Merge: '<S4>/Merge1' */
  *rty_idq_ref_l = 0;

  /* SystemInitialize for Merge: '<S4>/Merge2' */
  *rty_spd_ramp = 0;
}

/* Output and update for atomic system: '<Root>/MFTask' */
void mmcs_s2f_MFTask(uint8_T rtu_sys_ctrl_mode, uint8_T rtu_motor_start, int16_T
                     rtu_spd_ref, int16_T rtu_spd_fed, real32_T rtu_pos_ref,
                     real32_T rtu_duration, int32_T rtu_pos_fed, uint8_T
                     *rty_ct_ctrl_mode, uint8_T *rty_stm_state, int16_T
                     *rty_idq_ref, int16_T *rty_idq_ref_l, int16_T *rty_spd_ramp,
                     B_MFTask_mmcs_s2f_T *localB, DW_MFTask_mmcs_s2f_T *localDW)
{
  /* Outputs for Atomic SubSystem: '<S4>/IsTransition' */
  /* Abs: '<S177>/Abs' */
  if (rtu_spd_ref < 0) {
    /* Abs: '<S177>/Abs' */
    localB->Abs = (int16_T)-rtu_spd_ref;
  } else {
    /* Abs: '<S177>/Abs' */
    localB->Abs = rtu_spd_ref;
  }

  /* End of Abs: '<S177>/Abs' */

  /* RelationalOperator: '<S184>/Compare' incorporates:
   *  Constant: '<S184>/Constant'
   */
  localB->Compare_m = (localB->Abs >= ((int16_T)IF_FINAL_SPEED));

  /* RelationalOperator: '<S177>/Relational Operator' incorporates:
   *  Constant: '<S177>/Constant'
   */
  localB->RelationalOperator_p = (rtu_sys_ctrl_mode == ((uint8_T)STO_ST_CTRL));

  /* UnitDelay: '<S177>/Unit Delay1' */
  localB->UnitDelay1_l = localDW->UnitDelay1_DSTATE_c;

  /* RelationalOperator: '<S177>/Relational Operator1' incorporates:
   *  Constant: '<S177>/Constant1'
   */
  localB->RelationalOperator1 = (localB->UnitDelay1_l == ((uint8_T)STM_IFRUN));

  /* Logic: '<S177>/Logical Operator' */
  localB->LogicalOperator_p = (localB->RelationalOperator_p &&
    localB->RelationalOperator1);

  /* If: '<S177>/If' */
  if (localB->LogicalOperator_p) {
    /* Outputs for IfAction SubSystem: '<S177>/If Action Subsystem' incorporates:
     *  ActionPort: '<S185>/Action Port'
     */
    /* Abs: '<S185>/Abs' */
    if (rtu_spd_fed < 0) {
      /* Abs: '<S185>/Abs' */
      localB->Abs_i = (int16_T)-rtu_spd_fed;
    } else {
      /* Abs: '<S185>/Abs' */
      localB->Abs_i = rtu_spd_fed;
    }

    /* End of Abs: '<S185>/Abs' */

    /* Product: '<S185>/Product' incorporates:
     *  Constant: '<S185>/Constant1'
     *  Constant: '<S185>/Constant2'
     */
    localB->Product_n = (int16_T)(((int16_T)IF_FINAL_SPEED) * 9);

    /* Product: '<S185>/Divide' incorporates:
     *  Constant: '<S185>/Constant3'
     */
    localB->Divide_f = (int16_T)(localB->Product_n / 10);

    /* Product: '<S185>/Product1' incorporates:
     *  Constant: '<S185>/Constant1'
     *  Constant: '<S185>/Constant4'
     */
    localB->Product1_a = (int16_T)(((int16_T)IF_FINAL_SPEED) * 11);

    /* Product: '<S185>/Divide1' incorporates:
     *  Constant: '<S185>/Constant5'
     */
    localB->Divide1_b = (int16_T)(localB->Product1_a / 10);

    /* RelationalOperator: '<S185>/Relational Operator' */
    localB->RelationalOperator_a = (localB->Abs_i >= localB->Divide_f);

    /* RelationalOperator: '<S185>/Relational Operator1' */
    localB->RelationalOperator1_p = (localB->Abs_i <= localB->Divide1_b);

    /* Logic: '<S185>/Logical Operator' */
    localB->LogicalOperator_o = (localB->RelationalOperator_a &&
      localB->RelationalOperator1_p);

    /* End of Outputs for SubSystem: '<S177>/If Action Subsystem' */
  }

  /* End of If: '<S177>/If' */

  /* Logic: '<S177>/Logical Operator1' */
  localB->LogicalOperator1_o = (localB->LogicalOperator_o && localB->Compare_m);

  /* End of Outputs for SubSystem: '<S4>/IsTransition' */

  /* Chart: '<S4>/Chart1' */
  if (localDW->temporalCounter_i1 < 65535U) {
    localDW->temporalCounter_i1++;
  }

  if (localDW->is_active_c3_mmcs_s2f == 0U) {
    localDW->is_active_c3_mmcs_s2f = 1U;
    localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_INIT;
    *rty_stm_state = ((uint8_T)STM_INIT);
    *rty_ct_ctrl_mode = ((uint8_T)TORQ_CTRL);
  } else {
    switch (localDW->is_c3_mmcs_s2f) {
     case mmcs_s2f_IN_ALIGN:
      if ((localDW->temporalCounter_i1 << 1) >= ((uint16_T)ALIGN_DURATION)) {
        localDW->align_comp = 1U;
        localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_ANY_STOP;
        *rty_stm_state = ((uint8_T)STM_ANY_STOP);
      } else {
        *rty_stm_state = ((uint8_T)STM_ALIGN);
      }
      break;

     case mmcs_s2f_IN_ANY_STOP:
      localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_STOP;
      localDW->temporalCounter_i1 = 0U;
      *rty_stm_state = ((uint8_T)STM_STOP);
      break;

     case mmcs_s2f_IN_IDLE:
      if (rtu_motor_start != 0) {
        localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_PREPARE;
        localDW->temporalCounter_i1 = 0U;
        *rty_stm_state = ((uint8_T)STM_PREPARE);
        *rty_ct_ctrl_mode = ((uint8_T)TORQ_CTRL);
        if (rtu_sys_ctrl_mode == ((uint8_T)HALL_ST_CTRL)) {
          localDW->align_comp = 1U;
        }

        if (localDW->align_comp == 1) {
          if ((rtu_sys_ctrl_mode == ((uint8_T)ENC_ST_CTRL)) ||
              (rtu_sys_ctrl_mode == ((uint8_T)HALL_ST_CTRL))) {
            *rty_ct_ctrl_mode = ((uint8_T)SPD_CTRL);
          } else if (rtu_sys_ctrl_mode == ((uint8_T)ENC_PT_CTRL)) {
            *rty_ct_ctrl_mode = ((uint8_T)POS_CTRL);
          }
        }
      } else {
        *rty_stm_state = ((uint8_T)STM_IDLE);
      }
      break;

     case mmcs_s2f_IN_IF_RUN:
      {
        if (rtu_motor_start == 0) {
          localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_ANY_STOP;
          *rty_stm_state = ((uint8_T)STM_ANY_STOP);
        } else {
          boolean_T out;
          out = ((rtu_sys_ctrl_mode == ((uint8_T)STO_ST_CTRL)) &&
                 ((localDW->temporalCounter_i1 << 1) >= ((uint16_T)
                   IF_ACC_DURATION)) && localB->LogicalOperator1_o);
          if (out) {
            *rty_ct_ctrl_mode = ((uint8_T)SPD_CTRL);
            localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_SWITCH;
            *rty_stm_state = ((uint8_T)STM_SWITCH);
          } else {
            *rty_stm_state = ((uint8_T)STM_IFRUN);
          }
        }
      }
      break;

     case mmcs_s2f_IN_INIT:
      localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_IDLE;
      *rty_stm_state = ((uint8_T)STM_IDLE);
      break;

     case mmcs_s2f_IN_PREPARE:
      if (localDW->temporalCounter_i1 >= 1U) {
        *rty_ct_ctrl_mode = ((uint8_T)TORQ_CTRL);
        if (rtu_sys_ctrl_mode == ((uint8_T)HALL_ST_CTRL)) {
          localDW->align_comp = 1U;
        }

        if (localDW->align_comp == 1) {
          if ((rtu_sys_ctrl_mode == ((uint8_T)ENC_ST_CTRL)) ||
              (rtu_sys_ctrl_mode == ((uint8_T)HALL_ST_CTRL))) {
            *rty_ct_ctrl_mode = ((uint8_T)SPD_CTRL);
          } else if (rtu_sys_ctrl_mode == ((uint8_T)ENC_PT_CTRL)) {
            *rty_ct_ctrl_mode = ((uint8_T)POS_CTRL);
          }
        }

        localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_START;
        *rty_stm_state = ((uint8_T)STM_START);
      } else {
        *rty_stm_state = ((uint8_T)STM_PREPARE);
        *rty_ct_ctrl_mode = ((uint8_T)TORQ_CTRL);
        if (rtu_sys_ctrl_mode == ((uint8_T)HALL_ST_CTRL)) {
          localDW->align_comp = 1U;
        }

        if (localDW->align_comp == 1) {
          if ((rtu_sys_ctrl_mode == ((uint8_T)ENC_ST_CTRL)) ||
              (rtu_sys_ctrl_mode == ((uint8_T)HALL_ST_CTRL))) {
            *rty_ct_ctrl_mode = ((uint8_T)SPD_CTRL);
          } else if (rtu_sys_ctrl_mode == ((uint8_T)ENC_PT_CTRL)) {
            *rty_ct_ctrl_mode = ((uint8_T)POS_CTRL);
          }
        }
      }
      break;

     case mmcs_s2f_IN_PT_RUN:
      if (rtu_motor_start == 0) {
        localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_ANY_STOP;
        *rty_stm_state = ((uint8_T)STM_ANY_STOP);
      } else {
        *rty_stm_state = ((uint8_T)STM_PTRUN);
      }
      break;

     case mmcs_s2f_IN_START:
      {
        if (*rty_ct_ctrl_mode == ((uint8_T)SPD_CTRL)) {
          localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_ST_RUN;
          *rty_stm_state = ((uint8_T)STM_STRUN);
        } else if (localDW->align_comp == 0) {
          localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_ALIGN;
          localDW->temporalCounter_i1 = 0U;
          *rty_stm_state = ((uint8_T)STM_ALIGN);
        } else {
          boolean_T out;
          out = ((localDW->align_comp != 0) && (*rty_ct_ctrl_mode == ((uint8_T)
                   TORQ_CTRL)));
          if (out) {
            localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_IF_RUN;
            localDW->temporalCounter_i1 = 0U;
            *rty_stm_state = ((uint8_T)STM_IFRUN);
          } else if (*rty_ct_ctrl_mode == ((uint8_T)POS_CTRL)) {
            localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_PT_RUN;
            *rty_stm_state = ((uint8_T)STM_PTRUN);
          } else {
            *rty_stm_state = ((uint8_T)STM_START);
          }
        }
      }
      break;

     case mmcs_s2f_IN_STOP:
      if (localDW->temporalCounter_i1 >= 50U) {
        localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_STOP_IDLE;
        localDW->temporalCounter_i1 = 0U;
        *rty_stm_state = ((uint8_T)STM_STOP_IDLE);
      } else {
        *rty_stm_state = ((uint8_T)STM_STOP);
      }
      break;

     case mmcs_s2f_IN_STOP_IDLE:
      if (localDW->temporalCounter_i1 >= 50U) {
        localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_IDLE;
        *rty_stm_state = ((uint8_T)STM_IDLE);
      } else {
        *rty_stm_state = ((uint8_T)STM_STOP_IDLE);
      }
      break;

     case mmcs_s2f_IN_ST_RUN:
      if (rtu_motor_start == 0) {
        if (rtu_sys_ctrl_mode == ((uint8_T)STO_ST_CTRL)) {
          localDW->align_comp = 0U;
        }

        localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_ANY_STOP;
        *rty_stm_state = ((uint8_T)STM_ANY_STOP);
      } else {
        *rty_stm_state = ((uint8_T)STM_STRUN);
      }
      break;

     default:
      /* case IN_SWITCH: */
      localDW->is_c3_mmcs_s2f = mmcs_s2f_IN_ST_RUN;
      *rty_stm_state = ((uint8_T)STM_STRUN);
      break;
    }
  }

  /* End of Chart: '<S4>/Chart1' */

  /* RelationalOperator: '<S241>/Compare' incorporates:
   *  Constant: '<S241>/Constant'
   */
  localB->Compare_f = (*rty_stm_state == ((uint8_T)STM_INIT));

  /* If: '<S179>/If1' */
  if (localB->Compare_f) {
    /* Outputs for IfAction SubSystem: '<S179>/PosCtrlInit' incorporates:
     *  ActionPort: '<S242>/Action Port'
     */
    /* S-Function (sfun_PosCtrlInit): '<S242>/sfun_PosCtrlInit' */
    PosCtrlInit(&localB->sfun_PosCtrlInit);

    /* DataStoreWrite: '<S242>/Data Store Write' */
    localDW->pos_ctrl = localB->sfun_PosCtrlInit;

    /* End of Outputs for SubSystem: '<S179>/PosCtrlInit' */
  }

  /* End of If: '<S179>/If1' */

  /* RelationalOperator: '<S243>/Compare' incorporates:
   *  Constant: '<S243>/Constant'
   */
  localB->Compare_ej = (*rty_stm_state == ((uint8_T)STM_PTRUN));

  /* DataStoreRead: '<S180>/Data Store Read' */
  localB->DataStoreRead_g = localDW->pos_ctrl.final_angle;

  /* RelationalOperator: '<S180>/Relational Operator' */
  localB->RelationalOperator = (localB->DataStoreRead_g != rtu_pos_ref);

  /* Logic: '<S180>/Logical Operator1' */
  localB->LogicalOperator1 = (localB->Compare_ej && localB->RelationalOperator);

  /* If: '<S180>/If' */
  if (localB->LogicalOperator1) {
    /* Outputs for IfAction SubSystem: '<S180>/PosCtrlPlan' incorporates:
     *  ActionPort: '<S244>/Action Port'
     */
    /* Product: '<S244>/Divide' incorporates:
     *  Constant: '<S244>/Constant2'
     */
    localB->Divide_e = (real32_T)rtu_pos_fed / RADTOS16_F;

    /* DataStoreRead: '<S244>/Data Store Read' */
    localB->DataStoreRead_c = localDW->pos_ctrl;

    /* S-Function (sfun_PosCtrPlan): '<S244>/sfun_PosCtrPlan' */
    localB->sfun_PosCtrPlan_o1 = PosCtrPlan(localB->Divide_e, rtu_pos_ref,
      rtu_duration, (PosCtrlHandle_t*)&localB->DataStoreRead_c,
      &localB->sfun_PosCtrPlan_o2);

    /* If: '<S244>/If' */
    if (localB->sfun_PosCtrPlan_o1 > 0) {
      /* Outputs for IfAction SubSystem: '<S244>/UpdatePosCtrl' incorporates:
       *  ActionPort: '<S245>/Action Port'
       */
      /* DataStoreWrite: '<S245>/Data Store Write' */
      localDW->pos_ctrl = localB->sfun_PosCtrPlan_o2;

      /* End of Outputs for SubSystem: '<S244>/UpdatePosCtrl' */
    }

    /* End of If: '<S244>/If' */
    /* End of Outputs for SubSystem: '<S180>/PosCtrlPlan' */
  }

  /* End of If: '<S180>/If' */

  /* RelationalOperator: '<S302>/Compare' incorporates:
   *  Constant: '<S302>/Constant'
   */
  localB->Compare_jy = (rtu_sys_ctrl_mode == ((uint8_T)ENC_PT_CTRL));

  /* UnitDelay: '<S182>/Unit Delay' */
  localB->UnitDelay = localDW->UnitDelay_DSTATE;

  /* RelationalOperator: '<S303>/Compare' incorporates:
   *  Constant: '<S303>/Constant'
   */
  localB->Compare_k1 = (localB->UnitDelay == ((uint8_T)ENC_ST_CTRL));

  /* Logic: '<S182>/Logical Operator' */
  localB->LogicalOperator = (localB->Compare_jy && localB->Compare_k1);

  /* RelationalOperator: '<S306>/Compare' incorporates:
   *  Constant: '<S306>/Constant'
   */
  localB->Compare_fi = (rtu_sys_ctrl_mode == ((uint8_T)ENC_PT_CTRL));

  /* RelationalOperator: '<S304>/Compare' incorporates:
   *  Constant: '<S304>/Constant'
   */
  localB->Compare_n = (*rty_stm_state == ((uint8_T)STM_START));

  /* UnitDelay: '<S182>/Unit Delay1' */
  localB->UnitDelay1 = localDW->UnitDelay1_DSTATE;

  /* RelationalOperator: '<S305>/Compare' incorporates:
   *  Constant: '<S305>/Constant'
   */
  localB->Compare_i = (localB->UnitDelay1 != ((uint8_T)STM_START));

  /* Logic: '<S182>/Logical Operator3' */
  localB->LogicalOperator3 = (localB->Compare_fi && localB->Compare_n &&
    localB->Compare_i);

  /* Logic: '<S182>/Logical Operator2' */
  localB->LogicalOperator2 = (localB->LogicalOperator ||
    localB->LogicalOperator3);

  /* If: '<S182>/If' */
  if (localB->LogicalOperator2) {
    /* Outputs for IfAction SubSystem: '<S182>/If Action Subsystem' incorporates:
     *  ActionPort: '<S307>/Action Port'
     */
    /* Product: '<S307>/Divide' incorporates:
     *  Constant: '<S307>/Constant2'
     */
    localB->Divide = (real32_T)rtu_pos_fed / RADTOS16_F;

    /* DataStoreWrite: '<S307>/Data Store Write1' incorporates:
     *  Constant: '<S307>/Constant'
     *  Constant: '<S307>/Constant1'
     */
    localDW->pos_ctrl.final_angle = localB->Divide;
    localDW->pos_ctrl.theta = localB->Divide;
    localDW->pos_ctrl.tc_sts = 0U;
    localDW->pos_ctrl.elapse_time = 0.0F;

    /* End of Outputs for SubSystem: '<S182>/If Action Subsystem' */
  }

  /* End of If: '<S182>/If' */

  /* SwitchCase: '<S4>/Switch Case' */
  switch (*rty_ct_ctrl_mode) {
   case 0:
    {
      int32_T u0;
      int32_T u1;
      int32_T u2;

      /* Outputs for IfAction SubSystem: '<S4>/TorqCtrl' incorporates:
       *  ActionPort: '<S183>/Action Port'
       */
      /* RelationalOperator: '<S310>/Compare' incorporates:
       *  Constant: '<S310>/Constant'
       */
      localB->Compare_e4 = (uint8_T)(*rty_stm_state == ((uint8_T)STM_START));

      /* DiscreteIntegrator: '<S314>/Discrete-Time Integrator1' */
      if ((localB->Compare_e4 != 0) || (localDW->DiscreteTimeIntegrator1_PrevRes
           != 0)) {
        localDW->DiscreteTimeIntegrator1_DSTATE = 0;
      }

      /* DiscreteIntegrator: '<S314>/Discrete-Time Integrator1' */
      localB->DiscreteTimeIntegrator1 = localDW->DiscreteTimeIntegrator1_DSTATE;

      /* Product: '<S314>/Product3' incorporates:
       *  Constant: '<S308>/Constant1'
       */
      localB->Product3 = ((int16_T)ALIGN_INIT_CURRENT) << 12;

      /* DiscreteIntegrator: '<S314>/Discrete-Time Integrator2' */
      if (localDW->DiscreteTimeIntegrator2_IC_LOAD != 0) {
        localDW->DiscreteTimeIntegrator2_DSTATE = localB->Product3;
      }

      if ((localB->Compare_e4 != 0) || (localDW->DiscreteTimeIntegrator2_PrevRes
           != 0)) {
        localDW->DiscreteTimeIntegrator2_DSTATE = localB->Product3;
      }

      /* DiscreteIntegrator: '<S314>/Discrete-Time Integrator2' */
      localB->DiscreteTimeIntegrator2 = localDW->DiscreteTimeIntegrator2_DSTATE;

      /* Sum: '<S314>/Subtract' incorporates:
       *  Constant: '<S308>/Constant1'
       *  Constant: '<S308>/Constant5'
       */
      localB->Subtract = (int16_T)(((int16_T)ALIGN_FINAL_CURRENT) - ((int16_T)
        ALIGN_INIT_CURRENT));

      /* Product: '<S314>/Product' */
      localB->Product = localB->Subtract << 12;

      /* Product: '<S314>/Divide' incorporates:
       *  Constant: '<S308>/Constant7'
       */
      u0 = ((uint16_T)ALIGN_DURATION);
      u1 = localB->Product;

      /* Product: '<S314>/Divide' */
      localB->Divide_i = u0 == 0 ? u1 >= 0 ? MAX_int32_T : MIN_int32_T : u1 / u0;

      /* Product: '<S314>/Divide1' */
      localB->Divide1 = localB->DiscreteTimeIntegrator2 / 4096;

      /* Product: '<S314>/Product4' incorporates:
       *  Constant: '<S308>/Constant9'
       */
      localB->Product4 = ((int16_T)ALIGN_FINAL_SPEED) << 12;

      /* Product: '<S314>/Divide4' incorporates:
       *  Constant: '<S308>/Constant7'
       */
      u0 = ((uint16_T)ALIGN_DURATION);
      u1 = localB->Product4;

      /* Product: '<S314>/Divide4' */
      localB->Divide4 = u0 == 0 ? u1 >= 0 ? MAX_int32_T : MIN_int32_T : u1 / u0;

      /* Product: '<S314>/Divide5' */
      localB->Divide5 = localB->DiscreteTimeIntegrator1 / 4096;

      /* Product: '<S314>/Product1' incorporates:
       *  Constant: '<S314>/Constant1'
       */
      localB->Product1 = localB->Divide_i * ((uint16_T)STOMS);

      /* Product: '<S314>/Product2' incorporates:
       *  Constant: '<S314>/Constant1'
       */
      localB->Product2 = localB->Divide4 * ((uint16_T)STOMS);

      /* Saturate: '<S314>/Saturation1' */
      u0 = localB->Divide1;
      u1 = ((int16_T)IF_FINAL_CURRENT_LOL);
      u2 = ((int16_T)IF_FINAL_CURRENT_UPL);
      if (u0 > u2) {
        u0 = u2;
      } else if (u0 < u1) {
        u0 = u1;
      }

      /* Saturate: '<S314>/Saturation1' */
      localB->Saturation1 = (int16_T)u0;

      /* Saturate: '<S314>/Saturation2' */
      u0 = localB->Divide5;
      u1 = ((int16_T)IF_FINAL_SPEED_LOL);
      u2 = ((int16_T)IF_FINAL_SPEED_UPL);
      if (u0 > u2) {
        u0 = u2;
      } else if (u0 < u1) {
        u0 = u1;
      }

      /* Saturate: '<S314>/Saturation2' */
      localB->Saturation2 = (int16_T)u0;

      /* Switch: '<S312>/Switch' */
      if (rtu_spd_ref >= 0) {
        /* Switch: '<S312>/Switch' incorporates:
         *  Constant: '<S312>/Constant1'
         *  Constant: '<S312>/Constant5'
         *  Constant: '<S312>/Constant9'
         */
        localB->Switch_dc[0] = ((int16_T)IF_INIT_CURRENT);
        localB->Switch_dc[1] = ((int16_T)IF_FINAL_CURRENT);
        localB->Switch_dc[2] = ((int16_T)IF_FINAL_SPEED);
      } else {
        /* Gain: '<S312>/Gain' incorporates:
         *  Constant: '<S312>/Constant1'
         *  Constant: '<S312>/Constant5'
         *  Constant: '<S312>/Constant9'
         */
        localB->Gain[0] = (int16_T)-((int16_T)IF_INIT_CURRENT);
        localB->Gain[1] = (int16_T)-((int16_T)IF_FINAL_CURRENT);
        localB->Gain[2] = (int16_T)-((int16_T)IF_FINAL_SPEED);

        /* Switch: '<S312>/Switch' */
        localB->Switch_dc[0] = localB->Gain[0];
        localB->Switch_dc[1] = localB->Gain[1];
        localB->Switch_dc[2] = localB->Gain[2];
      }

      /* End of Switch: '<S312>/Switch' */

      /* Product: '<S315>/Product3' */
      localB->Product3_f = localB->Switch_dc[0] << 12;

      /* DiscreteIntegrator: '<S315>/Discrete-Time Integrator2' */
      if (localDW->DiscreteTimeIntegrator2_IC_LO_a != 0) {
        localDW->DiscreteTimeIntegrator2_DSTAT_m = localB->Product3_f;
      }

      if ((localB->Compare_e4 != 0) || (localDW->DiscreteTimeIntegrator2_PrevR_c
           != 0)) {
        localDW->DiscreteTimeIntegrator2_DSTAT_m = localB->Product3_f;
      }

      /* DiscreteIntegrator: '<S315>/Discrete-Time Integrator2' */
      localB->DiscreteTimeIntegrator2_c =
        localDW->DiscreteTimeIntegrator2_DSTAT_m;

      /* Product: '<S315>/Divide1' */
      localB->Divide1_n = localB->DiscreteTimeIntegrator2_c / 4096;

      /* Saturate: '<S315>/Saturation1' */
      u0 = localB->Divide1_n;
      u1 = ((int16_T)IF_FINAL_CURRENT_LOL);
      u2 = ((int16_T)IF_FINAL_CURRENT_UPL);
      if (u0 > u2) {
        u0 = u2;
      } else if (u0 < u1) {
        u0 = u1;
      }

      /* Saturate: '<S315>/Saturation1' */
      localB->Saturation1_o = (int16_T)u0;

      /* DiscreteIntegrator: '<S315>/Discrete-Time Integrator1' */
      if ((localB->Compare_e4 != 0) || (localDW->DiscreteTimeIntegrator1_PrevR_o
           != 0)) {
        localDW->DiscreteTimeIntegrator1_DSTAT_i = 0;
      }

      /* DiscreteIntegrator: '<S315>/Discrete-Time Integrator1' */
      localB->DiscreteTimeIntegrator1_e =
        localDW->DiscreteTimeIntegrator1_DSTAT_i;

      /* Product: '<S315>/Divide5' */
      localB->Divide5_l = localB->DiscreteTimeIntegrator1_e / 4096;

      /* Saturate: '<S315>/Saturation2' */
      u0 = localB->Divide5_l;
      u1 = ((int16_T)IF_FINAL_SPEED_LOL);
      u2 = ((int16_T)IF_FINAL_SPEED_UPL);
      if (u0 > u2) {
        u0 = u2;
      } else if (u0 < u1) {
        u0 = u1;
      }

      /* Saturate: '<S315>/Saturation2' */
      localB->Saturation2_d = (int16_T)u0;

      /* SwitchCase: '<S183>/Switch Case' incorporates:
       *  Constant: '<S308>/Constant6'
       *  Constant: '<S312>/Constant6'
       *  Inport: '<S309>/id_ref_i'
       *  Inport: '<S309>/iq_ref_i'
       *  Inport: '<S309>/spd_ramp_i'
       *  Inport: '<S313>/id_ref_i'
       *  Inport: '<S313>/iq_ref_i'
       *  Inport: '<S313>/spd_ramp_i'
       */
      switch (*rty_stm_state) {
       case 4:
        /* Outputs for IfAction SubSystem: '<S183>/AligntAction' incorporates:
         *  ActionPort: '<S309>/Action Port'
         */
        *rty_idq_ref = localB->Saturation1;
        *rty_idq_ref_l = 0;
        *rty_spd_ramp = localB->Saturation2;

        /* End of Outputs for SubSystem: '<S183>/AligntAction' */
        break;

       case 5:
        /* Outputs for IfAction SubSystem: '<S183>/IFStart' incorporates:
         *  ActionPort: '<S313>/Action Port'
         */
        *rty_idq_ref = 0;
        *rty_idq_ref_l = localB->Saturation1_o;
        *rty_spd_ramp = localB->Saturation2_d;

        /* End of Outputs for SubSystem: '<S183>/IFStart' */
        break;

       default:
        /* Outputs for IfAction SubSystem: '<S183>/DefAction' incorporates:
         *  ActionPort: '<S311>/Action Port'
         */
        /* SignalConversion generated from: '<S311>/id_ref' incorporates:
         *  Constant: '<S311>/Constant'
         */
        *rty_idq_ref = 0;

        /* SignalConversion generated from: '<S311>/iq_ref' incorporates:
         *  Constant: '<S311>/Constant1'
         */
        *rty_idq_ref_l = 0;

        /* SignalConversion generated from: '<S311>/spd_ramp' incorporates:
         *  Constant: '<S311>/Constant2'
         */
        *rty_spd_ramp = 0;

        /* End of Outputs for SubSystem: '<S183>/DefAction' */
        break;
      }

      /* End of SwitchCase: '<S183>/Switch Case' */

      /* Sum: '<S315>/Subtract' */
      localB->Subtract_c = (int16_T)(localB->Switch_dc[1] - localB->Switch_dc[0]);

      /* Product: '<S315>/Product' */
      localB->Product_e = localB->Subtract_c << 12;

      /* Product: '<S315>/Divide' incorporates:
       *  Constant: '<S312>/Constant7'
       */
      u0 = ((uint16_T)IF_ACC_DURATION);
      u1 = localB->Product_e;

      /* Product: '<S315>/Divide' */
      localB->Divide_g = u0 == 0 ? u1 >= 0 ? MAX_int32_T : MIN_int32_T : u1 / u0;

      /* Product: '<S315>/Product4' */
      localB->Product4_g = localB->Switch_dc[2] << 12;

      /* Product: '<S315>/Divide4' incorporates:
       *  Constant: '<S312>/Constant7'
       */
      u0 = ((uint16_T)IF_ACC_DURATION);
      u1 = localB->Product4_g;

      /* Product: '<S315>/Divide4' */
      localB->Divide4_k = u0 == 0 ? u1 >= 0 ? MAX_int32_T : MIN_int32_T : u1 /
        u0;

      /* Product: '<S315>/Product1' incorporates:
       *  Constant: '<S315>/Constant1'
       */
      localB->Product1_j = localB->Divide_g * ((uint16_T)STOMS);

      /* Product: '<S315>/Product2' incorporates:
       *  Constant: '<S315>/Constant1'
       */
      localB->Product2_i = localB->Divide4_k * ((uint16_T)STOMS);

      /* Update for DiscreteIntegrator: '<S314>/Discrete-Time Integrator1' */
      localDW->DiscreteTimeIntegrator1_DSTATE += mul_s32_hiSR_zero(274877907,
        localB->Product2, 5U);
      localDW->DiscreteTimeIntegrator1_PrevRes = (int8_T)(localB->Compare_e4 > 0);

      /* Update for DiscreteIntegrator: '<S314>/Discrete-Time Integrator2' */
      localDW->DiscreteTimeIntegrator2_IC_LOAD = 0U;
      localDW->DiscreteTimeIntegrator2_DSTATE += mul_s32_hiSR_zero(274877907,
        localB->Product1, 5U);
      localDW->DiscreteTimeIntegrator2_PrevRes = (int8_T)(localB->Compare_e4 > 0);

      /* Update for DiscreteIntegrator: '<S315>/Discrete-Time Integrator2' */
      localDW->DiscreteTimeIntegrator2_IC_LO_a = 0U;
      localDW->DiscreteTimeIntegrator2_DSTAT_m += mul_s32_hiSR_zero(274877907,
        localB->Product1_j, 5U);
      localDW->DiscreteTimeIntegrator2_PrevR_c = (int8_T)(localB->Compare_e4 > 0);

      /* Update for DiscreteIntegrator: '<S315>/Discrete-Time Integrator1' */
      localDW->DiscreteTimeIntegrator1_DSTAT_i += mul_s32_hiSR_zero(274877907,
        localB->Product2_i, 5U);
      localDW->DiscreteTimeIntegrator1_PrevR_o = (int8_T)(localB->Compare_e4 > 0);

      /* End of Outputs for SubSystem: '<S4>/TorqCtrl' */
    }
    break;

   case 1:
    {
      int32_T u0;
      int32_T u1;

      /* Outputs for IfAction SubSystem: '<S4>/SpdCtrl' incorporates:
       *  ActionPort: '<S181>/Action Port'
       */
      /* RelationalOperator: '<S246>/Compare' incorporates:
       *  Constant: '<S246>/Constant'
       */
      localB->Compare_e = (uint8_T)(*rty_stm_state == ((uint8_T)STM_SWITCH));

      /* RelationalOperator: '<S247>/Compare' incorporates:
       *  Constant: '<S247>/Constant'
       */
      localB->Compare_p = (uint8_T)(*rty_stm_state == ((uint8_T)STM_SWITCH));

      /* RelationalOperator: '<S248>/Compare' incorporates:
       *  Constant: '<S248>/Constant'
       */
      localB->Compare_j = (uint8_T)(*rty_stm_state == ((uint8_T)STM_STRUN));

      /* RelationalOperator: '<S249>/Compare' incorporates:
       *  Constant: '<S249>/Constant'
       */
      localB->Compare_pv = (uint8_T)(*rty_stm_state == ((uint8_T)STM_START));

      /* Logic: '<S181>/Logical Operator1' */
      localB->LogicalOperator1_j = ((localB->Compare_j != 0) ||
        (localB->Compare_p != 0));

      /* Logic: '<S181>/Logical Operator2' */
      localB->LogicalOperator2_f = ((localB->Compare_pv != 0) ||
        (localB->Compare_e != 0));

      /* SignalConversion generated from: '<S181>/id_ref' incorporates:
       *  Constant: '<S250>/Constant6'
       */
      *rty_idq_ref = 0;

      /* Switch: '<S181>/Switch' */
      if (localB->LogicalOperator1_j) {
        /* Switch: '<S181>/Switch' */
        localB->Switch_g = rtu_spd_ref;
      } else {
        /* Switch: '<S181>/Switch' incorporates:
         *  Constant: '<S181>/Constant'
         */
        localB->Switch_g = 0;
      }

      /* End of Switch: '<S181>/Switch' */

      /* SignalConversion generated from: '<S181>/spd_ramp' */
      *rty_spd_ramp = localB->Switch_g;

      /* Sum: '<S250>/Sum' */
      localB->Sum_a = (int16_T)(localB->Switch_g - rtu_spd_fed);

      /* Gain: '<S290>/Proportional Gain' */
      localB->ProportionalGain = mul_s32_loSR_sat_zero(PI_KP_SPD, localB->Sum_a,
        2U);

      /* DiscreteIntegrator: '<S285>/Integrator' */
      if (localB->LogicalOperator2_f || (localDW->Integrator_PrevResetState_h !=
           0)) {
        localDW->Integrator_DSTATE = 0;
      }

      /* DiscreteIntegrator: '<S285>/Integrator' */
      localB->Integrator_m = localDW->Integrator_DSTATE;

      /* Sum: '<S294>/Sum' incorporates:
       *  DiscreteIntegrator: '<S285>/Integrator'
       *  Gain: '<S290>/Proportional Gain'
       */
      u0 = localB->ProportionalGain;
      u1 = localB->Integrator_m;
      if ((u0 < 0) && (u1 < MIN_int32_T - u0)) {
        u0 = MIN_int32_T;
      } else if ((u0 > 0) && (u1 > MAX_int32_T - u0)) {
        u0 = MAX_int32_T;
      } else {
        u0 += u1;
      }

      /* Sum: '<S294>/Sum' */
      localB->Sum_c = ((u0 < 0 ? 16383 : 0) + u0) >> 14;

      /* Saturate: '<S292>/Saturation' */
      u0 = localB->Sum_c;
      if (u0 > 32767) {
        /* Saturate: '<S292>/Saturation' */
        localB->Saturation_c = 32767;
      } else if (u0 < -32768) {
        /* Saturate: '<S292>/Saturation' */
        localB->Saturation_c = -32768;
      } else {
        /* Saturate: '<S292>/Saturation' */
        localB->Saturation_c = u0;
      }

      /* End of Saturate: '<S292>/Saturation' */

      /* DataTypeConversion: '<S250>/Data Type Conversion' */
      *rty_idq_ref_l = (int16_T)localB->Saturation_c;

      /* Gain: '<S276>/ZeroGain' */
      localB->ZeroGain_m = 0;

      /* DeadZone: '<S278>/DeadZone' */
      if (localB->Sum_c > 32767) {
        u0 = localB->Sum_c;
        if (u0 < -2147450881) {
          u0 = MIN_int32_T;
        } else {
          u0 -= 32767;
        }

        /* DeadZone: '<S278>/DeadZone' */
        localB->DeadZone_j = u0;
      } else if (localB->Sum_c >= -32768) {
        /* DeadZone: '<S278>/DeadZone' */
        localB->DeadZone_j = 0;
      } else {
        u0 = localB->Sum_c;
        if (u0 > 2147450879) {
          u0 = MAX_int32_T;
        } else {
          u0 -= -32768;
        }

        /* DeadZone: '<S278>/DeadZone' */
        localB->DeadZone_j = u0;
      }

      /* End of DeadZone: '<S278>/DeadZone' */

      /* RelationalOperator: '<S276>/NotEqual' */
      localB->NotEqual_f = (localB->ZeroGain_m != localB->DeadZone_j);

      /* Signum: '<S276>/SignPreSat' */
      u0 = localB->DeadZone_j;
      if (u0 < 0) {
        /* Signum: '<S276>/SignPreSat' */
        localB->SignPreSat_c = -1;
      } else {
        /* Signum: '<S276>/SignPreSat' */
        localB->SignPreSat_c = (u0 > 0);
      }

      /* End of Signum: '<S276>/SignPreSat' */

      /* DataTypeConversion: '<S276>/DataTypeConv1' */
      u0 = localB->SignPreSat_c;
      if (u0 > 127) {
        u0 = 127;
      } else if (u0 < -128) {
        u0 = -128;
      }

      /* DataTypeConversion: '<S276>/DataTypeConv1' */
      localB->DataTypeConv1_f = (int8_T)u0;

      /* Gain: '<S282>/Integral Gain' */
      localB->IntegralGain = mul_s32_loSR_sat_zero(PI_KI_SPD, localB->Sum_a, 2U);

      /* Signum: '<S276>/SignPreIntegrator' incorporates:
       *  Gain: '<S282>/Integral Gain'
       */
      u0 = localB->IntegralGain;
      if (u0 < 0) {
        /* Signum: '<S276>/SignPreIntegrator' */
        localB->SignPreIntegrator_f = -1;
      } else {
        /* Signum: '<S276>/SignPreIntegrator' */
        localB->SignPreIntegrator_f = (u0 > 0);
      }

      /* End of Signum: '<S276>/SignPreIntegrator' */

      /* DataTypeConversion: '<S276>/DataTypeConv2' */
      u0 = localB->SignPreIntegrator_f;
      if (u0 > 127) {
        u0 = 127;
      } else if (u0 < -128) {
        u0 = -128;
      }

      /* DataTypeConversion: '<S276>/DataTypeConv2' */
      localB->DataTypeConv2_c = (int8_T)u0;

      /* RelationalOperator: '<S276>/Equal1' */
      localB->Equal1_g = (localB->DataTypeConv1_f == localB->DataTypeConv2_c);

      /* Logic: '<S276>/AND3' */
      localB->AND3_g = (localB->NotEqual_f && localB->Equal1_g);

      /* Switch: '<S276>/Switch' */
      if (localB->AND3_g) {
        /* Switch: '<S276>/Switch' incorporates:
         *  Constant: '<S276>/Constant1'
         */
        localB->Switch = 0;
      } else {
        /* Switch: '<S276>/Switch' incorporates:
         *  Gain: '<S282>/Integral Gain'
         */
        localB->Switch = localB->IntegralGain;
      }

      /* End of Switch: '<S276>/Switch' */

      /* Update for DiscreteIntegrator: '<S285>/Integrator' incorporates:
       *  Switch: '<S276>/Switch'
       */
      u0 = localDW->Integrator_DSTATE;
      u1 = mul_s32_hiSR_zero(274877907, localB->Switch, 5U);
      if ((u0 < 0) && (u1 < MIN_int32_T - u0)) {
        u0 = MIN_int32_T;
      } else if ((u0 > 0) && (u1 > MAX_int32_T - u0)) {
        u0 = MAX_int32_T;
      } else {
        u0 += u1;
      }

      localDW->Integrator_DSTATE = u0;
      localDW->Integrator_PrevResetState_h = (int8_T)localB->LogicalOperator2_f;

      /* End of Update for DiscreteIntegrator: '<S285>/Integrator' */
      /* End of Outputs for SubSystem: '<S4>/SpdCtrl' */
    }
    break;

   case 2:
    {
      int32_T u0;

      /* Outputs for IfAction SubSystem: '<S4>/PosCtrl' incorporates:
       *  ActionPort: '<S178>/Action Port'
       */
      /* DataStoreRead: '<S178>/Data Store Read' */
      localB->DataStoreRead = localDW->pos_ctrl;

      /* S-Function (sfun_PosCtrPlanExec): '<S178>/sfun_PosCtrPlanExec' */
      localB->sfun_PosCtrPlanExec_o1 = PosCtrPlanExec((PosCtrlHandle_t*)
        &localB->DataStoreRead, &localB->sfun_PosCtrPlanExec_o2);

      /* If: '<S178>/If' */
      if (localB->sfun_PosCtrPlanExec_o1 > 0) {
        /* Outputs for IfAction SubSystem: '<S178>/If Action Subsystem' incorporates:
         *  ActionPort: '<S188>/Action Port'
         */
        /* DataStoreWrite: '<S188>/Data Store Write' */
        localDW->pos_ctrl = localB->sfun_PosCtrPlanExec_o2;

        /* End of Outputs for SubSystem: '<S178>/If Action Subsystem' */
      }

      /* End of If: '<S178>/If' */

      /* RelationalOperator: '<S186>/Compare' incorporates:
       *  Constant: '<S186>/Constant'
       */
      localB->Compare = (uint8_T)(*rty_stm_state == ((uint8_T)STM_START));

      /* RelationalOperator: '<S187>/Compare' incorporates:
       *  Constant: '<S187>/Constant'
       */
      localB->Compare_k = (uint8_T)(*rty_stm_state == ((uint8_T)STM_PTRUN));

      /* SignalConversion generated from: '<S178>/id_ref' incorporates:
       *  Constant: '<S189>/Constant6'
       */
      *rty_idq_ref = 0;

      /* Switch: '<S178>/Switch' */
      if (localB->Compare_k > 0) {
        real32_T tmp;

        /* DataStoreRead: '<S178>/Data Store Read1' */
        localB->DataStoreRead1 = localDW->pos_ctrl.theta;

        /* Product: '<S178>/Product' incorporates:
         *  Constant: '<S178>/Constant2'
         */
        tmp = truncf(localB->DataStoreRead1 * RADTOS16_F);
        if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
          tmp = 0.0F;
        } else {
          tmp = fmodf(tmp, 4.2949673E+9F);
        }

        /* Product: '<S178>/Product' */
        localB->pos_ctrltheat = tmp < 0.0F ? -(int32_T)(uint32_T)-tmp : (int32_T)
          (uint32_T)tmp;

        /* Switch: '<S178>/Switch' */
        pos_ref_int = localB->pos_ctrltheat;
      } else {
        /* Switch: '<S178>/Switch' */
        pos_ref_int = rtu_pos_fed;
      }

      /* End of Switch: '<S178>/Switch' */

      /* Sum: '<S189>/Sum' */
      localB->Sum = pos_ref_int - rtu_pos_fed;

      /* Gain: '<S229>/Proportional Gain' */
      u0 = PI_KP_POS;
      if (u0 > 131071) {
        u0 = MAX_int32_T;
      } else if (u0 <= -131072) {
        u0 = MIN_int32_T;
      } else {
        u0 <<= 14;
      }

      /* Gain: '<S229>/Proportional Gain' */
      localB->ProportionalGain_g = mul_s32_loSR_zero(u0, localB->Sum, 30U);

      /* DiscreteIntegrator: '<S224>/Integrator' */
      if ((localB->Compare != 0) || (localDW->Integrator_PrevResetState != 0)) {
        localDW->Integrator_DSTATE_o = 0;
      }

      /* DiscreteIntegrator: '<S224>/Integrator' */
      localB->Integrator = localDW->Integrator_DSTATE_o;

      /* Sum: '<S233>/Sum' incorporates:
       *  DiscreteIntegrator: '<S224>/Integrator'
       */
      localB->Sum_d = localB->ProportionalGain_g + mul_s32_hiSR_zero
        (localB->Integrator, 274877907, 5U);

      /* Saturate: '<S231>/Saturation' */
      u0 = localB->Sum_d;
      if (u0 > 32767) {
        /* Saturate: '<S231>/Saturation' */
        localB->Saturation = 32767;
      } else if (u0 < -32768) {
        /* Saturate: '<S231>/Saturation' */
        localB->Saturation = -32768;
      } else {
        /* Saturate: '<S231>/Saturation' */
        localB->Saturation = u0;
      }

      /* End of Saturate: '<S231>/Saturation' */

      /* DataTypeConversion: '<S189>/Data Type Conversion' */
      *rty_idq_ref_l = (int16_T)localB->Saturation;

      /* Gain: '<S215>/ZeroGain' */
      localB->ZeroGain = 0;

      /* DeadZone: '<S217>/DeadZone' */
      if (localB->Sum_d > 32767) {
        /* DeadZone: '<S217>/DeadZone' */
        localB->DeadZone = localB->Sum_d - 32767;
      } else if (localB->Sum_d >= -32768) {
        /* DeadZone: '<S217>/DeadZone' */
        localB->DeadZone = 0;
      } else {
        /* DeadZone: '<S217>/DeadZone' */
        localB->DeadZone = localB->Sum_d + 32768;
      }

      /* End of DeadZone: '<S217>/DeadZone' */

      /* RelationalOperator: '<S215>/NotEqual' */
      localB->NotEqual = (localB->ZeroGain != localB->DeadZone);

      /* Signum: '<S215>/SignPreSat' */
      u0 = localB->DeadZone;
      if (u0 < 0) {
        /* Signum: '<S215>/SignPreSat' */
        localB->SignPreSat = -1;
      } else {
        /* Signum: '<S215>/SignPreSat' */
        localB->SignPreSat = (u0 > 0);
      }

      /* End of Signum: '<S215>/SignPreSat' */

      /* DataTypeConversion: '<S215>/DataTypeConv1' */
      localB->DataTypeConv1 = (int8_T)localB->SignPreSat;

      /* Gain: '<S221>/Integral Gain' */
      u0 = PI_KI_POS;
      if (u0 > 131071) {
        u0 = MAX_int32_T;
      } else if (u0 <= -131072) {
        u0 = MIN_int32_T;
      } else {
        u0 <<= 14;
      }

      /* Gain: '<S221>/Integral Gain' */
      localB->IntegralGain_f = mul_s32_loSR_zero(u0, localB->Sum, 30U);

      /* Signum: '<S215>/SignPreIntegrator' */
      u0 = localB->IntegralGain_f;
      if (u0 < 0) {
        /* Signum: '<S215>/SignPreIntegrator' */
        localB->SignPreIntegrator = -1;
      } else {
        /* Signum: '<S215>/SignPreIntegrator' */
        localB->SignPreIntegrator = (u0 > 0);
      }

      /* End of Signum: '<S215>/SignPreIntegrator' */

      /* DataTypeConversion: '<S215>/DataTypeConv2' */
      localB->DataTypeConv2 = (int8_T)localB->SignPreIntegrator;

      /* RelationalOperator: '<S215>/Equal1' */
      localB->Equal1 = (localB->DataTypeConv1 == localB->DataTypeConv2);

      /* Logic: '<S215>/AND3' */
      localB->AND3 = (localB->NotEqual && localB->Equal1);

      /* Switch: '<S215>/Switch' */
      if (localB->AND3) {
        /* Switch: '<S215>/Switch' incorporates:
         *  Constant: '<S215>/Constant1'
         */
        localB->Switch_d = 0;
      } else {
        /* Switch: '<S215>/Switch' */
        localB->Switch_d = localB->IntegralGain_f;
      }

      /* End of Switch: '<S215>/Switch' */

      /* SignalConversion generated from: '<S178>/spd_ramp' incorporates:
       *  Constant: '<S178>/Constant1'
       */
      *rty_spd_ramp = 0;

      /* Update for DiscreteIntegrator: '<S224>/Integrator' */
      localDW->Integrator_DSTATE_o += localB->Switch_d;
      localDW->Integrator_PrevResetState = (int8_T)(localB->Compare > 0);

      /* End of Outputs for SubSystem: '<S4>/PosCtrl' */
    }
    break;
  }

  /* End of SwitchCase: '<S4>/Switch Case' */

  /* Update for Atomic SubSystem: '<S4>/IsTransition' */
  /* Update for UnitDelay: '<S177>/Unit Delay1' */
  localDW->UnitDelay1_DSTATE_c = *rty_stm_state;

  /* End of Update for SubSystem: '<S4>/IsTransition' */

  /* Update for UnitDelay: '<S182>/Unit Delay' */
  localDW->UnitDelay_DSTATE = rtu_sys_ctrl_mode;

  /* Update for UnitDelay: '<S182>/Unit Delay1' */
  localDW->UnitDelay1_DSTATE = *rty_stm_state;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
