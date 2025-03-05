/*
 * File: mmcs_s2f_private.h
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

#ifndef RTW_HEADER_mmcs_s2f_private_h_
#define RTW_HEADER_mmcs_s2f_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

extern real_T rt_roundd_snf(real_T u);
extern void ssuMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[],
  int32_T n2, uint32_T y[], int32_T n);
extern int32_T MultiWord2sLong(const uint32_T u[]);
extern void sMultiWordDivZero(const uint32_T u1[], int32_T n1, const uint32_T
  u2[], int32_T n2, uint32_T y1[], int32_T m1, uint32_T y2[], int32_T m2,
  uint32_T t1[], int32_T l1, uint32_T t2[], int32_T l2);
extern void MultiWordNeg(const uint32_T u1[], uint32_T y[], int32_T n);
extern void sMultiWord2MultiWord(const uint32_T u1[], int32_T n1, uint32_T y[],
  int32_T n);
extern void MultiWordSetSignedMin(uint32_T y[], int32_T n);
extern void MultiWordSetSignedMax(uint32_T y[], int32_T n);
extern int32_T uMultiWordDiv(uint32_T a[], int32_T na, uint32_T b[], int32_T nb,
  uint32_T q[], int32_T nq, uint32_T r[], int32_T nr);
extern void sLong2MultiWord(int32_T u, uint32_T y[], int32_T n);
extern void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi,
  uint32_T *ptrOutBitsLo);
extern int32_T mul_s32_loSR_zero(int32_T a, int32_T b, uint32_T aShift);
extern int32_T mul_s32_hiSR_zero(int32_T a, int32_T b, uint32_T aShift);
extern int32_T mul_s32_loSR_sat_zero(int32_T a, int32_T b, uint32_T aShift);
extern int32_T mul_s32_sat(int32_T a, int32_T b);
extern int16_T div_s16s32(int32_T numerator, int32_T denominator);
extern int32_T div_s32(int32_T numerator, int32_T denominator);

#endif                                 /* RTW_HEADER_mmcs_s2f_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
