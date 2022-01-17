# mkr-test

A set of test programs for Arduino MKR Zero.

The `res/` folder contains useful resources, including a diagram of the board pinout and the SAMD21 processor datasheet.

---

## General

### `helloworld`

Prints "Hello, World!" to the serial port.

### `blink`

Blinks the onboard LED.

### `echo-serial`

Echoes serial port input.

---

## XBee

### `xbee-tx-no-api`

Transmits payload in transparent mode (raw bytes over serial).

For this test, both XBees must be configured to use transparent mode (parameter AP = API disabled [0]).

### `xbee-tx`

Transmits payload in API mode using the (xbee-arduino)[https://github.com/andrewrapp/xbee-arduino] library.
Check the (developer guide)[https://github.com/andrewrapp/xbee-arduino/wiki/Developers-Guide] for more information on the library.

For this test, both XBees must be configured to use transparent mode (parameter AP = API enabled with escaped characters [2]).

---

## CAN

### `can-loopback-uno`

Sends CAN messages using (ACAN2515)[https://github.com/pierremolinaro/acan2515] library in loopback mode. 
Use this to verify the CAN shield functions correctly.

Adapted from ACAN2515 `LoopBackDemo.ino` example.

### `ecu-uno`

A program for the Arduino Uno that emulates the DTAFast S60 Pro ECU (Engine Control Unit) CAN communication using the (mcp_can)[https://github.com/coryjfowler/MCP_CAN_lib] library by coryjfowler.

Use this when bench-testing CAN communications with the ECU.