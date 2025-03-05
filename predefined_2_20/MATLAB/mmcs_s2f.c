/*
 * File: mmcs_s2f.c
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

#include "mmcs_s2f.h"
#include "mmcs_s2f_private.h"

/* Exported block signals */
uint8_T motor_start;                   /* '<Root>/motor_start' */
uint8_T sys_ctrl_mode;                 /* '<Root>/sys_ctrl_mode' */
int16_T spd_ref;                       /* '<Root>/spd_ref' */
real32_T pos_ref;                      /* '<Root>/pos_ref' */
real32_T move_duration;                /* '<Root>/move_duration' */
int16_T iab_adc[2];                    /* '<Root>/iab_adc' */
int16_T spd_sensor;                    /* '<Root>/spd_sensor' */
int16_T theta_sensor;                  /* '<Root>/theta_sensor' */
int32_T pos_fed;                       /* '<Root>/pos_sensor' */
uint16_T mcu_ccrx[3];                  /* '<Root>/Variant Sink1' */
int16_T spd_fed;                       /* '<Root>/SpeedConvert' */
int16_T id_ref;                        /* '<S4>/Merge' */
int16_T iq_ref;                        /* '<S4>/Merge1' */
int16_T w_dot;                         /* '<S122>/Divide' */
uint8_T stm_state;                     /* '<S4>/Chart1' */
uint8_T ct_ctrl_mode;                  /* '<S4>/Chart1' */
int32_T pos_ref_int;                   /* '<S178>/Switch' */
int32_T i_alpha_dot;                   /* '<S123>/Saturation' */
int32_T i_beta_dot;                    /* '<S123>/Saturation1' */
int16_T theta_e;                       /* '<S6>/Switch1' */
int16_T i_alpha;                       /* '<S9>/Clark' */
int16_T i_beta;                        /* '<S9>/Clark' */
int16_T u_alpha;                       /* '<S9>/AntiPark' */
int16_T u_beta;                        /* '<S9>/AntiPark' */
int32_T e_alpha_dot;                   /* '<S123>/Saturation2' */
int32_T e_beta_dot;                    /* '<S123>/Saturation3' */
int16_T ia;                            /* '<S9>/Data Type Conversion' */
int16_T ib;                            /* '<S9>/Data Type Conversion1' */
int16_T id;                            /* '<S9>/Park' */
int16_T id_err;                        /* '<S9>/Sum3' */
int16_T iq;                            /* '<S9>/Park' */
int16_T iq_err;                        /* '<S9>/Sum1' */
int16_T ud;                            /* '<S9>/sfun_CircleLimit' */
int16_T uq;                            /* '<S9>/sfun_CircleLimit' */

/* Block signals (default storage) */
B_mmcs_s2f_T mmcs_s2f_B;

/* Block states (default storage) */
DW_mmcs_s2f_T mmcs_s2f_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_mmcs_s2f_T mmcs_s2f_PrevZCX;

