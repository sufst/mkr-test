#include <XBee.h>

/* On MKR Zero, LED_BUILTIN = 32 */
const int ledPin = LED_BUILTIN;

/* Serial input buffer */
const int bufferSize = 128;
char buffer[bufferSize];

char c='\0';
int i=0;

void clearBuffer(char buffer[], int size) {
    for (int i=0; i<size; ++i) {
        buffer[i] = '\0';
    }
}

void printBuffer(char buffer[], int size) {
    Serial.print("buffer (size: ");
    Serial.print(size);
    Serial.println(")");

    for (int i=0; i<size; ++i) {
        Serial.print("[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(buffer[i]);
    }
}

/* XBee instance */
XBee xbee = XBee();

/* Cart-side XBee Address */
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x41E758C2);

/* XBee serial baud-rate */
const int xbee_baud = 115200; 

/* XBee payload */
uint8_t payload[bufferSize]; // same size as serial buffer

void xbeeTX(const char buffer[], int size) {
    // todo - implement XBee transmission

    for (int i=0; i<size; ++i) {
        payload[i] = (uint8_t) buffer[i];
    }

    Tx64Request tx = Tx64Request(addr64, payload, sizeof(payload));

    xbee.send(tx);

    Serial.println("Transmission complete.");
}

void setup() {

    Serial.begin(xbee_baud);

    /* This might be buggy since it uses the same Serial.
       Change this to SoftwareSerial? */
    xbee.setSerial(Serial); 

    while(!Serial); // Wait for serial monitor to connect

    pinMode(ledPin, OUTPUT);

    printBuffer(buffer, bufferSize);

    Serial.println("Setup Complete.");
}

void loop() {

    while(!Serial.available()); // wait for input

    digitalWrite(ledPin, HIGH);
    c = Serial.read();

    if (c == '\r') {
        xbeeTX(buffer, i); // transmit payload
        printBuffer(buffer, i);

        clearBuffer(buffer, i);
        i = 0;
    } else if (i < bufferSize) {
        buffer[i] = c;
        ++i;
    }

    delay(5); // slight delay for visible LED
    Serial.print(c);
    digitalWrite(ledPin, LOW);
}
