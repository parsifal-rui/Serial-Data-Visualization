#ifndef OVER_CURRENT_DETECT_H_
#define	OVER_CURRENT_DETECT_H_

#define OVER_CURRENT_THF	(float)3.5
#define OVER_CURRENT_UPL	(int16_t)(3277*OVER_CURRENT_THF)
#define OVER_CURRENT_LOL	(int16_t)(-3277*OVER_CURRENT_THF)

typedef struct
{
	uint16_t 	oc_cnt;			// Continuous overcurrent counter
	uint32_t 	pre_oc_time;	// Last overcurrent time
	uint8_t  	is_oc;			// 
	uint8_t		is_oc_cnt;
}OCDetect_t;

OCDetect_t *OcDetectGetHandle(void);
void OcDetectInit(void);
void OcDetectExec(void);

#endif

