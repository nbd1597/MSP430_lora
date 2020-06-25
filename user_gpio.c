#include "user_gpio.h"

void set_output(unsigned int port_num, uint8_t PINx) {
    if (port_num == 1) {
        P1DIR |= PINx;
        P1OUT &= ~PINx;
    } else if (port_num == 2) {
        P2DIR |= PINx;
        P2OUT &= ~PINx;
    }
}

void set_input(unsigned int port_num, uint8_t PINx, PullState GPIO_PullState) {
    if (port_num == 1) {
        P1DIR &= ~PINx;
        P1REN |= PINx;
        if (GPIO_PullState == PULL_HIGH)
            P1OUT |= PINx;
        else P1OUT &= ~PINx;
    } else if (port_num == 2) {
        P2DIR &= ~PINx;
        P2REN |= PINx;
        if (GPIO_PullState == PULL_HIGH)
            P2OUT |= PINx;
        else P2OUT &= ~PINx;
    }
}

void GPIO_Init() {
    // Alternate function for UART
    P1SEL |= RXD | TXD;
    P1SEL2 |= RXD | TXD;
    P1OUT &= ~(RXD | TXD);

    set_output(1, LED1 | LED2 | M0 | M1);
    set_output(2, VAL_EN | VAL_IN1 | VAL_IN2);
    set_input(1, AUX, PULL_HIGH);

    // Enable interrupt for AUX pin
    //P1IE |= AUX;
    //P1IES |= AUX;
    //P1IFG &= ~AUX;
}
