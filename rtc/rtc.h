#ifndef RTC_TEST_H
#define RTC_TEST_H

#include "Arduino.h"
#include <RTCZero.h>

static RTCZero rtc;

void initRTC(uint8_t hours=0, uint8_t minutes=0, uint8_t seconds=0);

String getDate();
String getTime();

#endif // RTC_TEST_H