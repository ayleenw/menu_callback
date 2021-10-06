#include <stdio.h>
#include "menu.h"
#include "func.h"

#define LINES 4 // Set lines acc. to used LCD
#define TEST 1  // 1 for print to stdout, 0 for write to LCD

#ifndef _TEST_
#define _TEST_
#include "lcd_dummy.h"
#else
#include "i2clcd.h"
#endif // end _TEST_

const char *menuTitle[] = {"Hauptmenue", "Submenue 1", "Submenue 2"};
const int numberOfItems[] = {5, 4, 3};

menuEntry menuEntries[10][10] = {{{"Hmenue 1", Menu, 1}, {"Hmenue 2", Menu, 2}, {"Hmenue 3", Menu, 3}, {"Hmenue 4", Menu, 4}, {"Hmenue 5", Menu, 5}},
                                 {{"Smenue 1_1 LED on", func1, 0}, {"Smenue 1_3 LED off", func2, 1}, {"Smenue 1_3", Menu, 2}, {"Zurueck", Menu, 0}},
                                 {{"Smenue 2_1", Menu, 0}, {"Smenue 2_2", Menu, 1}, {"Zurueck", Menu, 0}}};

int Menu(int id)
{
    if (id != MenuActive)
    {
        MenuItems = numberOfItems[id];
        MenuActive = id;
        StartPosition = 0;
        MarkerPosition = 0;
    }

    int entryPos = StartPosition;

    if (TEST)
    {
        printf("%s\n", menuTitle[id]);
    }
    else
    {
        lcd_write(menuTitle[id], 0, 0);
    }

    for (int i = 1; i < LINES; i++)
    {
        if (entryPos == MarkerPosition)
        {
            if (TEST)
                printf("> ");
            else
                lcd_write("> ", i, 0);
        }
        else
        {
            if (TEST)
                printf("  ");
            else
                lcd_write("  ", i, 0);
        }
        if (TEST)
            printf("%s\n", menuEntries[id][entryPos].menuText);
        else
            lcd_write(menuEntries[id][entryPos].menuText, i, 2);
        entryPos++;
    }

    return 0;
}

void SetMarkerPosition(int position)
{
    MarkerPosition = position;
    // Increasing the marker position
    if (MarkerPosition > StartPosition + LINES - 2)
    {
        SetStartPosition(MarkerPosition - LINES + 2);
    }
    // Decreasing the marker position
    if (MarkerPosition < StartPosition)
    {
        SetStartPosition(MarkerPosition);
    }
    Menu(MenuActive);
}

void IncreaseMarkerPosition()
{
    if (MarkerPosition < MenuItems)
    {
        MarkerPosition++;
        if (MarkerPosition > StartPosition + LINES - 2)
        {
            StartPosition++;
        }
        Menu(MenuActive);
    }
}

void DecreaseMarkerPosition()
{
    if (MarkerPosition > 0)
    {
        MarkerPosition--;
        if (MarkerPosition < StartPosition)
        {
            StartPosition--;
        }
        Menu(MenuActive);
    }
}

int GetMarkerPosition()
{
    return MarkerPosition;
}

op_t GetMenuItemFunction()
{
    return *menuEntries[MenuActive][MarkerPosition].opt;
}

int GetMenuTarget()
{
    return menuEntries[MenuActive][MarkerPosition].target;
}

void SetStartPosition(int position)
{
    StartPosition = position;
}

int GetStartPosition()
{
    return StartPosition;
}

void SetMenuId(int id)
{
    MenuActive = id;
}

int CallbackFunctionFromMenuItem(int param, op_t op)
{
    return op(param);
}