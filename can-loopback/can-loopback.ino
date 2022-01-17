#include <mcp_can.h>

const int ledPin = LED_BUILTIN;

/* for MKR, CS = 3, INT = 7
   for Uno, MS = 9, INT = 2*/
static const byte chipSelectPinMCP = 3;  // CS (chip select) input of MCP2515
static const byte interruptPinMCP = 7; // INT (interrupt) output of MCP2515

static const uint32_t baud = 115200;
static const uint32_t blinkDelayInactive_ms = 100;

MCP_CAN can(chipSelectPinMCP);

void setup() {

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);
    
    pinMode(interruptPinMCP, INPUT);

    Serial.begin(baud);

    while (!Serial) { // blink LED while inactive
        delay(blinkDelayInactive_ms);
        digitalWrite(ledPin, !digitalRead(ledPin)); // toggle LED
    }

    Serial.println("---Initializing CAN.");

    while (uint8_t error = can.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) != CAN_OK) {
        Serial.print("CAN Configuration error: ");
        Serial.println(error);
        delay(1000); // try again after delay
    }

    can.setMode(MCP_LOOPBACK); // redundant since loopback is default. added for clarity.

    Serial.println("---CAN Initialized.");
}

static const uint32_t canTxDelay_ms = 1000;
static long time_ms = 0;

static uint32_t txFrameCount = 0;
static uint32_t rxFrameCount = 0;

void loop() {  

    if (millis() > time_ms + canTxDelay_ms) {
        time_ms = millis(); // new timestamp
        
        Serial.print("time (ms): ");
        Serial.print(millis());
        Serial.print(" | ");

        unsigned long frameId = 1234;
        uint8_t frameLen = 8;
        uint8_t frameData[8] = {0, 1, 2, 3, 4, 5, 6, 7};

        uint8_t txStat = can.sendMsgBuf(frameId, 0, frameLen, frameData);

        if (txStat == CAN_OK) {
            Serial.print("Sending - ID:");
            Serial.print(frameId);

            Serial.print(" Data: ");

            for (int i = 0; i < frameLen; i++) {
                Serial.print(frameData[i]);
                Serial.print(" ");
            }

            Serial.println();

            ++txFrameCount;

            Serial.print("Transmitted Frames: ");
            Serial.println(txFrameCount);
        } else {
            Serial.print("Unable to send CAN frame. Error: ");
            Serial.println(txStat);
        }
    }

    if (!digitalRead(interruptPinMCP)) {

        Serial.print("time (ms): ");
        Serial.print(millis());
        Serial.print(" | ");

        long unsigned int rxID;
        unsigned char rxLen = 0;
        unsigned char rxBuf[8];
        can.readMsgBuf(&rxID, &rxLen, rxBuf);
        rxID = rxID & 0xFFFF;

        Serial.print("Received - ID:");
        Serial.print(rxID);

        Serial.print(" Data: ");

        for (int i = 0; i < rxLen; i++) {
            Serial.print(rxBuf[i]);
            Serial.print(" ");
        }

        Serial.println();

        ++rxFrameCount;

        Serial.print("Received Frames: ");
        Serial.println(rxFrameCount);
    }

}