#ifndef RoombaHardware_HPP
#define RoombaHardware_HPP

// -----------------------------------
// Logic for moving the roomba
// -----------------------------------

#include "RoombaProperties.hpp"
#include "Stepper.h"

class RoombaHardware
{
    public:
        void InitHardware();

        /**
         * @brief Move the roomba forward
         */
        void MoveForward();

        /**
         * @brief Detect if there is a wall/ obstacle infront of the roomba.
         * 
         * @return True: A wall/ obstacle is present. False: A wall/ obstacle is not present. 
         */
        bool DetectFront();

        /**
         * @brief Detect if there is a wall/ obstacle left of the roomba.
         * 
         * @return True: A wall/ obstacle is present. False: A wall/ obstacle is not present. 
         */
        bool DetectLeft();
        
        /**
         * @brief Detect if there is a wall/ obstacle right of the roomba.
         * 
         * @return True: A wall/ obstacle is present. False: A wall/ obstacle is not present. 
         */
        bool DetectRight();

        /**
         * @brief Turn the roomba right 90°
         * 
         */
        void TurnRight();

        /**
         * @brief Turn the roomba left 90°
         * 
         */
        void TurnLeft();

          /**
         * @brief Move the roomba backward
         */
        void MoveBackward();

        
        void DanceLR();
        void RoombaSpin();
        void DanceFB();
        void DanceDanceRevolution();

        RoombaDirection GetCurrentLookDirection();

        RoombaDirection GetCurrentExpectedDirection();
        bool TurningDone();
        float GetDeltaMovement();

    private:
        RoombaDirection expectedDirection;
        float movementDelta;
        static const int step_360 = 200;// 360 number of steps per/rev
        //Count of spins in DanceDanceRevolution
        int HowManyMoves = 3;
        // initialize the stepper library on pins 2-5 n 8-11
        Stepper myStepper1 = Stepper(step_360,2,3,4,5);
        Stepper myStepper2 = Stepper(step_360,8,9,10,11);
};

#endif