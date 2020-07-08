#ifndef USER_LORA_H_
#define USER_LORA_H_

#include <msp430.h>
#include <stdint.h>
#include "user_gpio.h"
#include "user_uart.h"
#include <stdio.h>
#include "user_rtc.h"
#include "buffer_queue.h"
uint8_t lora_buf[32];
uint8_t TX_en;

// Byte 0 command head
typedef enum {
    PWR_DWN_SAVE = 0xC0,
    READ_CFG = 0xC1,
    PWR_DWN_LOSE = 0xC2,
    READ_MODULE_VER = 0xC3,
    RESET = 0xC4
} CommandType;


// Byte 1 + 2 address


// Byte 3 speed
// UART parity bit
#define _8IN1       0x00
#define _8O1        0x40
#define _8E1        0x80


// UART Baud rate
#define BR_1200     0x00
#define BR_2400     0x08
#define BR_4800     0x10
#define BR_9600     0x18
#define BR_19200    0x20
#define BR_38400    0x28
#define BR_57600    0x30
#define BR_115200   0x38


// Air data rate
#define ADR_0_3     0x00
#define ADR_1_2     0x01
#define ADR_2_4     0x02
#define ADR_4_8     0x03
#define ADR_9_6     0x04
#define ADR_19_2    0x05


// Byte 4 channel, running from 0x00 to 0x1F, channel frequency = 410M + channel * 1M


// Byte 5 option
// Fixed transmission enable bit
#define MODE_TRANS  0x00
#define MODE_FIXED  0x80


// IO drive mode
#define IO_PP_PU    0x40
#define IO_OC_OC    0x00


// Wireless wake up time millisecond
#define WK_UP_250   0x00
#define WK_UP_500   0x80
#define WK_UP_750   0x10
#define WK_UP_1000  0x18
#define WK_UP_1250  0x20
#define WK_UP_1500  0x28
#define WK_UP_1750  0x30
#define WK_UP_2000  0x38


// FEC switch
#define FEC_OFF     0x00
#define FEC_ON      0x04


// Transmission power
#define PWR_20      0x00
#define PWR_17      0x01
#define PWR_14      0x02
#define PWR_10      0x03


// Working mode
typedef enum {
    MODE_0_NORMAL = 0,
    MODE_1_WAKE_UP,
    MODE_2_POWER_SAVE,
    MODE_3_SLEEP
} ModeType;

void LORA_SwitchMode(ModeType);
void LORA_SendCmd(CommandType);
void LORA_SendParam(CommandType, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
void LORA_SendByte(uint8_t);
void LORA_SendString(char *);
void LORA_SendData(Queue* buffer, uint8_t *data);
void return_time(rtc_state *rtc, Queue* buffer);

#endif /* USER_LORA_H_ */
