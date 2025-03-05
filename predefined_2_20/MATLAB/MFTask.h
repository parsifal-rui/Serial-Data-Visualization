/*
 * File: MFTask.h
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

#ifndef RTW_HEADER_MFTask_h_
#define RTW_HEADER_MFTask_h_
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
#include "rt_nonfinite.h"

/* Block signals for system '<Root>/MFTask' */
typedef struct {
  PosCtrlHandle_t DataStoreRead;       /* '<S178>/Data Store Read' */
  PosCtrlHandle_t sfun_PosCtrPlanExec_o2;/* '<S178>/sfun_PosCtrPlanExec' */
  PosCtrlHandle_t DataStoreRead_c;     /* '<S244>/Data Store Read' */
  PosCtrlHandle_t sfun_PosCtrPlan_o2;  /* '<S244>/sfun_PosCtrPlan' */
  PosCtrlHandle_t sfun_PosCtrlInit;    /* '<S242>/sfun_PosCtrlInit' */
  real32_T DataStoreRead_g;            /* '<S180>/Data Store Read' */
  real32_T Divide;                     /* '<S307>/Divide' */
  real32_T DataStoreRead1;             /* '<S178>/Data Store Read1' */
  real32_T Divide_e;                   /* '<S244>/Divide' */
  int32_T Integrator;                  /* '<S224>/Integrator' */
  int32_T ProportionalGain;            /* '<S290>/Proportional Gain' */
  int32_T Integrator_m;                /* '<S285>/Integrator' */
  int32_T IntegralGain;                /* '<S282>/Integral Gain' */
  int32_T Switch;                      /* '<S276>/Switch' */
  int32_T Sum;                         /* '<S189>/Sum' */
  int32_T ProportionalGain_g;          /* '<S229>/Proportional Gain' */
  int32_T Sum_d;                       /* '<S233>/Sum' */
  int32_T Saturation;                  /* '<S231>/Saturation' */
  int32_T ZeroGain;                    /* '<S215>/ZeroGain' */
  int32_T DeadZone;                    /* '<S217>/DeadZone' */
  int32_T SignPreSat;                  /* '<S215>/SignPreSat' */
  int32_T IntegralGain_f;              /* '<S221>/Integral Gain' */
  int32_T SignPreIntegrator;           /* '<S215>/SignPreIntegrator' */
  int32_T Switch_d;                    /* '<S215>/Switch' */
  int32_T pos_ctrltheat;               /* '<S178>/Product' */
  int32_T Sum_c;                       /* '<S294>/Sum' */
  int32_T Saturation_c;                /* '<S292>/Saturation' */
  int32_T ZeroGain_m;                  /* '<S276>/ZeroGain' */
  int32_T DeadZone_j;                  /* '<S278>/DeadZone' */
  int32_T SignPreSat_c;                /* '<S276>/SignPreSat' */
  int32_T SignPreIntegrator_f;         /* '<S276>/SignPreIntegrator' */
  int32_T DiscreteTimeIntegrator1;     /* '<S314>/Discrete-Time Integrator1' */
  int32_T Product3;                    /* '<S314>/Product3' */
  int32_T DiscreteTimeIntegrator2;     /* '<S314>/Discrete-Time Integrator2' */
  int32_T Product;                     /* '<S314>/Product' */
  int32_T Divide_i;                    /* '<S314>/Divide' */
  int32_T Divide1;                     /* '<S314>/Divide1' */
  int32_T Product4;                    /* '<S314>/Product4' */
  int32_T Divide4;                     /* '<S314>/Divide4' */
  int32_T Divide5;                     /* '<S314>/Divide5' */
  int32_T Product1;                    /* '<S314>/Product1' */
  int32_T Product2;                    /* '<S314>/Product2' */
  int32_T Product3_f;                  /* '<S315>/Product3' */
  int32_T DiscreteTimeIntegrator2_c;   /* '<S315>/Discrete-Time Integrator2' */
  int32_T Divide1_n;                   /* '<S315>/Divide1' */
  int32_T DiscreteTimeIntegrator1_e;   /* '<S315>/Discrete-Time Integrator1' */
  int32_T Divide5_l;                   /* '<S315>/Divide5' */
  int32_T Product_e;                   /* '<S315>/Product' */
  int32_T Divide_g;                    /* '<S315>/Divide' */
  int32_T Product4_g;                  /* '<S315>/Product4' */
  int32_T Divide4_k;                   /* '<S315>/Divide4' */
  int32_T Product1_j;                  /* '<S315>/Product1' */
  int32_T Product2_i;                  /* '<S315>/Product2' */
  int16_T Switch_g;                    /* '<S181>/Switch' */
  int16_T Sum_a;                       /* '<S250>/Sum' */
  int16_T Subtract;                    /* '<S314>/Subtract' */
  int16_T Saturation1;                 /* '<S314>/Saturation1' */
  int16_T Saturation2;                 /* '<S314>/Saturation2' */
  int16_T Switch_dc[3];                /* '<S312>/Switch' */
  int16_T Saturation1_o;               /* '<S315>/Saturation1' */
  int16_T Saturation2_d;               /* '<S315>/Saturation2' */
  int16_T Subtract_c;                  /* '<S315>/Subtract' */
  int16_T Gain[3];                     /* '<S312>/Gain' */
  int16_T Abs;                         /* '<S177>/Abs' */
  int16_T Abs_i;                       /* '<S185>/Abs' */
  int16_T Product_n;                   /* '<S185>/Product' */
  int16_T Divide_f;                    /* '<S185>/Divide' */
  int16_T Product1_a;                  /* '<S185>/Product1' */
  int16_T Divide1_b;                   /* '<S185>/Divide1' */
  uint8_T UnitDelay;                   /* '<S182>/Unit Delay' */
  uint8_T UnitDelay1;                  /* '<S182>/Unit Delay1' */
  uint8_T sfun_PosCtrPlanExec_o1;      /* '<S178>/sfun_PosCtrPlanExec' */
  uint8_T Compare;                     /* '<S186>/Compare' */
  uint8_T Compare_k;                   /* '<S187>/Compare' */
  uint8_T Compare_e;                   /* '<S246>/Compare' */
  uint8_T Compare_p;                   /* '<S247>/Compare' */
  uint8_T Compare_j;                   /* '<S248>/Compare' */
  uint8_T Compare_pv;                  /* '<S249>/Compare' */
  uint8_T Compare_e4;                  /* '<S310>/Compare' */
  uint8_T sfun_PosCtrPlan_o1;          /* '<S244>/sfun_PosCtrPlan' */
  uint8_T UnitDelay1_l;                /* '<S177>/Unit Delay1' */
  int8_T DataTypeConv1;                /* '<S215>/DataTypeConv1' */
  int8_T DataTypeConv2;                /* '<S215>/DataTypeConv2' */
  int8_T DataTypeConv1_f;              /* '<S276>/DataTypeConv1' */
  int8_T DataTypeConv2_c;              /* '<S276>/DataTypeConv2' */
  boolean_T Compare_f;                 /* '<S241>/Compare' */
  boolean_T Compare_ej;                /* '<S243>/Compare' */
  boolean_T RelationalOperator;        /* '<S180>/Relational Operator' */
  boolean_T LogicalOperator1;          /* '<S180>/Logical Operator1' */
  boolean_T Compare_jy;                /* '<S302>/Compare' */
  boolean_T Compare_k1;                /* '<S303>/Compare' */
  boolean_T LogicalOperator;           /* '<S182>/Logical Operator' */
  boolean_T Compare_fi;                /* '<S306>/Compare' */
  boolean_T Compare_n;                 /* '<S304>/Compare' */
  boolean_T Compare_i;                 /* '<S305>/Compare' */
  boolean_T LogicalOperator3;          /* '<S182>/Logical Operator3' */
  boolean_T LogicalOperator2;          /* '<S182>/Logical Operator2' */
  boolean_T NotEqual;                  /* '<S215>/NotEqual' */
  boolean_T Equal1;                    /* '<S215>/Equal1' */
  boolean_T AND3;                      /* '<S215>/AND3' */
  boolean_T LogicalOperator1_j;        /* '<S181>/Logical Operator1' */
  boolean_T LogicalOperator2_f;        /* '<S181>/Logical Operator2' */
  boolean_T NotEqual_f;                /* '<S276>/NotEqual' */
  boolean_T Equal1_g;                  /* '<S276>/Equal1' */
  boolean_T AND3_g;                    /* '<S276>/AND3' */
  boolean_T Compare_m;                 /* '<S184>/Compare' */
  boolean_T RelationalOperator_p;      /* '<S177>/Relational Operator' */
  boolean_T RelationalOperator1;       /* '<S177>/Relational Operator1' */
  boolean_T LogicalOperator_p;         /* '<S177>/Logical Operator' */
  boolean_T LogicalOperator1_o;        /* '<S177>/Logical Operator1' */
  boolean_T RelationalOperator_a;      /* '<S185>/Relational Operator' */
  boolean_T RelationalOperator1_p;     /* '<S185>/Relational Operator1' */
  boolean_T LogicalOperator_o;         /* '<S185>/Logical Operator' */
} B_MFTask_mmcs_s2f_T;

