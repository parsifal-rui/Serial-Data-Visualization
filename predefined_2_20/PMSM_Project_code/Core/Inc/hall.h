#ifndef HALL_H_
#define	HALL_H_

#define	PWMNUM_PER_MTASK	(PWM_FREQUENCY/SPD_SAMPLE_FREQ)
#define	H1_GPIO_PORT		((GPIO_TypeDef *)GPIOA)
#define	H2_GPIO_PORT		((GPIO_TypeDef *)GPIOA)
#define	H3_GPIO_PORT		((GPIO_TypeDef *)GPIOB)
#define	H1_PIN				GPIO_PIN_6
#define	H2_PIN				GPIO_PIN_7
#define	H3_PIN				GPIO_PIN_0

#define S16_DEGREE_120 		(int16_t)(65536/3)
#define S16_DEGREE_60		(int16_t)(65536/6)

#define	HALL_BEMF_TG5P60	0	//320
#define	HALL_BEMF_JSF630	35
#define	HALL_BEMF_TB2P		35

#define	HALL_TIM_FREQUENCY	72000000
#define	CALC_DPP_FACT1		(HALL_TIM_FREQUENCY/6/PWM_FREQUENCY*65536)

/*
1, MAX_PERIOD_FACT source
- Minimum speed threshold(rpm): 200
- Minimum speed threshold(rps): 200/60
- Number of hall pulses per cycle: rps*6*Pn=200/60*6*Pn
- The period of the hall pulse, represented by the CPU clock: 72000000/(200/60*6*Pn)=3600000/Pn
2, MAX_PERIOD_FACT Usage
- When the speed is low, the speed value obtained by averaging the buffer zone is not accurate
- Improvement plan: When the speed is low, calculate the speed value directly using the current captured hall pulse period
*/
#define	MAX_PERIOD_FACT		3600000	// Corresponding hall pulse period at 200rpm

/*
1, MIN-PERIOD-FACT source
- Maximum speed threshold (rpm): 3000
- Maximum speed threshold (rps): 3000/60
- Number of Hall pulses per cycle: rps * 6 * Pn=3000/60 * 6 * Pn
- The period of Hall pulses, represented by the CPU clock: 72000000/(3000/60 * 6 * Pn)=240000/Pn
2, MIN-PERIOD-FACT Usage
- Electrical interference may cause abnormal hall state cycles, and abnormal data can be determined through MIN-PERIOD-FACT
*/
#define	MIN_PERIOD_FACT		240000	// Corresponding hall pulse period at 3000rpm

#define	HALL_BUFF_SIZE		16

enum
{
	HALL_STATE1 = 0x01,
	HALL_STATE2,
	HALL_STATE3,
	HALL_STATE4,
	HALL_STATE5,
	HALL_STATE6,
};

typedef struct
{
	TIM_TypeDef *TIMx;
	int8_t		direction;			// rotate direction
	int16_t		measured_theat_e;	// The measured electrical angle
	int16_t		theat_e;			// Output electrical angle
	int32_t		state_period[HALL_BUFF_SIZE];	// HALL The period between adjacent states, represented by the CPU clock
	uint8_t		buf_idx;			// State_period buffer index
	uint8_t		buf_filled;			// State_period buffer first fill flag
	int32_t		period_sum;			// State_period buffer data accumulation sum
	uint8_t		first_capt;			// First capture of hall status update
	int16_t		avr_spd_dpp;		// Average speed, expressed in dpp
	uint32_t	state_upd_time;		// Hall status update time
	int16_t		comp_spd;			// Speed compensation, represented by s16Degree
	uint16_t	ovf_num;			// Timer overflow count
	uint8_t		cur_state;			// hall current state
	int16_t		hall_bemf;			// Hall phase offset angle
	int16_t 	delta_theat;		// measured_theat_e - theat_e
	uint8_t		operational;		// The sensor is operating normally
	uint8_t		err_cnt;			// Hall status error count
	int16_t		mec_spd;			// Mechanical speed in rpm
	uint16_t	stall_cnt;			// Number of motor stalling cycles

}HallHandle_t;

HallHandle_t *HallGetHandle(void);
void HallInit(void);
void HallInitElAngle(void);
void HallClear(void);
void HallTimUPIRQHandler(void);
void HallTimCCIRQHandler(void);
uint8_t HallCalcSpdPos(int16_t *mec_spd, int32_t *mec_pos);
uint8_t HallCalcAngle(int16_t *theat_e);

#endif

