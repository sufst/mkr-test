#include "rtc.h"

void setup() {
    Serial.begin(115200);

    initRTC();
}

void loop() {

    Serial.print("date: ");
    String date = getDate();
    Serial.print(date);

    Serial.print("| time: ");
    String time = getTime();
    Serial.println(time);

    long delay_ms = random(100, 2000);

    Serial.print("delay: ");
    Serial.println(delay_ms);
    Serial.println();

    delay(delay_ms); // random delay

}