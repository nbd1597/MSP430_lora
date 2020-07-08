/*
 * main.h
 *
 *  Created on: Jun 26, 2020
 *      Author: Duy
 */

#ifndef MAIN_H_
#define MAIN_H_


#include <msp430.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "user_uart.h"
#include "user_gpio.h"
#include "user_timer.h"
#include "user_rtc.h"
#include "user_lora.h"
#include "state_machine.h"
#include "buffer_queue.h"


uint8_t lora_buf[32];
uint8_t RX_buf[8];
//Queue *LORA_buf;


#endif /* MAIN_H_ */
