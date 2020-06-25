#ifndef USER_GPIO_H_
#define USER_GPIO_H_

#include <stdint.h>
#include <msp430.h>
#include <string.h>

// Port 1
#define LED1    BIT0
#define RXD     BIT1
#define TXD     BIT2
#define M0      BIT3
#define M1      BIT4
#define AUX     BIT5
#define LED2    BIT6

// Port 2
#define EN_9V   BIT0
#define VAL_EN  BIT1
#define VAL_IN1 BIT2
#define VAL_IN2 BIT3
#define LED_DB  BIT5

typedef enum {
    PULL_HIGH = 0,
    PULL_LOW = !PULL_HIGH
} PullState;

void set_output(unsigned int port_num, uint8_t PINx);
void set_input(unsigned int port_num, uint8_t PINx, PullState GPIO_PullState);
void GPIO_Init();

#endif /* USER_GPIO_H_ */
