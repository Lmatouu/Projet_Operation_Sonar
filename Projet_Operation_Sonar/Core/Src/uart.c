#include "uart.h"
#include "gpio.h"
#include "main.h"
#include "usart.h"
#include <string.h>
#include "servo.h"

static int positionPourcentage=0;

void loop_send_uart(void){
  char *message = "Hello, World!\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);
  HAL_Delay(1000);
}


void loop_received_uart(void){
  uint8_t data[1];
  char *message = "Message envoyé!\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);

  while (data[0] == 0) {
    HAL_UART_Receive(&huart2, data, 1, 1000);
  }

  message = "Message reçu!\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), HAL_MAX_DELAY);

  switch(data[0]) {
    case 0x01:
      positionPourcentage = 0;
      break;
    case 0x02:
      positionPourcentage = 20;
      break;
    case 0x03:
      positionPourcentage = 40;
      break;
    case 0x04:
      positionPourcentage = 60;
      break;
    case 0x05:
      positionPourcentage = 80;
      break;
    case 0x06:
      positionPourcentage = 100;
      break;
    default:
      // Valeur non reconnue
      break;
  }

  setServoPosition(positionPourcentage);
}