/* Real-time model */
static RT_MODEL_mmcs_s2f_T mmcs_s2f_M_;
RT_MODEL_mmcs_s2f_T *const mmcs_s2f_M = &mmcs_s2f_M_;
void ssuMultiWordMul(const uint32_T u1[], int32_T n1, const uint32_T u2[],
                     int32_T n2, uint32_T y[], int32_T n)
{
  int32_T i;
  int32_T j;
  int32_T k;
  uint32_T cb;
  uint32_T cb1;
  uint32_T yk;
  boolean_T isNegative1;
  isNegative1 = ((u1[n1 - 1] & 2147483648U) != 0U);
  cb1 = 1U;

  /* Initialize output to zero */
  for (k = 0; k < n; k++) {
    y[k] = 0U;
  }

  for (i = 0; i < n1; i++) {
    int32_T ni;
    uint32_T a0;
    uint32_T a1;
    uint32_T u1i;
    cb = 0U;
    u1i = u1[i];
    if (isNegative1) {
      u1i = ~u1i + cb1;
      cb1 = (uint32_T)(u1i < cb1);
    }

    a1 = u1i >> 16U;
    a0 = u1i & 65535U;
    ni = n - i;
    ni = n2 <= ni ? n2 : ni;
    k = i;
    for (j = 0; j < ni; j++) {
      uint32_T b1;
      uint32_T w01;
      uint32_T w10;
      u1i = u2[j];
      b1 = u1i >> 16U;
      u1i &= 65535U;
      w10 = a1 * u1i;
      w01 = a0 * b1;
      yk = y[k] + cb;
      cb = (uint32_T)(yk < cb);
      u1i *= a0;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w10 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w01 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      y[k] = yk;
      cb += w10 >> 16U;
      cb += w01 >> 16U;
      cb += a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }

  /* Apply sign */
  if (isNegative1) {
    cb = 1U;
    for (k = 0; k < n; k++) {
      yk = ~y[k] + cb;
      y[k] = yk;
      cb = (uint32_T)(yk < cb);
    }
  }
}

int32_T MultiWord2sLong(const uint32_T u[])
{
  return (int32_T)u[0];
}

void sMultiWordDivZero(const uint32_T u1[], int32_T n1, const uint32_T u2[],
  int32_T n2, uint32_T y1[], int32_T m1, uint32_T y2[], int32_T m2, uint32_T t1[],
  int32_T l1, uint32_T t2[], int32_T l2)
{
  boolean_T denNeg;
  boolean_T numNeg;
  numNeg = ((u1[n1 - 1] & 2147483648U) != 0U);
  denNeg = ((u2[n2 - 1] & 2147483648U) != 0U);
  if (numNeg) {
    MultiWordNeg(u1, t1, n1);
  } else {
    sMultiWord2MultiWord(u1, n1, t1, l1);
  }

  if (denNeg) {
    MultiWordNeg(u2, t2, n2);
  } else {
    sMultiWord2MultiWord(u2, n2, t2, l2);
  }

  if (uMultiWordDiv(t1, l1, t2, l2, y1, m1, y2, m2) < 0) {
    if (numNeg) {
      MultiWordSetSignedMin(y1, m1);
    } else {
      MultiWordSetSignedMax(y1, m1);
    }
  } else if ((boolean_T)(numNeg ^ denNeg)) {
    MultiWordNeg(y1, y1, m1);
  }
}

void MultiWordNeg(const uint32_T u1[], uint32_T y[], int32_T n)
{
  int32_T i;
  uint32_T carry = 1U;
  for (i = 0; i < n; i++) {
    uint32_T yi;
    yi = ~u1[i] + carry;
    y[i] = yi;
    carry = (uint32_T)(yi < carry);
  }
}

void sMultiWord2MultiWord(const uint32_T u1[], int32_T n1, uint32_T y[], int32_T
  n)
{
  int32_T i;
  int32_T nm;
  nm = n1 < n ? n1 : n;
  for (i = 0; i < nm; i++) {
    y[i] = u1[i];
  }

  if (n > n1) {
    uint32_T u1i;
    u1i = (u1[n1 - 1] & 2147483648U) != 0U ? MAX_uint32_T : 0U;
    for (i = nm; i < n; i++) {
      y[i] = u1i;
    }
  }
}

void MultiWordSetSignedMin(uint32_T y[], int32_T n)
{
  int32_T i;
  int32_T n1;
  n1 = n - 1;
  for (i = 0; i < n1; i++) {
    y[i] = 0U;
  }

  y[n - 1] = 2147483648U;
}

void MultiWordSetSignedMax(uint32_T y[], int32_T n)
{
  int32_T i;
  int32_T n1;
  n1 = n - 1;
  for (i = 0; i < n1; i++) {
    y[i] = MAX_uint32_T;
  }

  y[n - 1] = 2147483647U;
}

int32_T uMultiWordDiv(uint32_T a[], int32_T na, uint32_T b[], int32_T nb,
                      uint32_T q[], int32_T nq, uint32_T r[], int32_T nr)
{
  int32_T ka;
  int32_T kr;
  int32_T nzb;
  int32_T tpi;
  int32_T y;
  nzb = nb;
  tpi = nb - 1;
  while ((nzb > 0) && (b[tpi] == 0U)) {
    nzb--;
    tpi--;
  }

  if (nzb > 0) {
    int32_T nza;
    nza = na;
    for (tpi = 0; tpi < nq; tpi++) {
      q[tpi] = 0U;
    }

    tpi = na - 1;
    while ((nza > 0) && (a[tpi] == 0U)) {
      nza--;
      tpi--;
    }

    if ((nza > 0) && (nza >= nzb)) {
      int32_T na1;
      int32_T nb1;
      nb1 = nzb - 1;
      na1 = nza - 1;
      for (kr = 0; kr < nr; kr++) {
        r[kr] = 0U;
      }

      /* Quick return if dividend and divisor fit into single word. */
      if (nza == 1) {
        uint32_T ak;
        uint32_T bk;
        uint32_T nbq;
        ak = a[0];
        bk = b[0];
        nbq = ak / bk;
        q[0] = nbq;
        r[0] = ak - nbq * bk;
        y = 7;
      } else {
        uint32_T kba;
        uint32_T kbb;
        uint32_T t;

        /* Remove leading zeros from both, dividend and divisor. */
        kbb = 1U;
        t = b[nzb - 1] >> 1U;
        while (t != 0U) {
          kbb++;
          t >>= 1U;
        }

        kba = 1U;
        t = a[nza - 1] >> 1U;
        while (t != 0U) {
          kba++;
          t >>= 1U;
        }

        /* Quick return if quotient is zero. */
        if ((nza > nzb) || (kba >= kbb)) {
          uint32_T ak;
          uint32_T bk;
          uint32_T mask;
          uint32_T nba;
          uint32_T nbb;
          uint32_T nbq;
          uint32_T tnb;
          nba = ((uint32_T)(nza - 1) << 5) + kba;
          nbb = ((uint32_T)(nzb - 1) << 5) + kbb;

          /* Normalize b. */
          if (kbb != 32U) {
            bk = b[nzb - 1];
            for (kr = nzb - 1; kr > 0; kr--) {
              t = bk << (32U - kbb);
              bk = b[kr - 1];
              t |= bk >> kbb;
              b[kr] = t;
            }

            b[kr] = bk << (32U - kbb);
            mask = ~((1U << (32U - kbb)) - 1U);
          } else {
            mask = MAX_uint32_T;
          }

          /* Initialize quotient to zero. */
          tnb = 0U;
          y = 0;

          /* Until exit conditions have been met, do */
          do {
            /* Normalize a */
            if (kba != 32U) {
              tnb = (tnb - kba) + 32U;
              ak = a[na1];
              for (ka = na1; ka > 0; ka--) {
                t = ak << (32U - kba);
                ak = a[ka - 1];
                t |= ak >> kba;
                a[ka] = t;
              }

              a[ka] = ak << (32U - kba);
            }

            /* Compare b against the a. */
            ak = a[na1];
            bk = b[nzb - 1];
            if (((nzb - 1 == 0 ? mask : MAX_uint32_T) & ak) == bk) {
              tpi = 0;
              ka = na1;
              kr = nzb - 1;
              while ((tpi == 0) && (kr > 0)) {
                ka--;
                ak = a[ka];
                kr--;
                bk = b[kr];
                if (((kr == 0 ? mask : MAX_uint32_T) & ak) != bk) {
                  tpi = ak > bk ? 1 : -1;
                }
              }
            } else {
              tpi = ak > bk ? 1 : -1;
            }

            /* If the remainder in a is still greater or equal to b, subtract normalized divisor from a. */
            if ((tpi >= 0) || (nba > nbb)) {
              nbq = nba - nbb;

              /* If the remainder and the divisor are equal, set remainder to zero. */
              if (tpi == 0) {
                ka = na1;
                for (kr = nzb - 1; kr > 0; kr--) {
                  a[ka] = 0U;
                  ka--;
                }

                a[ka] -= b[kr];
              } else {
                /* Otherwise, subtract the divisor from the remainder */
                if (tpi < 0) {
                  ak = a[na1];
                  kba = 31U;
                  for (ka = na1; ka > 0; ka--) {
                    t = ak << 1U;
                    ak = a[ka - 1];
                    t |= ak >> 31U;
                    a[ka] = t;
                  }

                  a[ka] = ak << 1U;
                  tnb++;
                  nbq--;
                }

                bk = 0U;
                ka = (na1 - nzb) + 1;
                for (kr = 0; kr < nzb; kr++) {
                  t = a[ka];
                  ak = (t - b[kr]) - bk;
                  bk = bk != 0U ? (uint32_T)(ak >= t) : (uint32_T)(ak > t);
                  a[ka] = ak;
                  ka++;
                }
              }

              /* Update the quotient. */
              tpi = (int32_T)(nbq >> 5);
              q[tpi] |= 1U << (nbq - ((uint32_T)tpi << 5));

              /* Remove leading zeros from the remainder and check whether the exit conditions have been met. */
              tpi = na1;
              while ((nza > 0) && (a[tpi] == 0U)) {
                nza--;
                tpi--;
              }

              if (nza >= nzb) {
                na1 = nza - 1;
                kba = 1U;
                t = a[nza - 1] >> 1U;
                while (t != 0U) {
                  kba++;
                  t >>= 1U;
                }

                nba = (((uint32_T)(nza - 1) << 5) + kba) - tnb;
                if (nba < nbb) {
                  y = 2;
                }
              } else if (nza == 0) {
                y = 1;
              } else {
                na1 = nza - 1;
                y = 4;
              }
            } else {
              y = 3;
            }
          } while (y == 0);

          /* Return the remainder. */
          if (y == 1) {
            r[0] = a[0];
          } else {
            tpi = (int32_T)(tnb >> 5);
            nbq = tnb - ((uint32_T)tpi << 5);
            if (nbq == 0U) {
              ka = tpi;
              for (kr = 0; kr <= nb1; kr++) {
                r[kr] = a[ka];
                ka++;
              }
            } else {
              ak = a[tpi];
              kr = 0;
              for (ka = tpi + 1; ka <= na1; ka++) {
                t = ak >> nbq;
                ak = a[ka];
                t |= ak << (32U - nbq);
                r[kr] = t;
                kr++;
              }

              r[kr] = ak >> nbq;
            }
          }

          /* Restore b. */
          if (kbb != 32U) {
            bk = b[0];
            for (kr = 0; kr < nb1; kr++) {
              t = bk >> (32U - kbb);
              bk = b[kr + 1];
              t |= bk << kbb;
              b[kr] = t;
            }

            b[kr] = bk >> (32U - kbb);
          }
        } else {
          for (kr = 0; kr < nr; kr++) {
            r[kr] = a[kr];
          }

          y = 6;
        }
      }
    } else {
      for (kr = 0; kr < nr; kr++) {
        r[kr] = a[kr];
      }

      y = 5;
    }
  } else {
    y = -1;
  }

  return y;
}

void sLong2MultiWord(int32_T u, uint32_T y[], int32_T n)
{
  int32_T i;
  uint32_T yi;
  y[0] = (uint32_T)u;
  yi = u < 0 ? MAX_uint32_T : 0U;
  for (i = 1; i < n; i++) {
    y[i] = yi;
  }
}

void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo)
{
  uint32_T absIn0;
  uint32_T absIn1;
  uint32_T in0Hi;
  uint32_T in0Lo;
  uint32_T in1Hi;
  uint32_T productHiLo;
  uint32_T productLoHi;
  absIn0 = in0 < 0 ? ~(uint32_T)in0 + 1U : (uint32_T)in0;
  absIn1 = in1 < 0 ? ~(uint32_T)in1 + 1U : (uint32_T)in1;
  in0Hi = absIn0 >> 16U;
  in0Lo = absIn0 & 65535U;
  in1Hi = absIn1 >> 16U;
  absIn0 = absIn1 & 65535U;
  productHiLo = in0Hi * absIn0;
  productLoHi = in0Lo * in1Hi;
  absIn0 *= in0Lo;
  absIn1 = 0U;
  in0Lo = (productLoHi << /*MW:OvBitwiseOk*/ 16U) + /*MW:OvCarryOk*/ absIn0;
  if (in0Lo < absIn0) {
    absIn1 = 1U;
  }

  absIn0 = in0Lo;
  in0Lo += /*MW:OvCarryOk*/ productHiLo << /*MW:OvBitwiseOk*/ 16U;
  if (in0Lo < absIn0) {
    absIn1++;
  }

  absIn0 = (((productLoHi >> 16U) + (productHiLo >> 16U)) + in0Hi * in1Hi) +
    absIn1;
  if ((in0 != 0) && ((in1 != 0) && ((in0 > 0) != (in1 > 0)))) {
    absIn0 = ~absIn0;
    in0Lo = ~in0Lo;
    in0Lo++;
    if (in0Lo == 0U) {
      absIn0++;
    }
  }

  *ptrOutBitsHi = absIn0;
  *ptrOutBitsLo = in0Lo;
}

