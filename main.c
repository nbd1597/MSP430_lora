
volatile unsigned int i = 0;
unsigned int cmd;
#include "main.h"

Queue buffer_queue;
const char str1[] = ":flip1;";
const char str2[] = ":flip2;";
const char str3[] = ":va_en;";
const char str4[] = ":va_de;";
const char str5[] = ":_time;";

int main(void) {
    TIMER_Init();
    GPIO_Init();
    UART_Init();
    RTC_Init_TimerA();
    Init_TimerB();
    buffer_queue.rear = capacity -1;
    _bis_SR_register(GIE);

    LORA_SwitchMode(MODE_3_SLEEP);
    //LORA_SendParam(PWR_DWN_SAVE, 0x01, 0x23, _8IN1 | BR_9600 | ADR_2_4, 0x23, MODE_TRANS | IO_PP_PU | WK_UP_250 | FEC_ON | PWR_20);
    //LORA_SendCmd(READ_CFG);
    LORA_SwitchMode(MODE_0_NORMAL);

    //LORA_buf = createQueue(128);
    //lora_state = AUX_WAIT;
    //LORA_SendString("abcde");
    LORA_SendData(&buffer_queue, "12345678987654321");
    LORA_SendData(&buffer_queue, "asdfghjk");


    _bis_SR_register(GIE | LPM3_bits); // General interrupt enable / Low power mode 3

    return 0;
}

#pragma vector = USCIAB0RX_VECTOR   // UART interrupt
__interrupt void USCI0RX_ISR()
{

    if (UCA0RXBUF == ':')
    {
        i = 0;
        cmd = 1;
    }

    if (cmd == 1)
    {
        RX_buf[i++] = UCA0RXBUF;
    }

    if (UCA0RXBUF == ';')
    {
        cmd = 0;

        if (!strcmp(str1, RX_buf)) {
            P1OUT |= LED1;
            P1OUT &= ~LED2;
            P2OUT |= VAL_IN1;
            P2OUT &= ~VAL_IN2;
        } else if (!strcmp(str2, RX_buf)) {
            P1OUT |= LED2;
            P1OUT &= ~LED1;
            P2OUT &= ~VAL_IN1;
            P2OUT |= VAL_IN2;
        } else if (!strcmp(str3, RX_buf)) {
            P2OUT |= VAL_EN;
        } else if (!strcmp(str4, RX_buf)) {
            P2OUT &= ~VAL_EN;
        } else if (!strcmp(str5, RX_buf)) {
            lora_state = AUX_WAIT;
            return_time(&rtc, &buffer_queue);
            //LORA_SendData("12345678");

        }

    //if (UCA0RXBUF == 0x24)
      //  P1OUT |= LED2;
    }
}
#pragma vector = USCIAB0TX_VECTOR                   // Send an array to the buffer
__interrupt void USCI0TX_ISR()
{
    if (!isEmpty(&buffer_queue))
    {
        UCA0TXBUF = dequeue(&buffer_queue);
    }

    /*if (UCA0TXBUF == '\0')
    {
        UC0IE &= ~UCA0TXIE;
        TX_en = 0;
        lora_state = AUX_WAIT;
        i = 0;
    }*/

}
/*
#pragma vector = PORT1_VECTOR
__interrupt void Interrupt_LED() {
    // P1OUT &= ~LED1;
    LORA_SendParam(PWR_DWN_SAVE, 0x01, 0x23, _8IN1 | BR_9600 | ADR_2_4, 0x17, MODE_TRANS | IO_PP_PU | WK_UP_250 | FEC_ON | PWR_20);
    P1IFG &= ~BIT3;


    //UC0IE |= UCA0TXIE;
    //P1IFG &= ~BIT3;

}
*/
