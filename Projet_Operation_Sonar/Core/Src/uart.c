#include "uart.h"
#include "gpio.h"
#include "main.h"
#include "usart.h"
#include <string.h>
#include "servo.h"
#include <stdio.h>

static int positionPourcentage = 0;

/**
 * @brief Envoie périodiquement le message "Hello, World!" via UART.
 */
void loop_send_uart_hello_word(void)
{
  char *message = "Hello, World!\n";
  HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), HAL_MAX_DELAY);
  HAL_Delay(1000);
}

/**
 * @brief Affiche un message via UART.
 *
 * @param message Le message à afficher.
 */
void display_uart_message(char *message)
{
  HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), 10);
  HAL_Delay(1000);
}

/**
 * @brief Boucle de réception de commande  UART pour le contrôle du servo.
 */
void loop_received_uart_servo(void)
{
  char messagePasReconnu[60]; // initialisation de la variable messagePasReconnu

  uint8_t data_rx[1];
  data_rx[0] = 0; //initialisation de la valeur de data_rx

  HAL_UART_Receive(&huart2, data_rx, sizeof(data_rx), 10); // réception de la valeur de data_rx via UART

  if (data_rx[0] != 0)
  {
    char message[50];
    sprintf(message, "Message reçu! + data[0] = %c\n", data_rx[0]); 
    // HAL_MAX_DELAY
    HAL_UART_Transmit(&huart2, (uint8_t *)message, strlen(message), 10); // affichage du message envoyé via UART

    char data_char = (char)data_rx[0];
    switch (data_char)
    {
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
      sprintf(messagePasReconnu, "valeur data_rx message pas reconnu valeur data char: %c\n", data_char);

      HAL_UART_Transmit(&huart2, (uint8_t *)messagePasReconnu, strlen(messagePasReconnu), 10);
      break;
    }

    setServoPosition(positionPourcentage);
  }
}
