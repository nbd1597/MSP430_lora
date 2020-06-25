#ifndef USER_RTC_H_
#define USER_RTC_H_

#include <stdint.h>
#include <msp430.h>
#include "user_gpio.h"

typedef volatile struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint8_t year;
} rtc_state;

rtc_state rtc;

void RTC_Init_TimerA();
inline static unsigned int is_leap_year(const int x);

#endif /* USER_RTC_H_ */
