/**
  ******************************************************************************
  * @file           : menu.h
  * @brief          : A menu for a 4x20LCD display
  ******************************************************************************
  * @author Ayleen Weiss, 2021-10-21
  * 
  *
  ******************************************************************************
  */

#ifndef _MENU_H_
#define _MENU_H_

typedef int (*op_int_t)(int);
typedef float (*op_float_t)();

int Menu(int param);
void UpdateActualMenu();
int NoOp(int);
void increase_marker_position();
void decrease_marker_position();
int GetMarkerPosition();
op_int_t GetMenuItemFunction();
int GetMenuTarget();
void SetStartPosition(int position);
int GetStartPosition();
void SetMenuId(int id);
int getMenuTextLength(int menuId, int menuItem);

int CallbackFunctionFromMenuItem(int param, op_int_t op);
float CallbackFunctionGetFloat(op_float_t op);

typedef struct
{
  char *menuText;
  op_int_t opt;
  int target;
  op_float_t value;
} menuEntry;

static int MenuItems;
static int StartPosition;
static int MarkerPosition;
static int MenuActive = -1;

#endif // end _MENU_H_
