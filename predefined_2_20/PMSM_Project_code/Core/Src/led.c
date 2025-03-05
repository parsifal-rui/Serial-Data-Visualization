#include "stm32f1xx_hal.h"
#include "led.h"

static uint16_t led_freq;
static uint16_t led_cnt;

void LedInit(void)
{
	led_freq = LED_FREQ_2HZ;
	led_cnt = 0;
}

void LedFreqSet(uint16_t freq)
{
	led_freq = freq;
}

void LedFlashing(void)
{
	led_cnt++;
	if(led_cnt >= led_freq)
	{
		led_cnt = 0;
		HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
	}
}

