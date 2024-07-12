#include "SetupPins.hpp"
#include <Arduino.h>

void SetupPins()
{
    pinMode( PIN_ULSound_FrontSide_Trigger, OUTPUT );
    pinMode( PIN_ULSound_FrontSide_Echo, INPUT );

    pinMode( PIN_ULSound_RightSide_Trigger, OUTPUT );
    pinMode( PIN_ULSound_RightSide_Echo, INPUT );

    pinMode( PIN_ULSound_LeftSide_Trigger, OUTPUT );
    pinMode( PIN_ULSound_LeftSide_Echo, INPUT );

    pinMode( PIN_ULSound_DownSide_Trigger, OUTPUT );
    pinMode( PIN_ULSound_DownSide_Echo, INPUT );

    pinMode( PIN_DEBUG_BUTTON, INPUT );
}