int32_T mul_s32_loSR_zero(int32_T a, int32_T b, uint32_T aShift)
{
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  u32_clo = (((int32_T)u32_chi < 0) && ((((1U << aShift) - 1U) & u32_clo) != 0U))
    + (u32_chi << /*MW:OvBitwiseOk*/ (32U - aShift) | u32_clo >> aShift);
  return (int32_T)u32_clo;
}

int32_T mul_s32_hiSR_zero(int32_T a, int32_T b, uint32_T aShift)
{
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  return (int32_T)((uint32_T)(((u32_clo != 0U) || ((((1U << aShift) - 1U) &
    u32_chi) != 0U)) && ((int32_T)u32_chi < 0)) + ((int32_T)u32_chi >> aShift));
}

int32_T mul_s32_loSR_sat_zero(int32_T a, int32_T b, uint32_T aShift)
{
  int32_T result;
  uint32_T u32_chi;
  uint32_T u32_clo;
  boolean_T roundup;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  roundup = (((int32_T)u32_chi < 0) && ((((1U << aShift) - 1U) & u32_clo) != 0U));
  u32_clo = (u32_chi << /*MW:OvBitwiseOk*/ (32U - aShift) | u32_clo >> aShift) +
    roundup;
  u32_chi = (uint32_T)(roundup && (u32_clo == 0U)) + ((int32_T)u32_chi >> aShift);
  if (((int32_T)u32_chi > 0) || ((u32_chi == 0U) && (u32_clo >= 2147483648U))) {
    result = MAX_int32_T;
  } else if (((int32_T)u32_chi < -1) || (((int32_T)u32_chi == -1) && (u32_clo <
               2147483648U))) {
    result = MIN_int32_T;
  } else {
    result = (int32_T)u32_clo;
  }

  return result;
}

