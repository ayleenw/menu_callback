#include <stdio.h>
#include "menu.h"
#include "func.h"
#include "lcd_dummy.h" // remove when using with MCU

#define LINES 4
#define TEST 1 // 1 for print to cmd, 0 for write to LCD

const char *menuTitle[] = {"Hauptmenue", "Submenue 1", "Submenue 1"};
const int numberOfItems[] = {5, 4, 3};

menuEntry menuEntries[10][10] = {{{"Hmenue 1", Menu}, {"Hmenue 2", Menu}, {"Hmenue 3", Menu}, {"Hmenue 4", Menu}, {"Hmenue 5", Menu}},
                                 {{"Smenue 1_1", func1}, {"Smenue 1_2", func2}, {"Smenue 1_3", Menu}, {"Smenue 1_4", Menu}},
                                 {{"Smenue 2_1", Menu}, {"Smenue 2_2", Menu}, {"Smenue 2_3", Menu}}};

void CreateMenu(int menuId)
{
    MenuItems = numberOfItems[menuId];
    StartPosition = 0;
    MarkerPosition = 0;
    Menu(menuId);
}

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