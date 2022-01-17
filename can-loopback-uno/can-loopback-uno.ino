#include <mcp_can.h>

#include <SPI.h>

const int ledPin = LED_BUILTIN;

static const byte chipSelectPinMCP = 9;  // CS (chip select) input of MCP2515
static const byte interruptPinMCP = 2; // INT (interrupt) output of MCP2515

//  MCP2515 Quartz Frequency
static const uint32_t quartzFrequencyMCP = (16UL * 1000UL * 1000UL); // 16 MHz

static const uint32_t baud = 115200;
static const uint32_t blinkDelayInactive_ms = 100;

static const uint32_t canTxDelay_ms = 1000;

//  MCP2515 Driver object
// ACAN2515 can(chipSelectPinMCP, SPI, interruptPinMCP);
MCP_CAN can(chipSelectPinMCP);

void setup() {

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);

    Serial.begin(baud);

    while (!Serial) { // blink LED while inactive
        delay(blinkDelayInactive_ms);
        digitalWrite(ledPin, !digitalRead(ledPin)); // toggle LED
    }

    // Serial.println("---Initializing SPI.");
    // SPI.begin();
    // Serial.println("---SPI initialized.");

    // Serial.println("---Initializing CAN.");

    // Match ECU bit-rate (1Mb/s)
    // ACAN2515Settings settings(quartzFrequencyMCP, 1000UL * 1000UL);

    // settings.mRequestedMode = ACAN2515Settings::LoopBackMode; // Enable Loopback Mode

    // const uint16_t errorCode = can.begin(settings, [] { 
    //         can.isr(); 
    //     }
    // );

    while (uint8_t error = can.begin(MCP_ANY, CAN_1000KBPS, MCP_16MHZ) != CAN_OK) {
        Serial.print("CAN Configuration error: ");
        Serial.println(error);
        delay(500); // try again after delay
    }

    can.setMode(MCP_LOOPBACK); // redundant since loopback is default. added for clarity.


    // if (errorCode == 0) {
        
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

    // } else {

    //     Serial.print("Configuration error 0x");
    //     Serial.println(errorCode, HEX);

    // }

    Serial.println("---CAN Initialized.");
}

//----------------------------------------------------------------------------------------------------------------------

static uint32_t gBlinkLedDate = 0;
static uint32_t gReceivedFrameCount = 0;
static uint32_t gSentFrameCount = 0;

//——————————————————————————————————————————————————————————————————————————————

void loop() {
    // CANMessage frame;

    unsigned long frameId = 1234;
    uint8_t frameLen = 8;
    uint8_t frameData[8] = {0, 1, 2, 3, 4, 5, 6, 7};

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
    
    // if (can.available()) {
    //     can.receive(frame);

    //     gReceivedFrameCount++;
        
    //     Serial.print("Received: ");
    //     Serial.println(gReceivedFrameCount);
    // }
}

//——————————————————————————————————————————————————————————————————————————————
