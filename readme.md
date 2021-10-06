# A simple menu system with callback functions

## Uses an LCD display and a rotary encoder, implemented in C for use with a MCU

This implements a menu to be shown on a LCD display (4 lines by 20 characters), connected to a microcontroller (STM32, Arduino, you name it) and controlled by a rotary encoder (alternatively it could be used with 3 buttons: up, down and select).

Assuming that the menu structure is known and fixed (no new menu entries are created during runtime), and one does not want to put the list nodes on the heap, this code does not use a linked list with dynamic memory allocation, but uses arrays and structs to hold the menu titles and entries. The entries ar assiociated with a callback funtion that can point to a submenu or call any other function that shall be executed when selecting the entry that is active (= has the ">" marker placed at the beginning of the line).

Uses char\* instead of string, because the latter is not available on some controllers.

_Note:_ Depending on the LCD driver / library you use, overflow of menutexts too long for the 20 char LCD display may not be handled graciously. This code does not contain any checks on the length of the entered texts.
