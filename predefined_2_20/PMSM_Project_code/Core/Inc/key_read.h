#ifndef KEY_READ_H_
#define	KEY_READ_H_

#define	KEY_DURATION_COUNT	1000

enum
{
	KEY_DOWN_LEVEL = 0,
	KEY_UP_LEVEL,
};

enum
{
	KEY_EVT_NONE = 0,
	KEY_EVT_DOWN,
	KEY_EVT_UP,
	KEY_EVT_MAX,
};

typedef struct
{
	GPIO_TypeDef	*pGPIOx;
	uint32_t	pin_num;
	uint8_t		last_sts;
	uint16_t	duration_count;
}KeyObj_t;

typedef struct
{
	uint8_t key_idx;
	uint8_t key_evt;
}KeyVal_t;

void KeyObjInit(KeyObj_t *phandle);
uint8_t ReadOneKey(KeyObj_t *phandle);
KeyVal_t ReadGroupKey(KeyObj_t *phandle, uint8_t len);

#endif

