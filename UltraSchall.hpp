#ifndef UltraSchall_HPP
#define UltraSchall_HPP

#include "SetupPins.hpp"

class ULSound
{
    public:
        //Check All Sides
        static bool CheckSides();

        static bool GetFrontSide();
        static bool GetLeftSide();
        static bool GetRightSide();
        static bool GetDownSide();

    private:
        static long dauer;
        static double distance;

        static bool CheckRightSave;
        static bool CheckLeftSave;
        static bool CheckFrontSave;
        static bool CheckDownSave;

        static void CheckFrontSide();
        static void CheckLeftSide();
        static void CheckRightSide();
        static void CheckDownSide();
        static int  CheckDistance(int trigger, int echo);
};

#endif