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
#include "main.h"
#include "menu.h"
#include "func.h"

static float batt_voltage = 12.2;
static float batt_current = 2.4;
static float vsel = 4.4;
static float csel = 1.7;

float getBattVoltage()
{
    return batt_voltage;
}

float getBattCurrent()
{
    return batt_current;
}

float getVsel()
{
    return vsel;
}

float getCsel()
{
    return csel;
}

int main()
{
    Menu(0);
    increase_marker_position(); // Rotary enc, rotate cw
    increase_marker_position();
    increase_marker_position();
    increase_marker_position();
    decrease_marker_position(); // Rotary enc, rotate ccw
    decrease_marker_position();
    decrease_marker_position();

    CallbackFunctionFromMenuItem(GetMenuTarget(), GetMenuItemFunction()); // Select button
    increase_marker_position();
    increase_marker_position();
    CallbackFunctionFromMenuItem(GetMenuTarget(), GetMenuItemFunction());
    CallbackFunctionFromMenuItem(GetMenuTarget(), GetMenuItemFunction());
    increase_marker_position();
    CallbackFunctionFromMenuItem(GetMenuTarget(), GetMenuItemFunction());

    return 0;
}
