#ifndef __UART_H
#define __UART_H

/**
 * @brief Envoie périodiquement le message "Hello, World!" via UART.
 */
void loop_send_uart_hello_word(void);


/**
 * @brief Boucle de réception de commande  UART pour le contrôle du servo.
 */
void loop_received_uart_servo(void);


/**
 * @brief Affiche un message via UART.
 * 
 * @param message Le message à afficher.
 */
void display_uart_message(char *message);

#endif
