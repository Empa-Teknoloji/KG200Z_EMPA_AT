/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    adc_if.c
  * @author  MCD Application Team
  * @brief   Read status related to the chip (battery level, VREF, chip temperature)
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
#include "adc_if.h"
#include "sys_app.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/**
  * @brief ADC handle
  */
extern ADC_HandleTypeDef hadc;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
#define TEMPSENSOR_TYP_CAL1_V          (( int32_t)  760)        /*!< Internal temperature sensor, parameter V30 (unit: mV). Refer to device datasheet for min/typ/max values. */
#define TEMPSENSOR_TYP_AVGSLOPE        (( int32_t) 2500)        /*!< Internal temperature sensor, parameter Avg_Slope (unit: uV/DegCelsius). Refer to device datasheet for min/typ/max values. */

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief This function reads the ADC channel
  * @param channel channel number to read
  * @return adc measured level value
  */
static uint32_t ADC_ReadChannels(uint32_t channel);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/
/* USER CODE BEGIN EF */

/* USER CODE END EF */

void SYS_InitMeasurement(void)
{
  /* USER CODE BEGIN SYS_InitMeasurement_1 */

  /* USER CODE END SYS_InitMeasurement_1 */
  hadc.Instance = ADC;
  /* USER CODE BEGIN SYS_InitMeasurement_2 */

  /* USER CODE END SYS_InitMeasurement_2 */
}

void SYS_DeInitMeasurement(void)
{
  /* USER CODE BEGIN SYS_DeInitMeasurement_1 */

  /* USER CODE END SYS_DeInitMeasurement_1 */
}

int32_t SYS_GetTemperatureLevel(void)
{
  /* USER CODE BEGIN SYS_GetTemperatureLevel_1 */
	int32_t ADC_ref_3v3 = *VREFINT_CAL_ADDR;  //1517

		int32_t ADC_ref_raw  = ADC_ReadChannels(ADC_CHANNEL_VREFINT);  //1528, as expected close to ADC_ref_3v3 as we run on 3.3V

		// 314 is way off, should be close to the 30C calibration point at 962
		// 944 is read with the 3 seconds delay, which is a sane value corresponding to 22C
		int32_t ADC_T_raw    = ADC_ReadChannels(ADC_CHANNEL_TEMPSENSOR); //314 without delay, 944 with delay

		// The temperature reading as if it had been taken at 3v3, which is the unit needed by the temp-sensor calibration.
		int32_t ADC_T = ADC_T_raw * ADC_ref_3v3 / ADC_ref_raw;  //311

		//Adc values @ 3v3 vref
		int32_t ADC_T0 = *TEMPSENSOR_CAL1_ADDR;   // 962
		int32_t ADC_T1 = *TEMPSENSOR_CAL2_ADDR;   // 1271

		int32_t T0 = TEMPSENSOR_CAL1_TEMP;  // 30
		int32_t T1 = TEMPSENSOR_CAL2_TEMP;  // 130

		// T-t0 = K * (ADC_T - ADC_T0)
		// 1000 * 100 * 4000  (28 bitar som värst, dvs inget overflow möjligt)
		int32_t T = (T1 - T0) * (ADC_T - ADC_T0) / (ADC_T1 - ADC_T0)  + T0;    // -180 without delay, 22 with delay

		return T;
  /* USER CODE END SYS_GetTemperatureLevel_1 */
//  __IO int16_t temperatureDegreeC = 0;
//  uint32_t measuredLevel = 0;
//  uint16_t batteryLevelmV = SYS_GetBatteryLevel();
//
//  measuredLevel = ADC_ReadChannels(ADC_CHANNEL_TEMPSENSOR);
//
//  /* convert ADC level to temperature */
//  /* check whether device has temperature sensor calibrated in production */
//  if (((int32_t)*TEMPSENSOR_CAL2_ADDR - (int32_t)*TEMPSENSOR_CAL1_ADDR) != 0)
//  {
//    /* Device with temperature sensor calibrated in production:
//       use device optimized parameters */
//    temperatureDegreeC = __LL_ADC_CALC_TEMPERATURE(batteryLevelmV,
//                                                   measuredLevel,
//                                                   LL_ADC_RESOLUTION_12B);
//  }
//  else
//  {
//    /* Device with temperature sensor not calibrated in production:
//       use generic parameters */
//    temperatureDegreeC = __LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(TEMPSENSOR_TYP_AVGSLOPE,
//                                                              TEMPSENSOR_TYP_CAL1_V,
//                                                              TEMPSENSOR_CAL1_TEMP,
//                                                              batteryLevelmV,
//                                                              measuredLevel,
//                                                              LL_ADC_RESOLUTION_12B);
//  }
//
//  /* from int16 to q8.7*/
//  temperatureDegreeC <<= 8;
//
//  return (int16_t) temperatureDegreeC;
  /* USER CODE BEGIN SYS_GetTemperatureLevel_2 */

  /* USER CODE END SYS_GetTemperatureLevel_2 */
}

uint16_t SYS_GetBatteryLevel(void)
{
  /* USER CODE BEGIN SYS_GetBatteryLevel_1 */

  /* USER CODE END SYS_GetBatteryLevel_1 */
  uint16_t batteryLevelmV = 0;
  uint32_t measuredLevel = 0;

  measuredLevel = ADC_ReadChannels(ADC_CHANNEL_VREFINT);

  if (measuredLevel == 0)
  {
    batteryLevelmV = 0;
  }
  else
  {
    if ((uint32_t)*VREFINT_CAL_ADDR != (uint32_t)0xFFFFU)
    {
      /* Device with Reference voltage calibrated in production:
         use device optimized parameters */
      batteryLevelmV = __LL_ADC_CALC_VREFANALOG_VOLTAGE(measuredLevel,
                                                        ADC_RESOLUTION_12B);
    }
    else
    {
      /* Device with Reference voltage not calibrated in production:
         use generic parameters */
      batteryLevelmV = (VREFINT_CAL_VREF * 1510) / measuredLevel;
    }
  }

  return batteryLevelmV;
  /* USER CODE BEGIN SYS_GetBatteryLevel_2 */

  /* USER CODE END SYS_GetBatteryLevel_2 */
}

/* Private Functions Definition -----------------------------------------------*/
/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */

static uint32_t ADC_ReadChannels(uint32_t channel)
{
  /* USER CODE BEGIN ADC_ReadChannels_1 */

  /* USER CODE END ADC_ReadChannels_1 */
  uint32_t ADCxConvertedValues = 0;
  ADC_ChannelConfTypeDef sConfig = {0};

  MX_ADC_Init();

  /* Start Calibration */
  if (HAL_ADCEx_Calibration_Start(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  /* Configure Regular Channel */
  sConfig.Channel = channel;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADC_Start(&hadc) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }
  /** Wait for end of conversion */
  HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);

  /** Wait for end of conversion */
  HAL_ADC_Stop(&hadc);   /* it calls also ADC_Disable() */

  ADCxConvertedValues = HAL_ADC_GetValue(&hadc);

  HAL_ADC_DeInit(&hadc);

  return ADCxConvertedValues;
  /* USER CODE BEGIN ADC_ReadChannels_2 */

  /* USER CODE END ADC_ReadChannels_2 */
}
