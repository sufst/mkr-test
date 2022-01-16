/*************************************************************************//**
* @file sys__manager.cpp
* @brief System manager 
* @copyright    Copyright (C) 2019  SOUTHAMPTON UNIVERSITY FORMULA STUDENT TEAM

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*****************************************************************************/
/*----------------------------------------------------------------------------
  include files
----------------------------------------------------------------------------*/
#include "sys__manager.h"
#include "../srv/srv__comms.h"
#include "sys__datastore.h"


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
sys__ecu_datastore_t sys__ecu_datastore;

/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/

/*************************************************************************//**
* @brief Initialises the system
* @param None
* @return None
* @note
*****************************************************************************/
void sys__manager__init()
{

    // Initialise CAN MCP2515
#if SYS__MANAGER__CAN_BUS_ENABLED 
    srv__comms__can_init(SYS__MANAGER__CAN_CS_PIN);
#endif // SYS__MANAGER__CAN_BUS_ENABLED
    Serial.println("SYSTEM INIT FINISHED");
}

/*************************************************************************//**
* @brief services loops
* @param None
* @return None
* @note
*****************************************************************************/
void sys__manager__process()
{
    srv__comms__process(sys__ecu_datastore);
    delay(1000);
}
/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/
