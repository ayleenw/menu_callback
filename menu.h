#ifndef _MENU_H_
#define _MENU_H_

typedef int (*op_t)(int);
int func1(int param);
int func2(int param);
int menu(int param);
int cb_func(int param, op_t op);

typedef struct
{
    char *menuText;
    op_t opt;

} menuEntry;

#endif // end _MENU_H_
