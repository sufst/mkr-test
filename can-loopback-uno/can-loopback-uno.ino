#include <ACAN2515.h>

#include <SPI.h>

const int ledPin = LED_BUILTIN;

static const byte MCP2515_CS = 9;  // CS (chip select) input of MCP2515
static const byte MCP2515_INT = 2; // INT (interrupt) output of MCP2515

//  MCP2515 Quartz Frequency
static const uint32_t QUARTZ_FREQUENCY = (16UL * 1000UL * 1000UL); // 16 MHz

static const uint32_t baud = 9600;
static const uint32_t blink_delay_ms_inactive = 100;

//  MCP2515 Driver object
ACAN2515 can(MCP2515_CS, SPI, MCP2515_INT);

void setup() {

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, HIGH);

    Serial.begin(baud);

    while (!Serial) { // blink LED while inactive
        delay(blink_delay_ms_inactive);
        digitalWrite(ledPin, !digitalRead(ledPin)); // toggle LED
    }

    Serial.println("---Initializing SPI.");
    SPI.begin();
    Serial.println("---SPI initialized.");

    Serial.println("---Initializing CAN.");

    // Match ECU bit-rate (1Mb/s)
    ACAN2515Settings settings(QUARTZ_FREQUENCY, 1000UL * 1000UL);

    settings.mRequestedMode = ACAN2515Settings::LoopBackMode; // Enable Loopback Mode

    const uint16_t errorCode = can.begin(settings, [] { 
            can.isr(); 
        }
    );

    if (errorCode == 0) {
        
        Serial.print("Bit Rate prescaler: ");
        Serial.println(settings.mBitRatePrescaler);

        Serial.print("Propagation Segment: ");
        Serial.println(settings.mPropagationSegment);

        Serial.print("Phase segment 1: ");
        Serial.println(settings.mPhaseSegment1);

        Serial.print("Phase segment 2: ");
        Serial.println(settings.mPhaseSegment2);

        Serial.print("SJW: ");
        Serial.println(settings.mSJW);

        Serial.print("Triple Sampling: ");
        Serial.println(settings.mTripleSampling ? "yes" : "no");

        Serial.print("Actual bit rate: ");
        Serial.print(settings.actualBitRate());

        Serial.println(" bit/s");
        Serial.print("Exact bit rate ? ");

        Serial.println(settings.exactBitRate() ? "yes" : "no");
        Serial.print("Sample point: ");

        Serial.print(settings.samplePointFromBitStart());
        Serial.println("%");

    } else {

        Serial.print("Configuration error 0x");
        Serial.println(errorCode, HEX);

    }

    Serial.println("---CAN Initialized.");
}

//----------------------------------------------------------------------------------------------------------------------

static uint32_t gBlinkLedDate = 0;
static uint32_t gReceivedFrameCount = 0;
static uint32_t gSentFrameCount = 0;

//——————————————————————————————————————————————————————————————————————————————

void loop() {
    CANMessage frame;

    if (gBlinkLedDate < millis()) {

        gBlinkLedDate += 2000;
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle LED
        
        const bool ok = can.tryToSend(frame);
        
        if (ok) {
            gSentFrameCount += 1;
            Serial.print("Sent: ");
            Serial.println(gSentFrameCount);
        } else {
            Serial.println("Send failure");
        }
    }
    
    if (can.available()) {
        can.receive(frame);

        gReceivedFrameCount++;
        
        Serial.print("Received: ");
        Serial.println(gReceivedFrameCount);
    }
}

//——————————————————————————————————————————————————————————————————————————————
