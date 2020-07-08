#include "user_rtc.h"
#include "user_lora.h"
#include <string.h>

uint8_t str7[16];

const unsigned int days_of_month[12][2] = {
    31,     31,                     // January
    28,     29,                     // February
    31,     31,                     // March
    30,     30,                     // April
    31,     31,                     // May
    30,     30,                     // June
    31,     31,                     // July
    31,     31,                     // August
    30,     30,                     // September
    31,     31,                     // October
    30,     30,                     // November
    31,     31                      // December
};

void RTC_Init_TimerA() {
    // Timer A configs
    TA0CTL = TACLR;                                     // Timer A setting clear
    TA0CTL |= TASSEL_1 | MC_1 | ID_3;                   // Clock source ACLK / Up Mode / Input divider: 8
    TA0CCTL0 |= CCIE;                                   // Enable capture / compare interrupt enable
    TA0CCR0  = 4096 - 1;                                // 32768Hz / 8 = 4096Hz -> 1s per interrupt

    // Initialize RTC structure
    rtc.second = 0x00;
    rtc.minute = 0x00;
    rtc.hour = 0x00;
    rtc.day = 0x00;
    rtc.month = 0x00;
    rtc.year = 0x00;
}


inline static unsigned int is_leap_year(const int x) {
    if (x & 3) return 0;                                // Not divisible by 4
    switch (x % 400) {                                  // Divisible by 4 but not 400
        case 100:
        case 200:
        case 300: return 0;
    }
    return 1;
}

#pragma vector = TIMER0_A0_VECTOR                       // CCR0 ISR
__interrupt void Timer_A_CCR0 (void) {
    // P1OUT ^= LED1;
    rtc.second++;
    //sprintf(str7, "%d-%d--%d---%d----%d", rtc.second, rtc.minute, rtc.hour, rtc.day, rtc.month);
    //LORA_SendString(str7);
    if (rtc.second >= 60) {
        // P1OUT ^= LED2;
        rtc.second = 0;
        rtc.minute++;
        if (rtc.minute >= 60) {
            rtc.minute = 0;
            rtc.hour++;
            if (rtc.hour >= 24) {
                rtc.hour = 0;
                rtc.day++;
                if (rtc.day >= days_of_month[rtc.month][is_leap_year(rtc.year + 1900)]) {
                    rtc.day = 0;
                    rtc.month++;
                    if (rtc.month >= 12) {
                        rtc.month = 0;
                        rtc.year++;
                    }
                }
            }
        }
    }
}
