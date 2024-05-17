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
#include <time.h>
#include <stdio.h>
//#include <stdlib.h>
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

#define BOTAO1 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)  //ESQUERDA
#define BOTAO2 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) //BAIXO
#define BOTAO3 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) //DIREITA
#define BOTAO4 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) //CIMA

#define LED3ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1) //LED3ON
#define LED4ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1) //LED4ON
#define LED5ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1) //LED5ON
#define LED6ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1) //LED6ON

#define LED3OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0) //LED3OFF
#define LED4OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0) //LED4OFF
#define LED5OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0) //LED5OFF
#define LED6OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0) //LED6OFF

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

//Variaveis iniciais da posição da cobra:
int Parte1CX = 60;
int Parte1CY = 120;
int Parte2X = 50;
int Parte2Y = 120;
int Parte3X = 40;
int Parte3Y = 120;
int Parte4X = 30;
int Parte4Y = 120;
int Parte5X = 20;
int Parte5Y = 120;
//Variaveis dinâmicas de posição:
int Parte1FX = 60;
int Parte1FY = 120;

int VelocidadeAndar;
int escolha = 1;
int escolha2 = 1;
int movimentar = 1;
int estado;

int interrompe;
int interrompe2;

int PararDeGerar;

int XFruta, YFruta;

int coletavel = 0;
int coletavel2 = 0;
int recorde = 0;
int direcao;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);

//anthony
void Menu(void);
void Play (void);
void Playning (void);
void Velocidade (void);
void Parte1 (void);
void Parte2 (void);
void Parte3 (void);
void Parte4 (void);
void Parte5 (void);
void Apagar (void);

//nicole
void AtualizarPlacar (void);
void AtualizarRecorde (void);
void AlterarDirecaodeMovimento (void);

//fabiane
void GerarNovoColetavel (void);
void VerificarColisao (void);
void VerificarColeta (void);
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
	  Menu ();
  }
   }

    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
  //}
  /* USER CODE END 3 */
// }

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
void Menu (void){

    ST7789_Fill_Color(BLACK);
    ST7789_WriteString(40, 40, "SNAKE.IO", Font_16x26, WHITE, MAGENTA);
    ST7789_WriteString(40, 100, "PLAY = PA11",Font_11x18, WHITE, MAGENTA);
    ST7789_WriteString(40, 120, "VELOCIDADE = PA12", Font_11x18, WHITE, MAGENTA);
    ST7789_WriteString(40, 140, "RECORDE = ", Font_11x18, WHITE, MAGENTA);
    ST7789_WriteChar(150, 140, recorde + '0', Font_11x18, WHITE, MAGENTA);

  while(escolha){

   if (BOTAO1 == 1 && BOTAO2 == 1 && BOTAO3 == 0 && BOTAO4 == 1) {
   Play();
   escolha = 0;
   }
   else if (BOTAO1 == 1 && BOTAO2 == 1 && BOTAO3 == 1 && BOTAO4 == 0) {
  Velocidade();
  escolha = 0;
     }
   }
}

void Play (void){


   ST7789_Fill_Color(BLACK);
   ST7789_DrawLine(10, 10, 230, 10, WHITE);
   ST7789_DrawLine(230, 10, 230, 190, WHITE);	//tamanho do campo de jogo
   ST7789_DrawLine(230, 190, 10, 190, WHITE);
   ST7789_DrawLine(10, 190, 10, 10, WHITE);

	 Parte1CX = 60;
	 Parte1CY = 120;
	 Parte1FX = 60;
	 Parte1FY = 120;
	 Parte2X = 50;
	 Parte2Y = 120;
	 Parte3X = 40;
	 Parte3Y = 120;
	 Parte4X = 30;
	 Parte4Y = 120;
	 Parte5X = 20;
	 Parte5Y = 120;

coletavel = 0;
ST7789_WriteString(10,200, "Pontos:", Font_16x26, BLACK, GREEN);
ST7789_WriteChar(130,200, coletavel + '0', Font_16x26, BLACK, GREEN);

	Parte1();
	Parte2();
	Parte3();
	Parte4();
	Parte5();
	Playning();
}

int direction = 0;