int32_T mul_s32_sat(int32_T a, int32_T b)
{
  int32_T result;
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  if (((int32_T)u32_chi > 0) || ((u32_chi == 0U) && (u32_clo >= 2147483648U))) {
    result = MAX_int32_T;
  } else if (((int32_T)u32_chi < -1) || (((int32_T)u32_chi == -1) && (u32_clo <
               2147483648U))) {
    result = MIN_int32_T;
  } else {
    result = (int32_T)u32_clo;
  }

  return result;
}

int16_T div_s16s32(int32_T numerator, int32_T denominator)
{
  int16_T quotient;
  if (denominator == 0) {
    quotient = (int16_T)(numerator >= 0 ? 32767 : -32768);

    /* Divide by zero handler */
  } else {
    uint32_T tempAbsQuotient;
    tempAbsQuotient = (numerator < 0 ? ~(uint32_T)numerator + 1U : (uint32_T)
                       numerator) / (denominator < 0 ? ~(uint32_T)denominator +
      1U : (uint32_T)denominator);
    quotient = (int16_T)((numerator < 0) != (denominator < 0) ? (int32_T)
                         (int16_T)-(int32_T)tempAbsQuotient : (int32_T)(int16_T)
                         tempAbsQuotient);
  }

  return quotient;
}

