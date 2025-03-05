/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"
#include "mc_aux.h"
#include "msconfig.h"
#include <string.h>
/* USER CODE BEGIN 0 */
typedef union {
    float ft;
    uint8_t bytes[4];
} FloatConverter;

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint8_t TxData[8];
uint8_t RxData[8];
uint32_t TxMailbox;

#define McGetIa_Addr       ((uint32_t)0x100)  // 电流 Ia 的地址
#define McGetIb_Addr       ((uint32_t)0x101)  // 电流 Ib 的地址
#define McGetIc_Addr       ((uint32_t)0x102)  // 电流 Ic 的地址
#define McGetId_Addr       ((uint32_t)0x103)  // 电流 Id 的地址
#define McGetIq_Addr       ((uint32_t)0x104)  // 电流 Iq 的地址
#define McGetSpdRef_Addr   ((uint32_t)0x105)  // 速度参考值的地址
#define McGetSpdFed_Addr   ((uint32_t)0x106)  // 速度反馈值的地址
#define McGetPosFedS16_Addr ((uint32_t)0x107) // 位置反馈值（16位有符号）的地址

/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 8;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_4TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */
  
    CAN_FilterTypeDef sFilterConfig;
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }
  
  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_CAN1_2();

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */
	__HAL_CAN_ENABLE_IT(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void CAN_Config(void)
{
    TxHeader.StdId = 0; 
    TxHeader.ExtId = 0;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.DLC = 8;
    TxHeader.TransmitGlobalTime = DISABLE;

	HAL_CAN_Start(&hcan);
    HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void CAN_SendString(uint32_t StdId, const char *msg)
{	
	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0) {
	}
    
    size_t msgLen = strlen(msg);
    if(msgLen > 8) {
        msgLen = 8;  
    }
	TxHeader.DLC = msgLen;
	TxHeader.StdId = StdId; 
	memcpy(TxData, msg, msgLen);
	
	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK) {
		Error_Handler();
	}

}

void Can_SendFloat(uint32_t StdId, const float f) {
	FloatConverter converter;
	converter.ft = f;
	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0) {
	}
	TxHeader.DLC = 4;
	TxHeader.StdId = StdId;
	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, converter.bytes, &TxMailbox) != HAL_OK) {
		Error_Handler();
	}
}

void CAN_SendFocVar() {
	Can_SendFloat(McGetIa_Addr, (float)McGetIa());
	Can_SendFloat(McGetIb_Addr, (float)McGetIb());
	Can_SendFloat(McGetIc_Addr, (float)McGetIc());
	Can_SendFloat(McGetId_Addr, (float)McGetId());
	Can_SendFloat(McGetIq_Addr, (float)McGetIq());
	Can_SendFloat(McGetSpdRef_Addr, (float)McGetSpdRef());
	Can_SendFloat(McGetSpdFed_Addr, (float)McGetSpdFed());
	Can_SendFloat(McGetPosFedS16_Addr, (float)McGetPosFedS16());
}

void CAN_ProcessReceivedData(CAN_RxHeaderTypeDef *RxHeader, uint8_t *RxData)
{
    // 控制电机打开
    if (strncmp((char*)RxData, "MOT ON", 6) == 0)
    {
        McStartMotor();
    }
	// 控制电机关闭
    else if (strncmp((char*)RxData, "MOT OFF", 7) == 0)
    {
        McStopMotor();
    }

    // 控制电机加速
    else if (strncmp((char*)RxData, "ACCE", 4) == 0)
    {
		McIncSpdRef();
    }

    // 控制电机减速
    else if (strncmp((char*)RxData, "DECE", 4) == 0)
    {
        McDecSpdRef();
    }

    // 控制电机正转
    else if (strncmp((char*)RxData, "DIR POS", 7) == 0)
    {
		if(McGetMotorStart() == 0){
			if(McGetRotateDir() == DIR_NEGTIVE) {
				McSetRotateDir(DIR_POSTIVE);
				int16_t spd = McGetSpdRef();
				McSetSpdRef(-spd);
			}
		}
    }
	// 控制电机反转
	else if (strncmp((char*)RxData, "DIR NEG", 7) == 0)
    {
		if(McGetMotorStart() == 0) {
			if(McGetRotateDir() == DIR_POSTIVE) {
				McSetRotateDir(DIR_NEGTIVE);
				int16_t spd = McGetSpdRef();
				McSetSpdRef(-spd);
			}
		}
    }
	// 控制电机反转方向
	else if (strncmp((char*)RxData, "DIR REV", 7) == 0)
    {
		if(McGetMotorStart() == 0)
			{
				int16_t spd;
				if(McGetRotateDir() == DIR_POSTIVE)
					McSetRotateDir(DIR_NEGTIVE);
				else
					McSetRotateDir(DIR_POSTIVE);
				spd = McGetSpdRef();
				McSetSpdRef(-spd);
			}
    }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
    {
        CAN_ProcessReceivedData(&RxHeader, RxData); 
    }
}


void Check_CAN_Error(void)
{
    uint32_t error_code = HAL_CAN_GetError(&hcan);
    if (error_code != HAL_CAN_ERROR_NONE)
    {
        HAL_CAN_Stop(&hcan);
        MX_CAN_Init();
		CAN_Config();
    }
}
/* USER CODE END 1 */