void Playning(void){

	//Define direction para 0:
	direction = 0;

	//Gera a primeira maçã:
	PararDeGerar = 1;
	GerarNovoColetavel();

	while(movimentar){

		//Define a direção baseado no valor dos botões:
	   if(BOTAO1 == 0 && BOTAO2 == 1 && BOTAO3 == 1 && BOTAO4 == 1){

		   direction = 1; //Esquerda
	   }
	   else if(BOTAO1 == 1 && BOTAO2 == 0 && BOTAO3 == 1 && BOTAO4 == 1){

		   direction = 2; //baixo
	   }
	   else if(BOTAO1 == 1 && BOTAO2 == 1 && BOTAO3 == 0 && BOTAO4 == 1){

		   direction = 3; //direita
	   }
	   else if(BOTAO1 == 1 && BOTAO2 == 1 && BOTAO3 == 1 && BOTAO4 == 0 ){

		   direction = 4; //cima
	   }



	   //Veirifica a rireção que precisa mover:
	   if(direction != 0){

		   if(direction == 1){
			   //Código para mover para esquerda
			   Parte1FX = Parte1CX - 10;

			   Apagar();
			   Parte5X = Parte4X;
			   Parte5Y = Parte4Y;
			   Parte5();
			   Parte4X = Parte3X;
			   Parte4Y = Parte3Y;
			   Parte4();
			   Parte3X = Parte2X;
			   Parte3Y = Parte2Y;
			   Parte3();
			   Parte2X = Parte1CX;
			   Parte2Y = Parte1CY;
			   Parte2();
			   Parte1CX = Parte1FX;
			   Parte1CY = Parte1FY;
			   Parte1();
			   VerificarColeta();
			   VerificarColisao ();

		   }
		   else if(direction == 2){
			   //Código para mover para baixo

			   Parte1FY = Parte1CY + 10;

			   Apagar();
			   Parte5X = Parte4X;
			   Parte5Y = Parte4Y;
			   Parte5();
			   Parte4X = Parte3X;
			   Parte4Y = Parte3Y;
			   Parte4();
			   Parte3X = Parte2X;
			   Parte3Y = Parte2Y;
			   Parte3();
			   Parte2X = Parte1CX;
			   Parte2Y = Parte1CY;
			   Parte2();
			   Parte1CX = Parte1FX;
			   Parte1CY = Parte1FY;
			   Parte1();
			   VerificarColeta();
			   VerificarColisao ();
		   }
		   else if(direction == 3){
			   //Código para mover para direita

			   Parte1FX = Parte1CX + 10;

			   Apagar();
			   Parte5X = Parte4X;
			   Parte5Y = Parte4Y;
			   Parte5();
			   Parte4X = Parte3X;
			   Parte4Y = Parte3Y;
			   Parte4();
			   Parte3X = Parte2X;
			   Parte3Y = Parte2Y;
			   Parte3();
			   Parte2X = Parte1CX;
			   Parte2Y = Parte1CY;
			   Parte2();
			   Parte1CX = Parte1FX;
			   Parte1CY = Parte1FY;
			   Parte1();
			   VerificarColeta();
			   VerificarColisao ();
		   }
		   else if(direction == 4){
			   //Código para mover para cima

			   Parte1FY = Parte1CY - 10;

			   Apagar();
			   Parte5X = Parte4X;
			   Parte5Y = Parte4Y;
			   Parte5();
			   Parte4X = Parte3X;
			   Parte4Y = Parte3Y;
			   Parte4();
			   Parte3X = Parte2X;
			   Parte3Y = Parte2Y;
			   Parte3();
			   Parte2X = Parte1CX;
			   Parte2Y = Parte1CY;
			   Parte2();
			   Parte1CX = Parte1FX;
			   Parte1CY = Parte1FY;
			   Parte1();
			   VerificarColeta();
			   VerificarColisao ();
		   }

	   }
   }
 }

void Velocidade (void){
	     ST7789_Fill_Color(BLACK);
	     ST7789_WriteString(45, 30, "VELOCIDADES", Font_16x26, WHITE, BLACK);
	     ST7789_WriteString(50, 100, "normal = PA9",Font_11x18, WHITE, BLACK);
	     ST7789_WriteString(50, 140, "media = PA10", Font_11x18, WHITE, BLACK);
	     ST7789_WriteString(50, 180, "rapida = PA11", Font_11x18, WHITE, BLACK);
         while (escolha2){

	       if (BOTAO1 == 0 && BOTAO2 == 1 && BOTAO3 == 1 && BOTAO4 == 1) {
	     ST7789_Fill_Color(GREEN);
	     ST7789_WriteString(30, 120, "VELOCIDADE 1",Font_16x26, WHITE, GREEN);
	     escolha2 = 0;
	     VelocidadeAndar = 0;
	     Play ();
	               }
	              else if (BOTAO1 == 1 && BOTAO2 == 0 && BOTAO3 == 1 && BOTAO4 == 1) {
	     ST7789_Fill_Color(YELLOW);
	     ST7789_WriteString(30, 120, "VELOCIDADE 2",Font_16x26, BLACK, YELLOW);
	     escolha2 = 0;
	     VelocidadeAndar = 5;
	     Play ();

	               }
	     else if (BOTAO1 == 1 && BOTAO2 == 1 && BOTAO3 == 0 && BOTAO4 == 1) {
	     ST7789_Fill_Color(RED);
	     ST7789_WriteString(30, 120, "VELOCIDADE 3",Font_16x26, WHITE, RED);
	     escolha2 = 0;
	     VelocidadeAndar = 10;
	     Play ();
	     }
       }
     }
