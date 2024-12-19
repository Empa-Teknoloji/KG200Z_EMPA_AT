/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    lora_app.c
 * @author  MCD Application Team
 * @brief   Application of the LRWAN Middleware
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "platform.h"
#include "sys_app.h"
#include "lora_app.h"
#include "stm32_seq.h"
#include "stm32_timer.h"
#include "utilities_def.h"
#include "app_version.h"
#include "lorawan_version.h"
#include "subghz_phy_version.h"
#include "lora_info.h"
#include "LmHandler.h"
#include "lora_command.h"
#include "lora_at.h"
#include "flash_if.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/**
 * LEDs period value of the timer in ms
 */
#define LED_PERIOD_TIME 500

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private function prototypes -----------------------------------------------*/
/**
 * @brief  join event callback function
 * @param  joinParams status of join
 */
static void OnJoinRequest(LmHandlerJoinParams_t *joinParams);

/**
 * @brief callback when LoRaWAN application has sent a frame
 * @brief  tx event callback function
 * @param  params status of last Tx
 */
static void OnTxData(LmHandlerTxParams_t *params);

/**
 * @brief callback when LoRaWAN application has received a frame
 * @param appData data received in the last Rx
 * @param params status of last Rx
 */
static void OnRxData(LmHandlerAppData_t *appData, LmHandlerRxParams_t *params);

/**
 * @brief callback when LoRaWAN Beacon status is updated
 * @param params status of Last Beacon
 */
static void OnBeaconStatusChange(LmHandlerBeaconParams_t *params);

/**
 * @brief callback when system time has been updated
 */
static void OnSysTimeUpdate(void);

/**
 * @brief callback when LoRaWAN application Class is changed
 * @param deviceClass new class
 */
static void OnClassChange(DeviceClass_t deviceClass);

/**
 * @brief  Notifies the upper layer that the NVM context has changed
 * @param  state Indicates if we are storing (true) or restoring (false) the NVM context
 */
static void OnNvmDataChange(LmHandlerNvmContextStates_t state);

/**
 * @brief  Store the NVM Data context to the Flash
 * @param  nvm ptr on nvm structure
 * @param  nvm_size number of data bytes which were stored
 */
static void OnStoreContextRequest(void *nvm, uint32_t nvm_size);

/**
 * @brief  Restore the NVM Data context from the Flash
 * @param  nvm ptr on nvm structure
 * @param  nvm_size number of data bytes which were restored
 */
static void OnRestoreContextRequest(void *nvm, uint32_t nvm_size);

/**
 * Will be called each time a Radio IRQ is handled by the MAC layer
 *
 */
static void OnMacProcessNotify(void);

/**
 * @brief  call back when LoRaWan Stack needs update
 */
static void CmdProcessNotify(void);

/**
 * @brief Change the periodicity of the uplink frames
 * @param periodicity uplink frames period in ms
 * @note Compliance test protocol callbacks
 */
static void OnTxPeriodicityChanged(uint32_t periodicity);

/**
 * @brief Change the confirmation control of the uplink frames
 * @param isTxConfirmed Indicates if the uplink requires an acknowledgement
 * @note Compliance test protocol callbacks
 */
static void OnTxFrameCtrlChanged(LmHandlerMsgTypes_t isTxConfirmed);

/**
 * @brief Change the periodicity of the ping slot frames
 * @param pingSlotPeriodicity ping slot frames period in ms
 * @note Compliance test protocol callbacks
 */
static void OnPingSlotPeriodicityChanged(uint8_t pingSlotPeriodicity);

/**
 * @brief Will be called to reset the system
 * @note Compliance test protocol callbacks
 */
