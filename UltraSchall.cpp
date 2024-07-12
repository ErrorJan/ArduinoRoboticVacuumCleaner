#include "SetupPins.hpp"
#include "UltraSchall.hpp"

#include <Arduino.h>

long ULSound::dauer = 0;
double ULSound::distance = 0;

bool ULSound::CheckRightSave = false;
bool ULSound::CheckLeftSave  = false;
bool ULSound::CheckFrontSave = false;
bool ULSound::CheckDownSave  = false;

//Check all Sides
bool ULSound::CheckSides()
{
    ULSound::CheckFrontSide();
    ULSound::CheckLeftSide();
    ULSound::CheckRightSide();
    ULSound::CheckDownSide();

    //Distance okay at all Sides?
    return CheckDownSave && CheckFrontSave && CheckLeftSave && CheckRightSave;
}

//Asulösen des Ultraschallsensors --> Messung Distanz
int ULSound::CheckDistance(int trigger, int echo)
{
    ULSound::dauer = 0;
    ULSound::distance = 0;

    //Ultrasound Pulse
    digitalWrite(trigger, LOW);
    delay(5);
    digitalWrite(trigger, HIGH);
    delay(10);
    digitalWrite(trigger, LOW);

    //Calculation Distance in CM
    ULSound::dauer = pulseIn(echo, HIGH);
    ULSound::distance = (dauer/2) * 0.03432;

    return distance;
}

void ULSound::CheckFrontSide()
{
    CheckFrontSave = false;

    //Check and config lowest distance thats allowed
    if (ULSound::CheckDistance(PIN_ULSound_FrontSide_Trigger, PIN_ULSound_FrontSide_Echo) > 2)
        CheckFrontSave = true;
}

void ULSound::CheckLeftSide()
{
    CheckLeftSave = false;

    //Check and config lowest distance thats allowed
    if (ULSound::CheckDistance(PIN_ULSound_LeftSide_Trigger, PIN_ULSound_LeftSide_Echo) > 3)
        CheckLeftSave = true;
}

void ULSound::CheckRightSide()
{
    CheckRightSave = false;

    //Check and config lowest distance thats allowed
    if (ULSound::CheckDistance(PIN_ULSound_RightSide_Trigger, PIN_ULSound_RightSide_Echo) > 3)
        CheckRightSave = true;
}

void ULSound::CheckDownSide()
{
    CheckDownSave = false;

    //Check and config lowest distance thats allowed
    if (ULSound::CheckDistance(PIN_ULSound_DownSide_Trigger, PIN_ULSound_DownSide_Echo) > 3)
        CheckDownSave = true;
}

bool ULSound::GetFrontSide() { return CheckFrontSave; }
bool ULSound::GetLeftSide() { return CheckLeftSave; }
bool ULSound::GetRightSide() { return CheckRightSave; }
bool ULSound::GetDownSide() { return CheckDownSave; }