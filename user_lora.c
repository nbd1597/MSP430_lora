#include "user_lora.h"
#include "state_machine.h"

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

    UC0IE |= UCA0TXIE;
    while (i != 3)
        LORA_SendByte(command);
    UC0IE &= ~UCA0TXIE;
}

void LORA_SendParam(CommandType command, uint8_t address_high, uint8_t address_low,
                    uint8_t speed, uint8_t channel, uint8_t option) {
    UC0IE |= UCA0TXIE;

    LORA_SendByte(command);
    LORA_SendByte(address_high);
    LORA_SendByte(address_low);
    LORA_SendByte(speed);
    LORA_SendByte(channel);
    LORA_SendByte(option);

    UC0IE &= ~UCA0TXIE;
    lora_state = AUX_WAIT;
}

void LORA_SendByte(uint8_t byte) {
    while(1)
    {
        if (lora_state == TX) break;
    }
    UC0IE |= UCA0TXIE;
    while (!(UC0IFG & UCA0TXIFG))
       continue;

    UCA0TXBUF = byte;
    UC0IE &= ~UCA0TXIE;
}

void LORA_SendString(char *str) {
    /*while (P1IN & AUX)
        continue;*/

    while (*str)
        LORA_SendByte(*str++);
    //LORA_SendByte(0x0A);


    //lora_state = IDLE;
}

void LORA_SendData(uint8_t *data)
{

    strcpy(lora_buf, data);
    //while(lora_state != TX) continue;
    UC0IE |= UCA0TXIE;
}

void LORA_AUXWait() {
    while (P1IN & AUX)
        _delay_cycles(3000);
}