static void OnSystemReset(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private variables ---------------------------------------------------------*/
/**
 * @brief LoRaWAN handler Callbacks
 */
static LmHandlerCallbacks_t LmHandlerCallbacks = { .GetBatteryLevel =
		GetBatteryLevel, .GetTemperature = GetTemperatureLevel, .GetUniqueId =
		GetUniqueId, .GetDevAddr = GetDevAddr, .OnRestoreContextRequest =
		OnRestoreContextRequest, .OnStoreContextRequest = OnStoreContextRequest,
		.OnMacProcess = OnMacProcessNotify, .OnNvmDataChange = OnNvmDataChange,
		.OnJoinRequest = OnJoinRequest, .OnTxData = OnTxData, .OnRxData =
				OnRxData, .OnBeaconStatusChange = OnBeaconStatusChange,
		.OnSysTimeUpdate = OnSysTimeUpdate, .OnClassChange = OnClassChange,
		.OnTxPeriodicityChanged = OnTxPeriodicityChanged,
		.OnTxFrameCtrlChanged = OnTxFrameCtrlChanged,
		.OnPingSlotPeriodicityChanged = OnPingSlotPeriodicityChanged,
		.OnSystemReset = OnSystemReset, };

/**
 * @brief LoRaWAN handler parameters
 */
static LmHandlerParams_t LmHandlerParams = { .ActiveRegion = ACTIVE_REGION,
		.DefaultClass = CLASS_A, .AdrEnable = LORAWAN_ADR_STATE, .TxDatarate =
		LORAWAN_DEFAULT_DATA_RATE, .TxPower = LORAWAN_DEFAULT_TX_POWER,
		.PingSlotPeriodicity = LORAWAN_DEFAULT_PING_SLOT_PERIODICITY,
		.RxBCTimeout = LORAWAN_DEFAULT_CLASS_B_C_RESP_TIMEOUT };

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Exported functions ---------------------------------------------------------*/
/* USER CODE BEGIN EF */

/* USER CODE END EF */

void LoRaWAN_Init(void) {
	/* USER CODE BEGIN LoRaWAN_Init_LV */

	/* USER CODE END LoRaWAN_Init_LV */

	CMD_Init(CmdProcessNotify);

	/* USER CODE BEGIN LoRaWAN_Init_1 */

	/* USER CODE END LoRaWAN_Init_1 */

	UTIL_SEQ_RegTask((1 << CFG_SEQ_Task_LmHandlerProcess), UTIL_SEQ_RFU,
			LmHandlerProcess);

	UTIL_SEQ_RegTask((1 << CFG_SEQ_Task_Vcom), UTIL_SEQ_RFU, CMD_Process);

	/* Init Info table used by LmHandler*/
	LoraInfo_Init();

	/* Init the Lora Stack*/
	LmHandlerInit(&LmHandlerCallbacks, APP_VERSION);

	LmHandlerConfigure(&LmHandlerParams);

	/* USER CODE BEGIN LoRaWAN_Init_Last */
	AT_PRINTF("\r\n.....EMPA-Quectel KG200Z Workshop.....\r\n");
	AT_PRINTF("Write AT? for listing the AT Functions\r\n");
	/* USER CODE END LoRaWAN_Init_Last */
}

/* USER CODE BEGIN PB_Callbacks */

/* USER CODE END PB_Callbacks */

/* Private functions ---------------------------------------------------------*/
/* USER CODE BEGIN PrFD */
#define LORAWAN_APP_DATA_BUFFER_MAX_SIZE            242
uint32_t Desk_id = 0x00;
/* USER CODE END PrFD */

static void OnRxData(LmHandlerAppData_t *appData, LmHandlerRxParams_t *params) {
	/* USER CODE BEGIN OnRxData_1 */
	const char *slotStrings[] = { "1", "2", "C", "C_MC", "P", "P_MC" };
	uint8_t ReceivedDataSize = 0;
	uint8_t RxPort = 0;

	if (appData != NULL) {
		RxPort = appData->Port;
		if ((appData->Buffer != NULL) && (appData->BufferSize > 0)) {
			/* Received data to be copied*/
			if (LORAWAN_APP_DATA_BUFFER_MAX_SIZE <= appData->BufferSize) {
				ReceivedDataSize = LORAWAN_APP_DATA_BUFFER_MAX_SIZE;
			} else {
				ReceivedDataSize = appData->BufferSize;
			}

			/*asynchronous notification to the host*/
			AT_PRINTF("Received Data:%d:%02X:", appData->Port,
					ReceivedDataSize);

			if (ReceivedDataSize == 2) {
				if (appData->Buffer[0] == Desk_id) {
					if (appData->Buffer[1] == 0x01) {
						HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 1); /* LED_RED */
						HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1); /* LED_RED */
					} else if (appData->Buffer[1] == 0x00) {
						HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 0); /* LED_RED */
						HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0); /* LED_RED */
					} else {
						AT_PRINTF("Wrong Command received\r\n");
					}

				} else if (appData->Buffer[0] == 0x00) {
					if (appData->Buffer[1] == 0x00) {
						HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 0); /* LED_RED */
						HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0); /* LED_RED */
					}else{
						AT_PRINTF("Wrong Command received\r\n");
					}
				} else if (appData->Buffer[0] == 0x01) {
					if (appData->Buffer[1] == 0x01) {
						HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 1); /* LED_RED */
						HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1); /* LED_RED */
					}else{
						AT_PRINTF("Wrong Command received\r\n");
					}
				}
			}
			for (uint8_t i = 0; i < ReceivedDataSize; i++) {
				AT_PRINTF("%02X", appData->Buffer[i]);
			}
			AT_PRINTF("\r\n");
		}
	}

	if ((params != NULL) && (params->RxSlot < RX_SLOT_NONE)) {
		AT_PRINTF("+QEVT:RX_%s, PORT %d, DR %d, RSSI %d, SNR %d",
				slotStrings[params->RxSlot], RxPort, params->Datarate,
				params->Rssi, params->Snr);
		if (params->LinkCheck == true) {
			AT_PRINTF(", DMODM %d, GWN %d", params->DemodMargin,
					params->NbGateways);
		}
		AT_PRINTF("\r\n");
	}
	/* USER CODE END OnRxData_1 */
}

