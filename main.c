/**
 *********************************************************************
  * @file           : main.c
  * @brief          : A menu for a 4x20LCD display to use with MCU
  * 
  * This main routine is made for testing the menu by emulating the 
  * rotary encoder and the button for selecting the menu entry thats
  * currently selected -> where the marker is placed.
 *********************************************************************
  * @author Ayleen Weiss, 2021-10-06
  * 
  * 
 *********************************************************************

*/
#include <stdio.h>
#include "menu.h"
#include "func.h"

int main()
{
    Menu(0);
    IncreaseMarkerPosition(); // Rotary enc, rotate cw
    IncreaseMarkerPosition();
    IncreaseMarkerPosition();
    IncreaseMarkerPosition();
    DecreaseMarkerPosition(); // Rotary enc, rotate ccw
    DecreaseMarkerPosition();
    DecreaseMarkerPosition();

    CallbackFunctionFromMenuItem(GetMarkerPosition(), GetMenuItemFunction()); // Select button
    IncreaseMarkerPosition();
    CallbackFunctionFromMenuItem(GetMarkerPosition(), GetMenuItemFunction());

    return 0;
}
