#ifndef ENCODER_H_
#define	ENCODER_H_

#define ENC_BUFF_SIZE		16

/* 1.5 times the maximum speed, in revolutions per second */
#define	MAX_SPD_RPS			(int32_t)(MAX_CLOSELOOP_SPD*1.5/60)

/* Maximum encoder pulse count at each sampling */
#define	PULSES_ONCE_THR 	(int32_t)(ENC_PULSE_NUM*MAX_SPD_RPS/SPD_SAMPLE_FREQ)

typedef struct
{
	TIM_TypeDef *TIMx;
	uint32_t	enc_cnt;			// Encoder pulse counter
	uint32_t	of_cnt;				// TIMx Overflow counter
	uint32_t	cnt_dir;			// The counting direction of the counter
	uint32_t 	enc_cnt_pre;		// Encoder pulse counter for the previous sampling
	int32_t 	pulses_once;
	int32_t 	buff[ENC_BUFF_SIZE];	// Loop queue
	uint8_t 	index;				// Index of circular queue
	int32_t		pulses_avr;			// The average value of encoder pulse count for each sampling
	int16_t		mec_spd;			// Mechanical speed in rpm

	int16_t		theat_e;			// Electric angle, unit: s16degree
	
	int64_t		enc_cnt_pos;		// Absolute position from the origin, in encoder pulses
	int32_t		mec_pos;			// Mechanical position, unit: s16degree

}EncHandle_t;

EncHandle_t *EncGetHandle(void);
void EncInit(void);
void EncAlign(void);
void EncClear(void);
void EncGetTimInfo(void);
uint8_t EncCalcSpdPos(int16_t *mec_spd, int32_t *mec_pos);
uint8_t EncCalcAngle(int16_t *theat_e);
int32_t EncGetBuffAvgVal(int32_t in_data);

#endif

