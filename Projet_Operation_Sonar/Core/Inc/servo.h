#ifndef __SERVO_H
#define __SERVO_H
#include "stm32f4xx_hal.h"
#include "stdint.h"


void loop_servo_delay(void);

void loop_servo_button(void);

void setServoPosition(int position);

#endif