int32_T div_s32(int32_T numerator, int32_T denominator)
{
  int32_T quotient;
  if (denominator == 0) {
    quotient = numerator >= 0 ? MAX_int32_T : MIN_int32_T;

    /* Divide by zero handler */
  } else {
    uint32_T tempAbsQuotient;
    tempAbsQuotient = (numerator < 0 ? ~(uint32_T)numerator + 1U : (uint32_T)
                       numerator) / (denominator < 0 ? ~(uint32_T)denominator +
      1U : (uint32_T)denominator);
    quotient = (numerator < 0) != (denominator < 0) ? -(int32_T)tempAbsQuotient :
      (int32_T)tempAbsQuotient;
  }

  return quotient;
}

/* Model step function for TID0 */
void mmcs_s2f_step0(void)              /* Sample time: [0.0001s, 0.0s] */
{
  int32_T tmp;

  /* RateTransition: '<Root>/RT1' */
  mmcs_s2f_B.RT1 = mmcs_s2f_DW.RT1_Buffer0;

  /* RateTransition: '<Root>/RT2' */
  mmcs_s2f_B.RT2 = mmcs_s2f_DW.RT2_Buffer0;

  /* RateTransition: '<Root>/RT3' */
  tmp = mmcs_s2f_DW.RT3_ActiveBufIdx << 1;

  /* RateTransition: '<Root>/RT3' */
  mmcs_s2f_B.RT3[0] = mmcs_s2f_DW.RT3_Buffer[tmp];
  mmcs_s2f_B.RT3[1] = mmcs_s2f_DW.RT3_Buffer[tmp + 1];

  /* RateTransition: '<Root>/RT4' */
  mmcs_s2f_B.RT4 = mmcs_s2f_DW.RT4_Buffer0;

  /* Outputs for Atomic SubSystem: '<Root>/HFTask' */

  /* Inport: '<Root>/sys_ctrl_mode' incorporates:
   *  Inport: '<Root>/iab_adc'
   *  Inport: '<Root>/spd_ref'
   *  Inport: '<Root>/theta_sensor'
   */
  mmcs_s2f_HFTask(sys_ctrl_mode, mmcs_s2f_B.RT1, mmcs_s2f_B.RT2, mmcs_s2f_B.RT3,
                  mmcs_s2f_B.RT4, iab_adc, theta_sensor, spd_ref,
                  &mmcs_s2f_B.sfun_EmSvpwm_o1, &mmcs_s2f_B.sfun_EmSvpwm_o2,
                  &mmcs_s2f_B.sfun_EmSvpwm_o3, &mmcs_s2f_B.DataTypeConversion,
                  &w_dot, &mmcs_s2f_B.HFTask, &mmcs_s2f_DW.HFTask,
                  &mmcs_s2f_PrevZCX.HFTask);

  /* End of Outputs for SubSystem: '<Root>/HFTask' */

  /* SignalConversion generated from: '<Root>/Variant Sink1' */
  mcu_ccrx[0] = mmcs_s2f_B.sfun_EmSvpwm_o1;
  mcu_ccrx[1] = mmcs_s2f_B.sfun_EmSvpwm_o2;
  mcu_ccrx[2] = mmcs_s2f_B.sfun_EmSvpwm_o3;

  /* UnitDelay: '<Root>/Unit Delay8' */
  mmcs_s2f_B.UnitDelay8 = mmcs_s2f_DW.UnitDelay8_DSTATE;

  /* Update for UnitDelay: '<Root>/Unit Delay8' */
  mmcs_s2f_DW.UnitDelay8_DSTATE = w_dot;
}