/* Block states (default storage) for system '<Root>/MFTask' */
typedef struct {
  PosCtrlHandle_t pos_ctrl;            /* '<S4>/Data Store Memory' */
  int32_T DiscreteTimeIntegrator1_DSTATE;/* '<S314>/Discrete-Time Integrator1' */
  int32_T DiscreteTimeIntegrator2_DSTATE;/* '<S314>/Discrete-Time Integrator2' */
  int32_T DiscreteTimeIntegrator2_DSTAT_m;/* '<S315>/Discrete-Time Integrator2' */
  int32_T DiscreteTimeIntegrator1_DSTAT_i;/* '<S315>/Discrete-Time Integrator1' */
  int32_T Integrator_DSTATE;           /* '<S285>/Integrator' */
  int32_T Integrator_DSTATE_o;         /* '<S224>/Integrator' */
  int32_T Sum_DWORK1;                  /* '<S233>/Sum' */
  int32_T Sum_DWORK1_f;                /* '<S294>/Sum' */
  uint16_T temporalCounter_i1;         /* '<S4>/Chart1' */
  uint8_T UnitDelay_DSTATE;            /* '<S182>/Unit Delay' */
  uint8_T UnitDelay1_DSTATE;           /* '<S182>/Unit Delay1' */
  uint8_T UnitDelay1_DSTATE_c;         /* '<S177>/Unit Delay1' */
  int8_T Integrator_PrevResetState;    /* '<S224>/Integrator' */
  int8_T Integrator_PrevResetState_h;  /* '<S285>/Integrator' */
  int8_T DiscreteTimeIntegrator1_PrevRes;/* '<S314>/Discrete-Time Integrator1' */
  int8_T DiscreteTimeIntegrator2_PrevRes;/* '<S314>/Discrete-Time Integrator2' */
  int8_T DiscreteTimeIntegrator2_PrevR_c;/* '<S315>/Discrete-Time Integrator2' */
  int8_T DiscreteTimeIntegrator1_PrevR_o;/* '<S315>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator2_IC_LOAD;/* '<S314>/Discrete-Time Integrator2' */
  uint8_T DiscreteTimeIntegrator2_IC_LO_a;/* '<S315>/Discrete-Time Integrator2' */
  uint8_T is_active_c3_mmcs_s2f;       /* '<S4>/Chart1' */
  uint8_T is_c3_mmcs_s2f;              /* '<S4>/Chart1' */
  uint8_T align_comp;                  /* '<S4>/Chart1' */
} DW_MFTask_mmcs_s2f_T;

extern void mmcs_s2f_MFTask_Init(uint8_T *rty_ct_ctrl_mode, uint8_T
  *rty_stm_state, int16_T *rty_idq_ref, int16_T *rty_idq_ref_l, int16_T
  *rty_spd_ramp, DW_MFTask_mmcs_s2f_T *localDW);
extern void mmcs_s2f_MFTask(uint8_T rtu_sys_ctrl_mode, uint8_T rtu_motor_start,
  int16_T rtu_spd_ref, int16_T rtu_spd_fed, real32_T rtu_pos_ref, real32_T
  rtu_duration, int32_T rtu_pos_fed, uint8_T *rty_ct_ctrl_mode, uint8_T
  *rty_stm_state, int16_T *rty_idq_ref, int16_T *rty_idq_ref_l, int16_T
  *rty_spd_ramp, B_MFTask_mmcs_s2f_T *localB, DW_MFTask_mmcs_s2f_T *localDW);

#endif                                 /* RTW_HEADER_MFTask_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