/* USER CODE BEGIN PrFD_LedEvents */

/* USER CODE END PrFD_LedEvents */

static void OnTxData(LmHandlerTxParams_t *params) {
	/* USER CODE BEGIN OnTxData_1 */
	/* USER CODE END OnTxData_1 */
}

static void OnJoinRequest(LmHandlerJoinParams_t *joinParams) {
	/* USER CODE BEGIN OnJoinRequest_1 */
	if ((joinParams != NULL)
			&& (joinParams->Status == LORAMAC_HANDLER_SUCCESS)) {
		AT_PRINTF("DEVICE JOINED\r\n");
		HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, GPIO_PIN_SET); /* LED_GREEN */

	} else {
		AT_PRINTF("DEVICE JOIN FAILED\r\n");
	}
	/* USER CODE END OnJoinRequest_1 */
}

static void OnBeaconStatusChange(LmHandlerBeaconParams_t *params) {
	/* USER CODE BEGIN OnBeaconStatusChange_1 */
	/* USER CODE END OnBeaconStatusChange_1 */
}

static void OnSysTimeUpdate(void) {
	/* USER CODE BEGIN OnSysTimeUpdate_1 */

	/* USER CODE END OnSysTimeUpdate_1 */
}

static void OnClassChange(DeviceClass_t deviceClass) {
	/* USER CODE BEGIN OnClassChange_1 */
	/* USER CODE END OnClassChange_1 */
}

static void CmdProcessNotify(void) {
	/* USER CODE BEGIN CmdProcessNotify_1 */

	/* USER CODE END CmdProcessNotify_1 */
	UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_Vcom), 0);
	/* USER CODE BEGIN CmdProcessNotify_2 */

	/* USER CODE END CmdProcessNotify_2 */
}

static void OnMacProcessNotify(void) {
	/* USER CODE BEGIN OnMacProcessNotify_1 */

	/* USER CODE END OnMacProcessNotify_1 */
	UTIL_SEQ_SetTask((1 << CFG_SEQ_Task_LmHandlerProcess), CFG_SEQ_Prio_0);

	/* USER CODE BEGIN OnMacProcessNotify_2 */

	/* USER CODE END OnMacProcessNotify_2 */
}

static void OnTxPeriodicityChanged(uint32_t periodicity) {
	/* USER CODE BEGIN OnTxPeriodicityChanged_1 */

	/* USER CODE END OnTxPeriodicityChanged_1 */
}

static void OnTxFrameCtrlChanged(LmHandlerMsgTypes_t isTxConfirmed) {
	/* USER CODE BEGIN OnTxFrameCtrlChanged_1 */

	/* USER CODE END OnTxFrameCtrlChanged_1 */
}

static void OnPingSlotPeriodicityChanged(uint8_t pingSlotPeriodicity) {
	/* USER CODE BEGIN OnPingSlotPeriodicityChanged_1 */

	/* USER CODE END OnPingSlotPeriodicityChanged_1 */
	LmHandlerParams.PingSlotPeriodicity = pingSlotPeriodicity;
	/* USER CODE BEGIN OnPingSlotPeriodicityChanged_2 */

	/* USER CODE END OnPingSlotPeriodicityChanged_2 */
}

static void OnSystemReset(void) {
	/* USER CODE BEGIN OnSystemReset_1 */

	/* USER CODE END OnSystemReset_1 */
}

static void OnNvmDataChange(LmHandlerNvmContextStates_t state) {
	/* USER CODE BEGIN OnNvmDataChange_1 */

	/* USER CODE END OnNvmDataChange_1 */
	AT_event_OnNvmDataChange(state);
	/* USER CODE BEGIN OnNvmDataChange_Last */

	/* USER CODE END OnNvmDataChange_Last */
}

static void OnStoreContextRequest(void *nvm, uint32_t nvm_size) {
	/* USER CODE BEGIN OnStoreContextRequest_1 */

	/* USER CODE END OnStoreContextRequest_1 */
	AT_event_OnStoreContextRequest(nvm, nvm_size);
	/* USER CODE BEGIN OnStoreContextRequest_Last */

	/* USER CODE END OnStoreContextRequest_Last */
}

static void OnRestoreContextRequest(void *nvm, uint32_t nvm_size) {
	/* USER CODE BEGIN OnRestoreContextRequest_1 */

	/* USER CODE END OnRestoreContextRequest_1 */
	AT_event_OnRestoreContextRequest(nvm, nvm_size);
	/* USER CODE BEGIN OnRestoreContextRequest_Last */

	/* USER CODE END OnRestoreContextRequest_Last */
}

