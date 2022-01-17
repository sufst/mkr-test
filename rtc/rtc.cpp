#include "rtc.h"

void initRTC(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    
    rtc.begin();
    rtc.setTime(hours, minutes, seconds);
}

String getDate() {

    String date = String(rtc.getYear()) + "/" +
                  String(rtc.getMonth()) + "/" +
                  String(rtc.getDay());

    return date;
}

String getTime() {

    String time = String(rtc.getHours()) + ":" +
                  String(rtc.getMinutes()) + ":" +
                  String(rtc.getSeconds());

    return time;
}