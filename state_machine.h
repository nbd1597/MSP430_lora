/*
 * state_machine.h
 *
 *  Created on: Jun 24, 2020
 *      Author: Duy
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "msp430g2553.h"
#include <stdint.h>
#include "user_gpio.h"

void Init_TimerB();
#define AUX_WAIT    1
#define TX_WAIT     2
#define TX          3
#define IDLE        0
volatile uint8_t lora_state;
volatile uint8_t lora_time;
//uint8_t* lora_timeP = &lora_time;

#endif /* STATE_MACHINE_H_ */
