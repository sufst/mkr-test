/*************************************************************************//**
* @file srv__comms.cpp
* @brief CAN communications service layer
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
#include "srv__comms.h"

#include "../sys/sys__manager.h"
#include "../sys/sys__datastore.h"


#if SYS__MANAGER__CAN_BUS_ENABLED
#include "../dev/dev__can__mcp2515.h"
#endif // SYS__MANAGER__CAN_BUS_ENABLED
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


/*----------------------------------------------------------------------------
  static variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  public functions
----------------------------------------------------------------------------*/
#if SYS__MANAGER__CAN_BUS_ENABLED
/*************************************************************************//**
* @brief Initialise MCP2515 CAN
* @param uint8_t pinCS Pin number of connection to SPI CS of MCP2515
* @return None
* @note
*****************************************************************************/
void srv__comms__can_init(uint8_t pinCS)
{  
  dev__can__mcp2515__init();
}


/*************************************************************************//**
* @brief Communications service process loop
* @param sys__datastore_t dataStore
* @param uint8_t canID
* @return None
* @note
*****************************************************************************/
void srv__comms__process(sys__ecu_datastore_t dataStore)
{ 

  dev__can__mcp2515_tx(dataStore, DEV__CAN__CMD_2000);
  delay(1000);
  dev__can__mcp2515_tx(dataStore, DEV__CAN__CMD_2001);
  delay(1000);
  dev__can__mcp2515_tx(dataStore, DEV__CAN__CMD_2002);
  delay(1000);
  dev__can__mcp2515_tx(dataStore, DEV__CAN__CMD_2003);
  delay(1000);
  dev__can__mcp2515_tx(dataStore, DEV__CAN__CMD_2004);
  delay(1000);
  dev__can__mcp2515_tx(dataStore, DEV__CAN__CMD_2005);
  delay(1000);
  dev__can__mcp2515_tx(dataStore, DEV__CAN__CMD_2006);
  delay(1000);
  dev__can__mcp2515_tx(dataStore, DEV__CAN__CMD_2007);
  delay(1000);
  

}

#endif // SYS__MANAGER__CAN_BUS_ENABLED

/*----------------------------------------------------------------------------
  private functions
----------------------------------------------------------------------------*/



