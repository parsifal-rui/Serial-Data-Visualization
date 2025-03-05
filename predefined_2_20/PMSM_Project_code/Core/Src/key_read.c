#include "stm32f1xx_hal.h"
#include "key_read.h"

void KeyObjInit(KeyObj_t *phandle)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	if(phandle == NULL)
		return;
	
	/* clock enable */
	if(phandle->pGPIOx == GPIOA)
		__HAL_RCC_GPIOA_CLK_ENABLE();
	else if(phandle->pGPIOx == GPIOB)
		__HAL_RCC_GPIOB_CLK_ENABLE();
	else if(phandle->pGPIOx == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();
	else if(phandle->pGPIOx == GPIOD)
		__HAL_RCC_GPIOD_CLK_ENABLE();
	else if(phandle->pGPIOx == GPIOE)
		__HAL_RCC_GPIOE_CLK_ENABLE();
//	else if(phandle->pGPIOx == GPIOF)
//		__HAL_RCC_GPIOF_CLK_ENABLE();
//	else if(phandle->pGPIOx == GPIOG)
//		__HAL_RCC_GPIOG_CLK_ENABLE();

	/* gpio init */
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	GPIO_InitStruct.Pin = phandle->pin_num;
	HAL_GPIO_Init(phandle->pGPIOx , &GPIO_InitStruct);
	
}

uint8_t ReadOneKey(KeyObj_t *phandle)
{
	uint8_t key_value = KEY_EVT_NONE;
	
	if(HAL_GPIO_ReadPin(phandle->pGPIOx, phandle->pin_num) == KEY_DOWN_LEVEL)
	{
		if(phandle->last_sts == KEY_UP_LEVEL)
		{
			phandle->duration_count++;
			if(phandle->duration_count >= KEY_DURATION_COUNT)
			{
				key_value = KEY_EVT_DOWN;
				phandle->last_sts = KEY_DOWN_LEVEL;
				phandle->duration_count = 0;
			}
		}
	}
	else
	{
		if(phandle->last_sts == KEY_DOWN_LEVEL)
		{
			phandle->duration_count++;
			if(phandle->duration_count >= KEY_DURATION_COUNT)
			{
				key_value = KEY_EVT_UP;
				phandle->last_sts = KEY_UP_LEVEL;
				phandle->duration_count = 0;
			}
		}
	}

	return key_value;
}

KeyVal_t ReadGroupKey(KeyObj_t *phandle, uint8_t len)
{
	uint8_t i = 0;
	KeyVal_t key_val;
	uint8_t key_evt = KEY_EVT_NONE;

	for(i = 0; i < len; i++)
	{
		key_evt = ReadOneKey(phandle + i);
		if(key_evt != KEY_EVT_NONE)
			break;
	}
	
	key_val.key_idx = i;
	key_val.key_evt = key_evt;
	
	return key_val;
}


