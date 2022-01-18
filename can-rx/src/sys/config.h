/*************************************************************************//**
* @file config.h
* @brief Configuration file
* @note
* @author
* @copyright
*****************************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

/*----------------------------------------------------------------------------
  macros
----------------------------------------------------------------------------*/

#define DEBUG_ENABLED        true
#define DEBUG_LED_PIN        LED_BUILTIN
#define DEBUG_BLINK_DELAY_MS 1000

#define COMMS_ENABLED true

#define COMMS__SERIAL_BAUD 115200

#define COMMS__CAN_ENABLED   true
#define COMMS__CAN_RETRY_MS  1000
#define COMMS__CAN_LOOPBACK  true
#define COMMS__CAN_CS_PIN    3
#define COMMS__CAN_INT_PIN   7
#define COMMS__CAN_SPEED     CAN_1000KBPS
#define COMMS__CAN_MCP_FREQ  MCP_16MHZ

/* Tests: */
#define COMMS__CAN_TEST      true

/*----------------------------------------------------------------------------
  constants
----------------------------------------------------------------------------*/

#endif //CONFIG_H