/* Model step function for TID1 */
void mmcs_s2f_step1(void)              /* Sample time: [0.002s, 0.0s] */
{
  /* RateTransition: '<Root>/RT' incorporates:
   *  Inport: '<Root>/sys_ctrl_mode'
   */
  mmcs_s2f_B.RT_a = sys_ctrl_mode;

  /* RateTransition: '<Root>/RT9' incorporates:
   *  Inport: '<Root>/spd_ref'
   */
  mmcs_s2f_B.spd_ref_h = spd_ref;

  /* RateTransition: '<Root>/RT6' incorporates:
   *  Inport: '<Root>/sys_ctrl_mode'
   */
  mmcs_s2f_B.RT6 = sys_ctrl_mode;

  /* RateTransition: '<Root>/RT8' */
  mmcs_s2f_B.RT8 = mmcs_s2f_B.UnitDelay8;

  /* Outputs for Atomic SubSystem: '<Root>/SpeedConvert' */

  /* Inport: '<Root>/spd_sensor' */
  mmcs_s2f_SpeedConvert(mmcs_s2f_B.RT6, spd_sensor, mmcs_s2f_B.RT8,
                        &mmcs_s2f_B.avg, &mmcs_s2f_B.SpeedConvert,
                        &mmcs_s2f_DW.SpeedConvert);

  /* End of Outputs for SubSystem: '<Root>/SpeedConvert' */

  /* SignalConversion generated from: '<Root>/SpeedConvert' */
  spd_fed = mmcs_s2f_B.avg;

  /* RateTransition: '<Root>/RT5' incorporates:
   *  Inport: '<Root>/pos_sensor'
   */
  mmcs_s2f_B.RT5 = pos_fed;

  /* Outputs for Atomic SubSystem: '<Root>/MFTask' */

  /* Inport: '<Root>/motor_start' incorporates:
   *  Inport: '<Root>/move_duration'
   *  Inport: '<Root>/pos_ref'
   */
  mmcs_s2f_MFTask(mmcs_s2f_B.RT_a, motor_start, mmcs_s2f_B.spd_ref_h, spd_fed,
                  pos_ref, move_duration, mmcs_s2f_B.RT5, &ct_ctrl_mode,
                  &stm_state, &id_ref, &iq_ref, &mmcs_s2f_B.Merge2,
                  &mmcs_s2f_B.MFTask, &mmcs_s2f_DW.MFTask);

  /* End of Outputs for SubSystem: '<Root>/MFTask' */

  /* RateTransition: '<Root>/RT1' */
  mmcs_s2f_DW.RT1_Buffer0 = ct_ctrl_mode;

  /* RateTransition: '<Root>/RT2' */
  mmcs_s2f_DW.RT2_Buffer0 = stm_state;

  /* RateTransition: '<Root>/RT3' */
  mmcs_s2f_DW.RT3_Buffer[(mmcs_s2f_DW.RT3_ActiveBufIdx == 0) << 1] = id_ref;
  mmcs_s2f_DW.RT3_Buffer[1 + ((mmcs_s2f_DW.RT3_ActiveBufIdx == 0) << 1)] =
    iq_ref;
  mmcs_s2f_DW.RT3_ActiveBufIdx = (int8_T)(mmcs_s2f_DW.RT3_ActiveBufIdx == 0);

  /* RateTransition: '<Root>/RT4' */
  mmcs_s2f_DW.RT4_Buffer0 = mmcs_s2f_B.Merge2;
}