void Apagar(void){
	   ST7789_DrawFilledCircle(Parte5X,Parte5Y, 5, BLACK);
	      //HAL_Delay(VelocidadeAndar);
	   }
void Parte1 (void){
	   ST7789_DrawFilledCircle(Parte1CX,Parte1CY, 5, GREEN);
	   HAL_Delay(VelocidadeAndar);
	   }
void Parte2 (void){
	   ST7789_DrawFilledCircle(Parte2X,Parte2Y, 5, GREEN);
	   HAL_Delay(VelocidadeAndar);
	   }
void Parte3 (void){
	   ST7789_DrawFilledCircle(Parte3X,Parte3Y, 5, GREEN);
	   HAL_Delay(VelocidadeAndar);
	   }
void Parte4 (void){
	   ST7789_DrawFilledCircle(Parte4X,Parte4Y, 5, GREEN);
	   HAL_Delay(VelocidadeAndar);
	   }
void Parte5 (void){
	     ST7789_DrawFilledCircle(Parte5X,Parte5Y, 5, GREEN);
	     HAL_Delay(VelocidadeAndar);
	     }

void GerarNovoColetavel (void) //(melhorar a geração de maçãs)
{
    while(PararDeGerar){

       //srand(time(NULL));

      XFruta = rand() % 22 * 10 + 10; // Valores aleatórios entre 0 e 220 de 10 em 10
      YFruta = rand() % 18 * 10 + 10; // Valores aleatórios entre 0 e 180

    if(XFruta != Parte1FX || YFruta != Parte1FY){
		ST7789_DrawFilledCircle(XFruta, YFruta, 5, RED);
		PararDeGerar = 0;
    }
  }
}

void VerificarColeta(void)
{
    if(XFruta == Parte1FX && YFruta == Parte1FY){
    ST7789_DrawFilledCircle(XFruta, YFruta, 5, BLACK);
    PararDeGerar = 1;
    GerarNovoColetavel();
    AtualizarPlacar();
    }
}

void VerificarColisao (void){

	if(Parte1FX <= 10 || Parte1FX > 230 || Parte1FY <= 10 || Parte1FY > 190){
	LED3ON; //LED3ON
	LED4ON;  //LED4ON
	LED5ON; //LED5ON
	LED6ON; //LED6ON
	HAL_Delay(2000);
	LED3OFF; //LED3OFF
	LED4OFF ;//LED4OFF
	LED5OFF  ;//LED5OFF
	LED6OFF ; //LED6OFF
	escolha = 1;
	AtualizarRecorde ();
	Menu();

}

if(Parte1FX == Parte5X && Parte1FY == Parte5Y){
LED3ON;
LED4ON;
LED5ON;
LED6ON;
HAL_Delay(2000);
LED3OFF;
LED4OFF;
LED5OFF;
LED6OFF;
escolha = 1;
AtualizarRecorde ();
Menu();

}
}

void AtualizarPlacar (void){
    coletavel ++;
    //ST7789_WriteString(10,200, "Pontos:", Font_16x26, BLACK, GREEN);
    ST7789_WriteChar(130,200, coletavel + '0', Font_16x26, BLACK, GREEN);

 /*   if(coletavel > 9){
    coletavel = 0;
    coletavel2 ++;
    ST7789_WriteChar(125,200, coletavel2 + '0', Font_16x26, BLACK, GREEN);

    }*/

}

void AtualizarRecorde (void){
	if (coletavel > recorde){
	recorde = coletavel;
	//ST7789_WriteString(10,199,recorde, Font_16x26, WHITE, BLACK);
	}
}

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
