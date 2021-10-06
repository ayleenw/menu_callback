/**
  ******************************************************************************
  * @file           : menu.hpp
  * @brief          : A menu for a 4x20LCD display
  ******************************************************************************
  * @author Ayleen Weiss, 2021-10-06
  * 
  *
  ******************************************************************************
  */

#ifndef _MENU_H_
#define _MENU_H_

typedef int (*op_t)(int);

void CreateMenu(int menuId);
int Menu(int param);
void SetMarkerPosition(int position);
void IncreaseMarkerPosition();
void DecreaseMarkerPosition();
int GetMarkerPosition();
op_t GetCallback();
void SetStartPosition(int position);
int GetStartPosition();
void SetMenuId(int id);

int cb_func(int param, op_t op);

typedef struct
{
    char *menuText;
    op_t opt;

} menuEntry;

static int MenuItems;
static int StartPosition;
static int MarkerPosition;
static int MenuActive = -1;

#endif // end _MENU_H_
