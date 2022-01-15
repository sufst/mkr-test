
const int baud           = 115200;

/* On MKR Zero, LED_BUILTIN = 32 */
const int ledPin = LED_BUILTIN;

void setup() {
  
    Serial.begin(baud);
    while(!Serial); // Wait for serial monitor to connect

    pinMode(ledPin, OUTPUT);

    Serial.println("Setup Complete.");
}

char c;

void loop() {

    // grab serial input

    if (Serial.available()) {
        digitalWrite(ledPin, HIGH);
        c  = Serial.read();
        delay(10); // slight delay for visible LED
        if (c == '\r')
            Serial.print("\r\n");
        else
            Serial.print(c);
        digitalWrite(ledPin, LOW);
    }
  
}
