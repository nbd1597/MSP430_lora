#include "user_lora.h"
#include "state_machine.h"
#include "main.h"

void LORA_SwitchMode(ModeType mode) {
    if (mode == MODE_0_NORMAL) {                        // Normal mode
        P1OUT &= ~(M0 | M1);
    } else if (mode == MODE_1_WAKE_UP) {                // Wake up mode
        P1OUT &= ~M0;
        P1OUT |= M1;
    } else if (mode == MODE_2_POWER_SAVE) {             // Power-saving mode
        P1OUT |= M0;
        P1OUT &= ~M1;
    } else if (mode == MODE_3_SLEEP) {                   // Sleep mode
        P1OUT |= M0 | M1;
    }
    lora_state = AUX_WAIT;
}

void LORA_SendCmd(CommandType command) {
    unsigned int i = 0;

    //UC0IE |= UCA0TXIE;
    while (i != 3)
        LORA_SendByte(command);
    //UC0IE &= ~UCA0TXIE;
    lora_state = AUX_WAIT;
}

void LORA_SendParam(CommandType command, uint8_t address_high, uint8_t address_low,
                    uint8_t speed, uint8_t channel, uint8_t option) {
    //UC0IE |= UCA0TXIE;

    LORA_SendByte(command);
    LORA_SendByte(address_high);
    LORA_SendByte(address_low);
    LORA_SendByte(speed);
    LORA_SendByte(channel);
    LORA_SendByte(option);

    //UC0IE &= ~UCA0TXIE;
    lora_state = AUX_WAIT;
}

void LORA_SendByte(uint8_t byte) {
/*    while(1)
    {
        if (lora_state == TX_RDY) break;
    }
    UC0IE |= UCA0TXIE;
    while (!(UC0IFG & UCA0TXIFG))
       continue;

    UCA0TXBUF = byte;
    UC0IE &= ~UCA0TXIE;
*/
    lora_buf[0] = byte;
    lora_buf[1] = '\0';
    //TX_en = 1;
}


void LORA_SendData(Queue* buffer, uint8_t *data)
{

    enqueue_string(buffer, data);
    TX_en = 1;
}

void return_time(rtc_state *rtc, Queue* buffer)
{
    uint8_t temp[32];
    sprintf(temp,"1:%d 2:%d 3:%d 4:%d 5:%d 6:%d ?", rtc->second, rtc->minute,rtc->hour,rtc->day,rtc->month,rtc->year);
    enqueue_string(buffer, temp);
    return;
}

