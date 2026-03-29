/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "i2c-lcd.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t config=0;
uint8_t ativo=0;
uint8_t deb=0;
uint8_t temp_sub=3;
char str_temp_sub[2];
uint8_t temp_des=3;
char str_temp_des[2];
uint8_t config_tela=0;
uint8_t emerg=0;

char str_estado[20];
char str_corrente[20];
char str_temp_res[20];
char str_velocidade[20];
int tempo_res;
char estado[10];
float corrente;
int velocidade;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void configuracao(void);
void emergencia(void);
void tela_principal(void);
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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  lcd_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  tela_principal();
	  configuracao();
	  emergencia();

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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	  if(GPIO_Pin == GPIO_PIN_0)
	  {
		  if(!config && !ativo && !config_tela && !emerg)
		  {
		    config=1;
		    config_tela=1;
		  }
	  }

	  if(GPIO_Pin == GPIO_PIN_4)
	  {
		  if(!config && !ativo && !config_tela)// trocar !ativo para ativo no fim dos testes
		  {
			  emerg=1;
		  }
	  }
}


void configuracao(void)
{
	while(config)
	{
		if(!(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3) && GPIO_PIN_3))
		{
			deb=1;
			HAL_Delay(200);
		}

		if(config_tela==1)
		{
			if(!(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1) && GPIO_PIN_1))
			{
				temp_sub--;
				HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
				HAL_Delay(200);
			}

			if(!(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2) && GPIO_PIN_2))
			{
				temp_sub++;
				HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
				HAL_Delay(200);
			}

			if(temp_sub<3)
			{
				temp_sub=3;
			}


			if(temp_sub>55)
			{
				temp_sub=55;
			}

			sprintf(str_temp_sub,"%d",temp_sub);

			lcd_clear();
			lcd_send_cmd (0x80|0x41);
			lcd_send_string("Tempo de Subida(s)");
			lcd_send_cmd (0x80|0x1D);
			lcd_send_string(str_temp_sub);
			lcd_send_cmd (0x80|0x54);
			lcd_send_string(" ");

			if(deb)
			{
			   config_tela=2;
			   deb=0;
			}
		}

		else if(config_tela==2)
		{
			if(!(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1) && GPIO_PIN_1))
			{
				temp_des--;
				HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
				HAL_Delay(200);
			}

			if(!(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2) && GPIO_PIN_2))
			{
				temp_des++;
				HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
				HAL_Delay(200);
			}

			if(temp_des<3)
			{
				temp_des=3;
			}

			if(temp_des>55)
			{
				temp_des=55;
			}

			sprintf(str_temp_des,"%d",temp_des);

			lcd_clear();
			lcd_send_cmd (0x80|0x41);
			lcd_send_string("Tempo de Descida(s)");
			lcd_send_cmd (0x80|0x1D);
			lcd_send_string(str_temp_des);

			if(deb)
			{
				config_tela=0;
				config=0;
				deb=0;
				lcd_send_cmd (0x1);
				HAL_Delay(10);
			}
		}
	}
}

void emergencia(void)
{
	while(emerg)
	{
		lcd_clear();
		config_tela=0;
		config=0;
		deb=0;

		lcd_send_cmd (0x80|0x47);
		lcd_send_string("PARADA");
		lcd_send_cmd (0x80|0x1B);
		lcd_send_string("MANUAL");

		if(!(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3) && GPIO_PIN_3))
			{
				emerg=0;
				lcd_clear();
			}


	};
}

void tela_principal(void)
{
	lcd_clear();
	sprintf(str_estado,"Estado: %s S", estado);
	sprintf(str_corrente,"Corrente: %.2f mA", corrente);
	sprintf(str_velocidade,"Velocidade: %i RPM",velocidade);
	sprintf(str_temp_res,"Tempo Restante: %i S",tempo_res);
	lcd_send_cmd (0x80|0x00);
	lcd_send_string(str_estado);
	lcd_send_cmd (0x80|0x40);
	lcd_send_string(str_corrente);
	lcd_send_cmd (0x80|0x14);
	lcd_send_string(str_velocidade);
	lcd_send_cmd (0x80|0x54);
	lcd_send_string(str_temp_res);
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
