#ifndef DebugPrinting_HPP
#define DebugPrinting_HPP

#include "RoombaAI.hpp"
#include "RoombaProperties.hpp"

namespace Debug
{
    using namespace RoombaAI;

    // Print out the chunks.
    void PrintAllChunks( Roomba& roomba )
    {
        for ( unsigned int i = 0; i < roomba.GetAmountOfChunks(); i++ )
        {
            RoombaAI::RoombaChunk* rc = roomba.GetAnyChunkAt( i );

            Serial.print( F("Chunk at: ") );
            Serial.print( rc->posX );
            Serial.print( F(", ") );
            Serial.println( rc->posY );
        }

        Serial.println( roomba.GetAmountOfChunks() );
    }

    // Position of the roomba
    void PrintRoombaPos( Roomba& roomba )
    {
        Serial.print( F("Roomba at: ") );
        Serial.println( roomba.GetPosition() );
    }

    // Pause execution for input in serial
    void PauseForInput()
    {
        while ( true )
        {
            String d = Serial.readString();

            if ( d != "" )
                break;

            delay( 100 );
        }
    }
}

#endif