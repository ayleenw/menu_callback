#include <stdio.h>
#include "menu.h"
#include "func.h"
#include "i2clcd.h"

#define LINES 4     // Set lines acc. to used LCD
#define COLUMNS 20  // Set columns acc. to used LCD
#define VALUE_LEN 5 // max length for injected live values (-1)
#define TEST 1      // 1 to print to stdout, 0 to write to real LCD

const char *menuTitle[] = {"Hauptmenue", "Submenue 1", "Submenue 2"};
const int numberOfItems[] = {3, 4, 3};

menuEntry menuEntries[10][10] = {{{"Hmenue 1", Menu, 1}, {"Hmenue 2", Menu, 2}, {"Hmenue 3", Menu, 3}},
                                 {{"Smenue 1_1 LED on", func1, 0}, {"Smenue 1_3 LED off", func2, 1}, {"Spannung:", Menu, 2}, {"Zurueck", Menu, 0}},
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

int getMenuTextLength(int menuId, int menuItem)
{
    int i = 0;
    while (menuEntries[menuId][menuItem].menuText[i] != '\0')
    {
        i++;
    }
    return i;
}

void injectVariableValueFloat(int menuId, int menuItem, float value)
{
    if (TEST)
        printf("Menu text: %s\n", menuEntries[menuId][menuItem].menuText);
    char valueAsText[VALUE_LEN];
    snprintf(valueAsText, VALUE_LEN, "%.1f", value);

    int position = getMenuTextLength(menuId, menuItem);
    if (TEST)
        printf("Menu text length: %d\n", position);
    if (TEST)
        printf("Value: %s\n", valueAsText);
    else
        lcd_write(valueAsText, menuItem + StartPosition, position + 2);
}

// SetMarkerPosition function not thoroughly tested! Use  IncreaseMarkerPosition / DecreaseMarkerPosition if possibile or perform tests
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