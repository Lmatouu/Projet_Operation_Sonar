#include "gpio.h"
#include "main.h"
#include <stm32f4xx_hal_tim.h>
#include "tim.h"
#include "ultrasonic.h"
#include <stdio.h>

static int fin = 0;
static int distance = 0;

void calculateDistance()
{
    // ===== FRONT MONTANT =====
    if (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_RESET)
    {
        TIM3->CNT = 0;
    }

    // ===== FRONT DESCENDANT =====
    if (HAL_GPIO_ReadPin(ECHO_GPIO_Port, ECHO_Pin) == GPIO_PIN_SET)
    {
        fin = TIM3->CNT;
        // ===== CALCUL DE LA DISTANCE =====
        distance = fin / 1000;
    }

    displayLed();
}

int getDistance()
{
    return fin;
}

void displayLed()
{
    if (distance < 5 || distance > 25)
    {
        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_ORANGE_GPIO_Port, LED_ORANGE_Pin, GPIO_PIN_SET);
    }
}