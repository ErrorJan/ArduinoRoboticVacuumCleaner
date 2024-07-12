#include "RoombaHardware.hpp"

#include "UltraSchall.hpp"



//Count of spins in DanceDanceRevolution
int HowManyMoves = 3;

// Run on setup
void RoombaHardware::InitHardware()
{
    expectedDirection = GetCurrentLookDirection();
    myStepper1.setSpeed(60);//left
    myStepper2.setSpeed(60);//right
}

void RoombaHardware::MoveForward()
{
    myStepper1.setSpeed(60);
    myStepper2.setSpeed(60);
    for(int s=0; s<step_360; s++)
{
    myStepper1.step(1);
    myStepper2.step(1);
}
}

bool RoombaHardware::DetectFront()
{
    return ULSound::GetFrontSide();
}

bool RoombaHardware::DetectLeft()
{
    return ULSound::GetLeftSide();
}

bool RoombaHardware::DetectRight()
{
    return ULSound::GetRightSide();
}

void RoombaHardware::TurnRight()
{
    expectedDirection = RightSideDirection( expectedDirection );

        for(int s=0; s<step_360; s++)
{
    myStepper1.setSpeed(-60);
    myStepper1.step(1);
    myStepper2.setSpeed(60);
    myStepper2.step(1);
}
}

void RoombaHardware::TurnLeft()
{
    expectedDirection = LeftSideDirection( expectedDirection );
            for(int s=0; s<step_360; s++)
{
    myStepper1.setSpeed(60);
    myStepper1.step(1);
    myStepper2.setSpeed(-60);
    myStepper2.step(1);
}
    // try turning left
}
void RoombaHardware::MoveBackward()
{
    myStepper1.setSpeed(-60);
    myStepper2.setSpeed(-60);
    for(int s=0; s<step_360; s++)
{
    myStepper1.step(1);
    myStepper2.step(1);
}
}

void RoombaHardware::DanceDanceRevolution()
{
    for (int i = 0; i < HowManyMoves; i++)
    {
    int Rdm = random(1,4);
    switch (Rdm)
    {
    case 1:RoombaSpin(); break;
    case 2:DanceFB();    break;
    case 3:DanceLR();    break;
    
    default: break;
    }
    }
}

void RoombaHardware::RoombaSpin()
{
    for (int i = 0; i < HowManyMoves; i++)
    {
        TurnLeft();
    }
}

void RoombaHardware::DanceFB()
{
    for (int i = 0; i < HowManyMoves; i++)
    {
       MoveForward();
       MoveBackward();
    }
    
}
void RoombaHardware::DanceLR()
{
    TurnLeft();
    TurnRight();
}

void RoombaHardware::DanceDanceRevolution()
{
    for (int i = 0; i < HowManyMoves; i++)
    {
    int Rdm = random(1,4);
    switch (Rdm)
    {
    case 1:RoombaSpin(); break;
    case 2:DanceFB();    break;
    case 3:DanceLR();    break;
    
    default: break;
    }
    }
}

void RoombaHardware::RoombaSpin()
{
    for (int i = 0; i < HowManyMoves; i++)
    {
        TurnLeft();
    }
}

void RoombaHardware::DanceFB()
{
    for (int i = 0; i < HowManyMoves; i++)
    {
       MoveForward();
       MoveBackward();
    }
    
}
void RoombaHardware::DanceLR()
{
    TurnLeft();
    TurnRight();
}

RoombaDirection RoombaHardware::GetCurrentLookDirection()
{
    // Gyroscope magic
    // Default direction, if not global possible: RoombaDirection::NORTH

    return RoombaDirection::NODIRECTION; // <- Don't let this be NODIRECTION on startup. Bad things will happen.
}

RoombaDirection RoombaHardware::GetCurrentExpectedDirection()
    { return this->expectedDirection; }

bool RoombaHardware::TurningDone()
    { return expectedDirection == GetCurrentLookDirection(); }

float RoombaHardware::GetDeltaMovement()
    { return movementDelta; }
