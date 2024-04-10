#ifndef __SERVO_H
#define __SERVO_H
#include "stm32f4xx_hal.h"
#include "stdint.h"

/**
 * @brief Fonction pour modifier la position du servo-moteur selon 3 positions avec des délais.
 */
void loop_servo_delay(void);

/**
 * @brief Fonction pour modifier la position du servo-moteur avec l'appuie sur un bouton poussoir.
 */
void loop_servo_button(void);

/**
 * @brief Fonction pour définir la position du servo.
 * @param position La position du servo (entre 0 et 100).
 */
void setServoPosition(int position);

#endif
