# mkr-test

A set of test programs for Arduino MKR Zero.

The `_resources/` folder contains useful resources, including a diagram of the board pinout and the SAMD21 processor datasheet.

---

## General Tests

### `helloworld`

Prints "Hello, World!" to the serial port.

### `blink`

Blinks the onboard LED.

### `echo-serial`

Echoes serial port input.

### `rtc`

Prints current date and time during random intervals starting from 0/0/0 0:0:0 when powered on.
The RTC is only accurate to 1 second. 

This requires the [RTCZero](https://www.arduino.cc/reference/en/libraries/rtczero/) library.

---

## XBee Tests

### `xbee-tx-no-api`

Transmits payload in transparent mode (raw bytes over serial).

For this test, both XBees must be configured to use transparent mode (parameter AP = API disabled [0]).

### `xbee-tx`

Transmits payload in API mode using the (xbee-arduino)[https://github.com/andrewrapp/xbee-arduino] library.
Check the (developer guide)[https://github.com/andrewrapp/xbee-arduino/wiki/Developers-Guide] for more information on the library.

For this test, both XBees must be configured to use transparent mode (parameter AP = API enabled with escaped characters [2]).

---

## CAN Tests

### `can`

Implements full CAN-bus funcitonality using the [mcp_can](https://github.com/coryjfowler/MCP_CAN_lib) library.
Can be configured in loopback mode.

### `can-loopback`

A simple test that sends CAN messages using the [mcp_can](https://github.com/coryjfowler/MCP_CAN_lib) library in loopback mode. 
Use this to verify the CAN shield functions correctly.

Adapted from the `CAN_loopback.ino` example from [mcp_can](https://github.com/coryjfowler/MCP_CAN_lib).

### `ecu-uno`

A program for the Arduino Uno that emulates the DTAFast S60 Pro ECU (Engine Control Unit) CAN communication using the [mcp_can](https://github.com/coryjfowler/MCP_CAN_lib) library.

Use this when bench-testing CAN communications with the ECU.