#include <stdio.h>
#include "menu.h"
#include "main.h"
#include "func.h"
#include "i2clcd.h"

#define LINES 4     // Set lines acc. to used LCD
#define COLUMNS 20  // Set columns acc. to used LCD
#define VALUE_LEN 5 // max length for injected live values (-1)
#define TEST 1      // 1 to print to stdout, 0 to write to real LCD

const char *menuTitle[] = {"Hauptmenue", "Submenue 1", "Submenue 2"};
const int numberOfItems[] = {2, 4, 5};

menuEntry menuEntries[10][10] = {{{"Hmenue 1", Menu, 1, NULL}, {"Hmenue 2", Menu, 2, NULL}},
                                 {{"Smenue 1_1 LED on", func1, 0, NULL}, {"Smenue 1_3 LED off", func2, 1, NULL}, {"Gehe zu 2:", Menu, 2, NULL}, {"Zurueck", Menu, 0, NULL}},
                                 {{"Spannung:", NoOp, 0, getBattVoltage}, {"Strom:", NoOp, 0, getBattCurrent}, {"MCU out:", NoOp, 1, getVsel}, {"Gehe zu 1:", Menu, 1, NULL}, {"Zurueck", Menu, 0, NULL}}};

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
            printf("%s", menuEntries[id][entryPos].menuText);
        else
            lcd_write(menuEntries[id][entryPos].menuText, i, 2);
        if (menuEntries[id][entryPos].value != NULL)
        {
            int linePos = getMenuTextLength(id, entryPos);
            char valueAsText[VALUE_LEN];
            snprintf(valueAsText, VALUE_LEN, "%.1f", CallbackFunctionGetFloat(menuEntries[id][entryPos].value));
            if (TEST)
                printf(" %s\n", valueAsText);
            else
                lcd_write(valueAsText, i, linePos + 3);
        }
        else
        {
            if (TEST)
                printf("\n");
        }
        entryPos++;
    }
    return 0;
}

void UpdateActualMenu()
{
    Menu(MenuActive);
}

int getMenuTextLength(int menuId, int menuItem)
{
    int i = 0;
    while (menuEntries[menuId][menuItem].menuText[i] != '\0')
    {
        i++;
    }
    return i;
}

void increase_marker_position()
{
    if (MarkerPosition < MenuItems - 1)
    {
        MarkerPosition++;
        if (MarkerPosition > StartPosition + LINES - 2)
        {
            StartPosition++;
        }
        Menu(MenuActive);
    }
}

void decrease_marker_position()
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

op_int_t GetMenuItemFunction()
{
    return *menuEntries[MenuActive][MarkerPosition].opt;
}

op_float_t GetMenuItemValue()
{
    return *menuEntries[MenuActive][MarkerPosition].value;
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

int CallbackFunctionFromMenuItem(int param, op_int_t op)
{
    return op(param);
}

float CallbackFunctionGetFloat(op_float_t op)
{
    return op();
}

int NoOp(int n)
{
    return n;
}