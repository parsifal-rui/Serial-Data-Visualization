/*
 * File: model_param.h
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

#ifndef RTW_HEADER_model_param_h_
#define RTW_HEADER_model_param_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#include "mmcs_s2f_types.h"

/* Exported data define */

/* Definition for custom storage class: Define */
#define ALIGN_DURATION                 700U                      /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S308>/Constant7'
                                                                  */
#define ALIGN_FINAL_CURRENT            4916                      /* Referenced by: '<S308>/Constant5' */
#define ALIGN_FINAL_SPEED              0                         /* Referenced by: '<S308>/Constant9' */
#define ALIGN_INIT_CURRENT             3277                      /* Referenced by: '<S308>/Constant1' */
#define ALIGN_THETA                    2731                      /* Referenced by: '<S11>/Constant3' */
#define DIVSQRT_3                      18918U                    /* Referenced by: '<S18>/Gain4' */
#define ENC_PT_CTRL                    4U                        /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S302>/Constant'
                                                                  * '<S306>/Constant'
                                                                  * '<S12>/Constant'
                                                                  */
#define ENC_PULSE_NUM                  10000U                    /* Referenced by: '<S16>/Constant7' */
#define ENC_ST_CTRL                    2U                        /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S303>/Constant'
                                                                  * '<S14>/Constant'
                                                                  */
#define HALL_ST_CTRL                   5U                        /* Referenced by: '<S4>/Chart1' */
#define IF_ACC_DURATION                1500U                     /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S312>/Constant7'
                                                                  */
#define IF_CTRL                        1U                        /* Referenced by: '<S4>/Chart1' */
#define IF_FINAL_CURRENT               4916                      /* Referenced by: '<S312>/Constant5' */
#define IF_FINAL_CURRENT_LOL           -4916                     /* Referenced by:
                                                                  * '<S314>/Saturation1'
                                                                  * '<S315>/Saturation1'
                                                                  */
#define IF_FINAL_CURRENT_UPL           4916                      /* Referenced by:
                                                                  * '<S314>/Saturation1'
                                                                  * '<S315>/Saturation1'
                                                                  */
#define IF_FINAL_SPEED                 600                       /* Referenced by:
                                                                  * '<S184>/Constant'
                                                                  * '<S185>/Constant1'
                                                                  * '<S312>/Constant9'
                                                                  */
#define IF_FINAL_SPEED_LOL             -600                      /* Referenced by:
                                                                  * '<S314>/Saturation2'
                                                                  * '<S315>/Saturation2'
                                                                  */
#define IF_FINAL_SPEED_UPL             600                       /* Referenced by:
                                                                  * '<S314>/Saturation2'
                                                                  * '<S315>/Saturation2'
                                                                  */
#define IF_INIT_CURRENT                3277                      /* Referenced by: '<S312>/Constant1' */
#define MOTOR_PN                       5U                        /* Referenced by:
                                                                  * '<S122>/Constant'
                                                                  * '<S15>/Gain5'
                                                                  */
#define MOTOR_TYPE                     3U                        /* Referenced by: '<S4>/Chart1' */
#define MOTOR_TYPE_JSF630              21U                       /* Referenced by: '<S4>/Chart1' */
#define MOTOR_TYPE_TB2P                11U                       /* Referenced by: '<S4>/Chart1' */
#define MOTOR_TYPE_TG5P60              3U                        /* Referenced by: '<S4>/Chart1' */
#define PI_KI_PLL                      983                       /* Referenced by: '<S156>/Integral Gain' */
#define PI_KI_POS                      65536                     /* Referenced by: '<S221>/Integral Gain' */
#define PI_KI_SPD                      655360                    /* Referenced by: '<S282>/Integral Gain' */
#define PI_KI_TQ                       1966080                   /* Referenced by:
                                                                  * '<S52>/Integral Gain'
                                                                  * '<S102>/Integral Gain'
                                                                  */
#define PI_KP_PLL                      4502                      /* Referenced by: '<S164>/Proportional Gain' */
#define PI_KP_POS                      65536                     /* Referenced by: '<S229>/Proportional Gain' */
#define PI_KP_SPD                      393216                    /* Referenced by: '<S290>/Proportional Gain' */
#define PI_KP_TQ                       25559                     /* Referenced by:
                                                                  * '<S60>/Proportional Gain'
                                                                  * '<S110>/Proportional Gain'
                                                                  */
