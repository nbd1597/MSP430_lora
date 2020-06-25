#include "user_uart.h"

void UART_Init() {
    //UART setup
    UCA0CTL1 |= UCSSEL_1;                           // Select ACLK
    UCA0BR0 |= 0x03;                                // Baudrate: 9600 / Frequency: 32768 Hz
    UCA0BR1 |= 0x00;
    UCA0MCTL = UCBRS1 + UCBRS0;                     // Modulator 3
    UCA0CTL1 &= ~UCSWRST;
    UC0IE |= UCA0RXIE;                              // UART enable
}