/* Model initialize function */
void mmcs_s2f_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* external inputs */
  sys_ctrl_mode = 2U;
  spd_ref = 1000;
  move_duration = 3.0F;
  mmcs_s2f_PrevZCX.HFTask.ObserverPLL.ResettableSubsystem_Reset_ZCE = POS_ZCSIG;

  /* SystemInitialize for Atomic SubSystem: '<Root>/HFTask' */
  mmcs_s2f_HFTask_Init(&w_dot, &mmcs_s2f_DW.HFTask);

  /* End of SystemInitialize for SubSystem: '<Root>/HFTask' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/MFTask' */

  /* SystemInitialize for Inport: '<Root>/pos_ref' incorporates:
   *  Inport: '<Root>/move_duration'
   */
  mmcs_s2f_MFTask_Init(&ct_ctrl_mode, &stm_state, &id_ref, &iq_ref,
                       &mmcs_s2f_B.Merge2, &mmcs_s2f_DW.MFTask);

  /* End of SystemInitialize for SubSystem: '<Root>/MFTask' */

  /* SystemInitialize for Atomic SubSystem: '<Root>/SpeedConvert' */
  mmcs_s2f_SpeedConvert_Init(&mmcs_s2f_DW.SpeedConvert);

  /* End of SystemInitialize for SubSystem: '<Root>/SpeedConvert' */
}

/* Model terminate function */
void mmcs_s2f_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/MFTask' */

  /* Terminate for Inport: '<Root>/pos_ref' incorporates:
   *  Inport: '<Root>/move_duration'
   */

  /* End of Terminate for SubSystem: '<Root>/MFTask' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
