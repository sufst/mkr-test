/*****************************************************************************
* @file srv__comms.cpp
* @brief Communication service layer
* @note
* @author
* @copyright
*****************************************************************************/

/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/

#include "srv__comms.h"

/*----------------------------------------------------------------------------
  manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  prototypes
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  global variables
----------------------------------------------------------------------------*/

MCP_CAN can(COMMS__CAN_CS_PIN); // CAN-bus driver object

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/

/*****************************************************************************
* @brief
* @note   
* @param  void
* @retval void
*****************************************************************************/

void srv__comms__init() {

    Serial.begin(COMMS__SERIAL_BAUD);

#if DEBUG_ENABLED
    while(!Serial) { /* Wait for serial monitor to connect */
        /* Toggle LED while inactive */
        delay(DEBUG_BLINK_DELAY_MS);
        digitalWrite(DEBUG_LED_PIN, !digitalRead(DEBUG_LED_PIN));
    }
#endif // DEBUG_ENABLED

#if COMMS__CAN_ENABLED
    srv__comms__CAN_init();
#endif // COMMS__CAN_ENABLED

#if DEBUG_ENABLED
    Serial.println("---- COMMS Initialized");
#endif // DEBUG_ENABLED

}

/*****************************************************************************
* @brief
* @note   
* @param  void
* @retval void
*****************************************************************************/

void srv__comms__process() {

    srv__comms__CAN_process();

}

/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/

#if COMMS__CAN_ENABLED

/*****************************************************************************
* @brief
* @note   
* @param  void
* @retval void
*****************************************************************************/

void srv__comms__CAN_init() {

#if DEBUG_ENABLED
    Serial.println("----- CAN Initializing");
#endif // DEBUG_ENABLED

    while (uint8_t error = can.begin(MCP_ANY, COMMS__CAN_SPEED, COMMS__CAN_MCP_FREQ) != CAN_OK) {
        
#if DEBUG_ENABLED
        Serial.print("CAN Configuration error: ");
        Serial.println(error);
#endif // DEBUG_ENABLED

        delay(COMMS__CAN_RETRY_MS);
    }

    if (COMMS__CAN_LOOPBACK) 
        can.setMode(MCP_LOOPBACK);

#if DEBUG_ENABLED
    Serial.print("Loopback ");
    Serial.println(COMMS__CAN_LOOPBACK ? "ENABLED" : "DISABLED");
#endif // DEBUG_ENABLED

#if DEBUG_ENABLED
    Serial.println("----- CAN Initialized");
#endif // DEBUG_ENABLED

#if COMMS__CAN_TEST
    srv__comms__CAN_test();
#endif //COMMS__CAN_TEST

}

/*****************************************************************************
* @brief
* @note   
* @param  void
* @retval void
*****************************************************************************/

#if COMMS__CAN_TEST

void srv__comms__CAN_test(const unsigned loops, const unsigned delay_ms) {

#if DEBUG_ENABLED
    Serial.println("------ CAN Test");
#endif // DEBUG_ENABLED

    unsigned time_ms = millis();
    unsigned txFrameCount = 0;
    
    for (unsigned i=0; i<loops; ++i) {

        unsigned long frameId = 1234;
        uint8_t frameLen = 8;
        uint8_t frameData[8] = {0, 1, 2, 3, 4, 5, 6, 7};

        uint8_t txStat = can.sendMsgBuf(frameId, 0, frameLen, frameData);

#if DEBUG_ENABLED
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
#endif //DEBUG_ENABLED

        delay(delay_ms);

    }

#if DEBUG_ENABLED
    Serial.println("------ CAN Test Complete");
#endif // DEBUG_ENABLED

}

#endif // COMMS__CAN_TEST

void srv__comms__CAN_process() {
    if (!digitalRead(COMMS__CAN_INT_PIN)) {


        long unsigned int rxID;
        unsigned char rxLen = 0;
        unsigned char rxBuf[8];
        can.readMsgBuf(&rxID, &rxLen, rxBuf);
        rxID = rxID & 0xFFFF;

#if DEBUG_ENABLED

        Serial.print("Received - ID:");
        Serial.print(rxID);

        Serial.print(" Data: ");

        for (int i = 0; i < rxLen; i++) {
            Serial.print(rxBuf[i]);
            Serial.print(" ");
        }

        Serial.println();

#endif // DEBUG_ENABLED

    }
}

#endif // COMMS__CAN_ENABLED

/*----------------------------------------------------------------------------
  End of file
----------------------------------------------------------------------------*/