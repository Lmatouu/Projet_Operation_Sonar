#ifndef __SERVO_H
#define __SERVO_H
#include "stm32f4xx_hal.h"
#include "stdint.h"

void loop_servo_delay(void);

void loop_servo_buton(void);

void loop_servo_send_uart(void);

void loop_servo_uart(void);
#endif
