#include <stdio.h>
#include "menu.h"
#include "func.h"

int main()
{
    Menu(0);
    IncreaseMarkerPosition();
    IncreaseMarkerPosition();
    IncreaseMarkerPosition();
    IncreaseMarkerPosition();
    DecreaseMarkerPosition();
    DecreaseMarkerPosition();
    DecreaseMarkerPosition();

    cb_func(GetMarkerPosition(), GetCallback());
    IncreaseMarkerPosition();
    cb_func(GetMarkerPosition(), GetCallback());

    // cb_func(0, func1);

    return 0;
}
