#include <stdio.h>
#include "menu.h"

const char *menuTitle[] = {"Hauptmenue", "Submenue 1", "Submenue 1"};
const int numberOfItems[] = {5, 4, 3};

menuEntry menuEntries[10][10] = {{{"Hmenue 1", menu}, {"Hmenue 2", menu}, {"Hmenue 3", menu}, {"Hmenue 4", menu}, {"Hmenue 5", menu}},
                                 {{"Smenue 1_1", func1}, {"Smenue 1_2", func2}, {"Smenue 1_3", menu}, {"Smenue 1_4", menu}},
                                 {{"Smenue 2_1", menu}, {"Smenue 2_2", menu}, {"Smenue 2_3", menu}}};

int func1(int param)
{
    printf("Funktion: Entladen 1");
    return 0;
}

int func2(int param)
{
    printf("Funktion: Entladen 2");
    return 0;
}

int cb_func(int param, op_t op)
{
    return op(param);
}

int menu(int param)
{
    printf("%s\n", menuTitle[param]);

    for (int i = 0; i < numberOfItems[param]; i++)
    {
        printf("%s\n", menuEntries[param][i].menuText);
    }

    return 0;
}