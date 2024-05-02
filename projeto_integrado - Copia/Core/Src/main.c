/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7789\st7789.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define WHITE       0xFFFF
#define BLACK       0x0000
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define RED         0xF800
#define YELLOW      0xFFE0
#define BOTAO01 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)  //ATRAS/ESQUERDA
#define BOTAO02 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) //PRA BAIXO
#define BOTAO03 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) //FRENTE/DIREITA
#define BOTAO04 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) //PRA CIMA
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
ST7789_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	        ST7789_Fill_Color(MAGENTA);
	  	  ST7789_WriteString(50, 20, "SNAKE.IO", Font_16x26, WHITE, MAGENTA);
	  	  ST7789_WriteString(70, 100, "PLAY=PA11",Font_11x18, WHITE, MAGENTA);
	  	  ST7789_WriteString(40, 180, "VELOCIDADE=PA12", Font_11x18, WHITE, MAGENTA);
	  	  HAL_Delay(2000);

	  	  if (BOTAO01 == 1 && BOTAO02 == 1 && BOTAO03 == 0 && BOTAO04 == 1) {
	  		  ST7789_Fill_Color(BLACK);

	  	      		//COMEÇA O JOGO (PARTE FABI)
	  	      	}

	  	  else if (BOTAO01 == 1 && BOTAO02 == 1 && BOTAO03 == 1 && BOTAO04 == 0) {
	  		 ST7789_Fill_Color(BLACK);
		  	 ST7789_WriteString(50, 20, "VEOCIDADES", Font_16x26, WHITE, BLACK);
		   	 ST7789_WriteString(50, 100, "1=PA9",Font_11x18, WHITE, BLACK);
		  	 ST7789_WriteString(50, 140, "2=PA10", Font_11x18, WHITE, BLACK);
		  	 ST7789_WriteString(50, 180, "3=PA11", Font_11x18, WHITE, BLACK);
		  	 HAL_Delay(2000);


	  	   if (BOTAO01 == 0 && BOTAO02 == 1 && BOTAO03 == 1 && BOTAO04 == 1) {
	  			ST7789_Fill_Color(GREEN);
			   	ST7789_WriteString(50, 120, "VELOCIDADE 1",Font_16x26, WHITE, GREEN);
	  			HAL_Delay(2000);
            }
           else if (BOTAO01 == 1 && BOTAO02 == 0 && BOTAO03 == 1 && BOTAO04 == 1) {
	  			ST7789_Fill_Color(YELLOW);
	  			ST7789_WriteString(50, 120, "VELOCIDADE 2",Font_16x26, WHITE, YELLOW);
	  			HAL_Delay(2000);
            }
	  		else if (BOTAO01 == 1 && BOTAO02 == 1 && BOTAO03 == 0 && BOTAO04 == 1) {
	  			ST7789_Fill_Color(RED);
	  			ST7789_WriteString(50, 120, "VELOCIDADE 3",Font_16x26, WHITE, RED);
	  			HAL_Delay(2000);

	       //AINDA NAO ESTA FUNCIONANDO!!!
	  		}
	  	  }




    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7789_CS_GPIO_Port, ST7789_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7789_DC_Pin|ST7789_RST_Pin|LED1_Pin|LED2_Pin
                          |LED3_Pin|LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7789_CS_Pin */
  GPIO_InitStruct.Pin = ST7789_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7789_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7789_DC_Pin ST7789_RST_Pin LED1_Pin LED2_Pin
                           LED3_Pin LED4_Pin */
  GPIO_InitStruct.Pin = ST7789_DC_Pin|ST7789_RST_Pin|LED1_Pin|LED2_Pin
                          |LED3_Pin|LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BOTAOP_E_Pin BOTAOP_B_Pin BOTAOP_D_Pin BOTAOP_C_Pin */
  GPIO_InitStruct.Pin = BOTAOP_E_Pin|BOTAOP_B_Pin|BOTAOP_D_Pin|BOTAOP_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/