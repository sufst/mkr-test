/*************************************************************************//**
* @file ecu-uno.ino
* @brief Emulator of DTA SFast S60 Pro ECU CAN messages
* @copyright Copyright (C) 2019  SOUTHAMPTON UNIVERSITY FORMULA STUDENT TEAM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>
*****************************************************************************/

#include "Arduino.h"
#include "src/sys/sys__manager.h"

void setup() {
    Serial.begin(115200);
    sys__manager__init();
}

void loop() {
    sys__manager__process();
}