#define POS_CTRL                       2U                        /* Referenced by: '<S4>/Chart1' */
#define PWM_FREQUENCY                  10000U                    /* Referenced by: '<S124>/Constant3' */
#define RAD2RPM_F_DEN                  1000U                     /* Referenced by: '<S317>/Constant3' */
#define RAD2RPM_F_NUM                  9549U                     /* Referenced by: '<S317>/Constant1' */
#define RADTOS16_F                     10430.3779F               /* Referenced by:
                                                                  * '<S178>/Constant2'
                                                                  * '<S244>/Constant2'
                                                                  * '<S307>/Constant2'
                                                                  */
#define RADTOS16_I                     10430U                    /* Referenced by: '<S124>/Constant5' */
#define REF_CURRENT_LOL                -9831                     /* Referenced by: '<S9>/Saturation1' */
#define REF_CURRENT_UPL                9831                      /* Referenced by: '<S9>/Saturation1' */
#define SPD_CTRL                       1U                        /* Referenced by: '<S4>/Chart1' */
#define STM_ALIGN                      4U                        /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S13>/Constant'
                                                                  */
#define STM_ANY_STOP                   8U                        /* Referenced by: '<S4>/Chart1' */
#define STM_IDLE                       2U                        /* Referenced by: '<S4>/Chart1' */
#define STM_IFRUN                      5U                        /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S177>/Constant1'
                                                                  */
#define STM_INIT                       1U                        /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S241>/Constant'
                                                                  */
#define STM_PREPARE                    3U                        /* Referenced by: '<S4>/Chart1' */
#define STM_PTRUN                      7U                        /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S187>/Constant'
                                                                  * '<S243>/Constant'
                                                                  */
#define STM_START                      12U                       /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S7>/Constant'
                                                                  * '<S186>/Constant'
                                                                  * '<S249>/Constant'
                                                                  * '<S304>/Constant'
                                                                  * '<S305>/Constant'
                                                                  * '<S310>/Constant'
                                                                  */
#define STM_STOP                       9U                        /* Referenced by: '<S4>/Chart1' */
#define STM_STOP_IDLE                  10U                       /* Referenced by: '<S4>/Chart1' */
#define STM_STRUN                      6U                        /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S248>/Constant'
                                                                  */
#define STM_SWITCH                     11U                       /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S246>/Constant'
                                                                  * '<S247>/Constant'
                                                                  */
#define STOMS                          1000U                     /* Referenced by:
                                                                  * '<S314>/Constant1'
                                                                  * '<S315>/Constant1'
                                                                  */
#define STO_C1                         316                       /* Referenced by:
                                                                  * '<S123>/Gain1'
                                                                  * '<S123>/Gain5'
                                                                  */
#define STO_C2                         -5907                     /* Referenced by:
                                                                  * '<S123>/Gain4'
                                                                  * '<S123>/Gain8'
                                                                  */
#define STO_C3                         1524                      /* Referenced by:
                                                                  * '<S123>/Gain3'
                                                                  * '<S123>/Gain7'
                                                                  */
#define STO_C4                         8271                      /* Referenced by:
                                                                  * '<S123>/Gain10'
                                                                  * '<S123>/Gain9'
                                                                  */
#define STO_C5                         1622                      /* Referenced by:
                                                                  * '<S123>/Gain2'
                                                                  * '<S123>/Gain6'
                                                                  */
#define STO_EST_MAX                    134213632                 /* Referenced by:
                                                                  * '<S123>/Saturation'
                                                                  * '<S123>/Saturation1'
                                                                  * '<S123>/Saturation2'
                                                                  * '<S123>/Saturation3'
                                                                  */
#define STO_EST_MIN                    -134213632                /* Referenced by:
                                                                  * '<S123>/Saturation'
                                                                  * '<S123>/Saturation1'
                                                                  * '<S123>/Saturation2'
                                                                  * '<S123>/Saturation3'
                                                                  */
#define STO_F1                         4096                      /* Referenced by:
                                                                  * '<S123>/Constant3'
                                                                  * '<S123>/Constant6'
                                                                  */
#define STO_F2                         4096                      /* Referenced by:
                                                                  * '<S123>/Constant2'
                                                                  * '<S123>/Constant5'
                                                                  * '<S124>/Constant4'
                                                                  */
#define STO_ST_CTRL                    3U                        /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S5>/Constant2'
                                                                  * '<S6>/Constant2'
                                                                  * '<S8>/Constant'
                                                                  * '<S177>/Constant'
                                                                  */
#define TORQ_CTRL                      0U                        /* Referenced by:
                                                                  * '<S4>/Chart1'
                                                                  * '<S6>/Constant1'
                                                                  */
#define U32MAXdivPulseNumber           429497U                   /* Referenced by: '<S15>/Constant6' */
#endif                                 /* RTW_HEADER_model_param_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
