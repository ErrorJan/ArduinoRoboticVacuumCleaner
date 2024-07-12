//----------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------

#include "RoombaProperties.hpp"
#include "RoombaAI.hpp"
#include "JoyStick.hpp"
#include "UltraSchall.hpp"
#include "SetupPins.hpp"
#include "memUsage.hpp"
#include "DebugPrinting.hpp"


// Create a roomba object
// Please try to not use this outside of main, 
// since that may introduce bugs if everyone accesses main roomba.
RoombaHardware hardware;
RoombaAI::Roomba roomba( hardware );
#include "Farcontroller.hpp"

// -------------------------------
// Setup Function:
// -------------------------------
void setup()
{
    Serial.begin( 19200 );
    randomSeed(analogRead(0));
    SetupPins();
    setupFcontroll();
    // Set the grid size.
    roomba.SetGridSize( 1.00 );

    // Set the default direction of the Roomba
    roomba.SetLookingDirection( RoombaDirection::NODIRECTION );

    // Create the first chunk.
    roomba.UpdatePosition( 0 );

    hardware.InitHardware();
}

// -------------------------------
// Loop Function:
// -------------------------------
void loop()
{
    Debug::PauseForInput();

    Serial.println( F( "\nContinuing..." ) );
    PrintMemUsage();
    
    roomba.SetLookingDirection( hardware.GetCurrentLookDirection() );
    // Update the position of the Roomba.
    if ( hardware.TurningDone() )
        roomba.UpdatePosition( hardware.GetDeltaMovement() );

    // Debug::PrintAllChunks( roomba );
    // Debug::PrintRoombaPos( roomba );
}