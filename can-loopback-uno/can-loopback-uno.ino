#include <mcp_can.h>

const int ledPin = LED_BUILTIN;

static const byte chipSelectPinMCP = 9;  // CS (chip select) input of MCP2515
static const byte interruptPinMCP = 2; // INT (interrupt) output of MCP2515

static const uint32_t baud = 115200;
static const uint32_t blinkDelayInactive_ms = 100;

static const uint32_t canTxDelay_ms = 1000;

MCP_CAN can(chipSelectPinMCP);

void setup() {

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);

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

    // todo - reimplement:
       
    //     Serial.print("Bit Rate prescaler: ");
    //     Serial.println(settings.mBitRatePrescaler);

    //     Serial.print("Propagation Segment: ");
    //     Serial.println(settings.mPropagationSegment);

    //     Serial.print("Phase segment 1: ");
    //     Serial.println(settings.mPhaseSegment1);

    //     Serial.print("Phase segment 2: ");
    //     Serial.println(settings.mPhaseSegment2);

    //     Serial.print("SJW: ");
    //     Serial.println(settings.mSJW);

    //     Serial.print("Triple Sampling: ");
    //     Serial.println(settings.mTripleSampling ? "yes" : "no");

    //     Serial.print("Actual bit rate: ");
    //     Serial.print(settings.actualBitRate());

    //     Serial.println(" bit/s");
    //     Serial.print("Exact bit rate ? ");

    //     Serial.println(settings.exactBitRate() ? "yes" : "no");
    //     Serial.print("Sample point: ");

    //     Serial.print(settings.samplePointFromBitStart());
    //     Serial.println("%");

    Serial.println("---CAN Initialized.");
}

static uint32_t gBlinkLedDate = 0;
static uint32_t gReceivedFrameCount = 0;
static uint32_t gSentFrameCount = 0;

void loop() {  

    unsigned long frameId = 1234;
    uint8_t frameLen = 8;
    uint8_t frameData[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    // todo - add confirmation of tx success
    can.sendMsgBuf(frameId, 0, frameLen, frameData);

    Serial.print("Sending - ID:");
    Serial.print(frameId);

    Serial.print(" Data: ");

    for (int i = 0; i < frameLen; i++) {
        Serial.print(frameData[i]);
        Serial.print(" ");
    }

    Serial.println();

    delay(canTxDelay_ms);

    // if (gBlinkLedDate < millis()) {

    //     gBlinkLedDate += 2000;
    //     digitalWrite(ledPin, !digitalRead(ledPin)); // toggle LED
        
    //     const bool ok = can.tryToSend(frame);
        
    //     if (ok) {
    //         gSentFrameCount += 1;
    //         Serial.print("Sent: ");
    //         Serial.println(gSentFrameCount);
    //     } else {
    //         Serial.println("Send failure");
    //     }
    // }
    
    // todo - implement CAN rx
    // if (can.available()) {
    //     can.receive(frame);

    //     gReceivedFrameCount++;
        
    //     Serial.print("Received: ");
    //     Serial.println(gReceivedFrameCount);
    // }
}

//——————————————————————————————————————————————————————————————————————————————
