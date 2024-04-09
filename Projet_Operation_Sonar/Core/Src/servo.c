#include "servo.h"
#include "gpio.h"
#include "main.h"
#include <stm32f4xx_hal_tim.h>
#include "tim.h"
#include "stdint.h"
#include "usart.h"
#include <string.h>

static int positionPourcentage=0;
void setServoPosition(int position);

/**
 * @brief Fonction pour modifier la position du servo-moteur selon 3 positions avec des délais.
 */
void loop_servo_delay(void)
{
  // Définir la position du servo à 200
  setServoPosition(0);
  // Attendre pendant 1 seconde
  HAL_Delay(1000);

  // Définir la position du servo à 400
   setServoPosition(50);
  // Attendre pendant 1 seconde
  HAL_Delay(1000);

  // Définir la position du servo à 600
   setServoPosition(100);
  // Attendre pendant 1 seconde
  HAL_Delay(1000);
}

/**
 * @brief Fonction pour définir la position du servo.
 * @param position La position du servo (entre 0 et 100).
 */
void setServoPosition(int position)
{
  // Convertir la position de 0-100 à 400-800
  int servoPosition = 400 + (position * 4);
  
  // Vérifier si la position dépasse 800
  if (servoPosition > 800)
  {
    servoPosition = 800;
  }
  
  // Vérifier si la position est inférieure à 400
  if (servoPosition < 400)
  {
    servoPosition = 400;
  }
  
  // Définir la nouvelle position du servo
  __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_2, servoPosition);
}

/**
 * @brief Fonction pour modifier la position du servo-moteur avec l'appuie sur un bouton pousoir.
 */
void loop_servo_buton(void)
{
  // État précédent du bouton
  static GPIO_PinState previousButtonState = GPIO_PIN_RESET;

  // Lire l'état actuel du bouton
  GPIO_PinState buttonState = HAL_GPIO_ReadPin(BP_USER_GPIO_Port, BP_USER_Pin);

  // Vérifier si le bouton est enfoncé et si l'état précédent était relâché
  if (buttonState == GPIO_PIN_SET && previousButtonState == GPIO_PIN_RESET)
  {
    // Augmenter la position du servo de 20%  chaque fois que le bouton est enfoncé
    positionPourcentage += 20;
  }
  
  previousButtonState = buttonState;

  // Vérifier si la position dépasse 100%
  if (positionPourcentage > 100)
  {
    // Réinitialiser la position du servo à 0%
    positionPourcentage = 0;
  }
  // Définir la nouvelle position du servo
  setServoPosition(positionPourcentage);
}

void loop_servo_send_uart(void){
  char *message = "Hello, World!\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);
  HAL_Delay(1000);
}


void loop_servo_uart(void){
  uint8_t data[1];
  char *message = "Message envoyé!\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);

  HAL_UART_Receive(&huart2, data, 1, 1000);

  *message = "Message reçu!\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);

  switch(data[0]) {
    case '1':
      positionPourcentage = 0;
      break;
    case '2':
      positionPourcentage = 20;
      break;
    case '3':
      positionPourcentage = 40;
      break;
    case '4':
      positionPourcentage = 60;
      break;
    case '5':
      positionPourcentage = 80;
      break;
    case '6':
      positionPourcentage = 100;
      break;
    default:
      // Valeur non reconnue
      break;
  }

  setServoPosition(positionPourcentage);
}








