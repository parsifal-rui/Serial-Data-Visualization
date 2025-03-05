#ifndef LED_H_
#define	LED_H_

#define	LED_PIN		GPIO_PIN_12
#define	LED_GPIO_PORT	((GPIO_TypeDef *)GPIOB)

#define	LED_FREQ_1HZ	250
#define	LED_FREQ_2HZ	125
#define	LED_FREQ_5HZ	50

void LedInit(void);
void LedFreqSet(uint16_t freq);
void LedFlashing(void);

#endif

