/*
 * state_machine.c
 *
 *  Created on: Jun 24, 2020
 *      Author: Duy
 */



#include "state_machine.h"
//volatile static uint8_t lora_time = 0;
//uint8_t lora_state;
void Init_TimerB()
{
    TA1CTL = TACLR;                                     // Timer A setting clear
    TA1CTL |= TASSEL_1 | MC_1 | ID_0;                   // Clock source ACLK / Up Mode / Input divider: 1
    TA1CCTL0 |= CCIE;                                   // Enable capture / compare interrupt enable
    TA1CCR0  = 32-1;                                    // 32768Hz / 1 -> ~0.98ms per interrupt

}

//uint8_t* lora_timeP = &lora_time;
//volatile extern uint8_t lora_time = 0;

#pragma vector = TIMER1_A0_VECTOR                       // CCR0 ISR
__interrupt void Timer_A2_CCR0 (void)
{
    lora_time++;
    //if (lora_time == 100) lora_time = 0;
    //if (! (P1IN & AUX)) lora_state = AUX_WAIT;
    switch (lora_state)
    {
    case AUX_WAIT:
        if (P1IN & AUX)
        {
            lora_state = TX_WAIT;
            lora_time = 0;
            UC0IE &= ~UCA0TXIE;
        }
        break;
    case TX_WAIT:
        if (lora_time > 4) lora_state = TX_RDY;

        break;
    case TX_RDY:

        if (!(P1IN & AUX))
        {
            lora_state = AUX_WAIT;
            UC0IE &= ~UCA0TXIE;
        } else
            UC0IE |= UCA0TXIE;
        break;
    case IDLE:
        break;
    }
    P1OUT ^= LED2;
}


