#include "RoombaAI.hpp"

#include "Vec2.hpp"
#include "RoombaProperties.hpp"
#include <Arduino.h>
#include "SetupPins.hpp"
#include "memUsage.hpp"

namespace RoombaAI
{
// -------------------- ---------------- -------------------- //
// ------------------- <RoombaAI::Roomba> ------------------- //
// -------------------- ---------------- -------------------- //
    // ----------------
    // Public Methods:
    // ----------------
    Roomba::Roomba( RoombaHardware hardware )
    {
        this->hardware = hardware;
        // gridPtr = new RoombaGrid();
    }

    void Roomba::UpdatePosition( float deltaDistance )
    {
        // Convert the direction into a usable vector.
        Vec2 lookVec = Direction2Vector( this->lookingDirection );

        // Update the internal position of the Roomba.
        this->roombaPosition = this->roombaPosition + lookVec * deltaDistance;
        this->gridRoombaPosition = RealPos2GridPos( this->roombaPosition, this->gridSize );

        this->deltaDistance = deltaDistance;

        grid.UpdateGrid( this );

        if ( lastAccessedChunk == nullptr )
        {
            grid.GetChunkAt( this->gridRoombaPosition, this->lastAccessedChunk );
        }

        Vec2 deltaMove = lookVec * deltaDistance;
        this->currentLazyChunkPos += abs( deltaMove.x + deltaMove.y );
        UpdateChunkWallInfo();
        if ( this->lookingDirection != RoombaDirection::NODIRECTION )
            MoveRoomba();
    }

    void Roomba::SetGridSize( float gridSize ) 
        { this->gridSize = gridSize; }

    float Roomba::GetGridSize() 
        { return this->gridSize; }

    int Roomba::GetAmountOfChunks() 
        { return grid.GetAmountOfChunks(); }

    Vec2 Roomba::GetPosition() 
        { return this->roombaPosition; }

    RoombaDirection Roomba::GetLookingDirection() 
        { return this->lookingDirection; }

    void Roomba::SetLookingDirection( RoombaDirection rd ) 
        { this->lookingDirection = rd; }

    RoombaChunk* Roomba::GetAnyChunkAt( const short& i ) 
        { return grid.GetAnyChunkAt( i ); }

    // ----------------
    // Private Methods:
    // ----------------
    void Roomba::UpdateChunkWallInfo()
    {
        RoombaChunk* currentChunk = nullptr;
        grid.GetChunkAt( this->gridRoombaPosition, currentChunk );

        bool nextChunkExists = grid.GetChunkAt( this->gridRoombaPosition + Direction2Vector( lookingDirection ) );

        if ( lastAccessedChunk != currentChunk )
        {
            this->currentLazyChunkPos = 0;
            lastAccessedChunk = currentChunk;
        }

        if ( hardware.DetectFront() || hardware.DetectLeft() || hardware.DetectRight() )
        {
            currentChunk->isObstacle = true;
        }
    }

    void Roomba::SetWallOnChunk( RoombaChunk& rc, const bool& set, RoombaDirection& rd )
    {
        rc.isObstacle = set;
    }

    void Roomba::MoveRoomba()
    {
        RoombaChunk* currentChunk = nullptr;
        grid.GetChunkAt( this->gridRoombaPosition, currentChunk );

        Vec2 nextPos = this->gridRoombaPosition + Direction2Vector( lookingDirection );
        Vec2 nextRPos = this->gridRoombaPosition + Direction2Vector( RightSideDirection( lookingDirection ) );
        Vec2 nextLPos = this->gridRoombaPosition + Direction2Vector( LeftSideDirection( lookingDirection ) );

        if ( grid.GetChunkAt( nextPos ) )
        {
            if ( !grid.GetChunkAt( nextRPos ) && !hardware.DetectRight() )
                hardware.TurnRight();

            else if ( !grid.GetChunkAt( nextLPos ) && !hardware.DetectLeft() )
                hardware.TurnLeft();

            else if ( this->currentLazyChunkPos > this->gridSize / 2 )
                ScanForUnfoundChunks();
        }

        SimpleMove();
    }

    void Roomba::SimpleMove()
    {
        if ( !hardware.DetectFront() )
        {
            hardware.MoveForward();
        }
        else
        {
            hardware.TurnRight();
        }
    }

    void Roomba::ScanForUnfoundChunks()
    {
        Serial.println( F("Scanning for new Chunks") );
    }
// -------------------- ---------------- -------------------- //
// ------------------- </RoombaAI::Roomba> ------------------ //
// -------------------- ---------------- -------------------- //



// ------------------ -------------------- ------------------ //
// ----------------- <RoombaAI::RoombaGrid> ----------------- //
// ------------------ -------------------- ------------------ //
    // ----------------
    // Public Methods:
    // ----------------
    void RoombaGrid::UpdateGrid( Roomba* roomba )
    {
        Vec2 gridPos = RealPos2GridPos( roomba->GetPosition(), roomba->GetGridSize() );

        // Get the position in a whole number (rounded), to store as the coordinates for each chunk.
        /*
        o = Origin Roomba position
        deltaDistance example: 0.5 every time this would be called.
        gridSize example: 1.0

        --------
        |     _  |
        |   _|_| | <- 1,2 (internalPos: 0.5/1.0, 1.5 / 2.0)
        |  |_|   | <- 0,1 (internalPos: 0, 0.5 / 1.0)
        |  |o|   | <- 0,0 (internalPos: 0,0)
        |   -    |
        |        |
        --------
        */

        // Store a new Chunk if necessary
        if ( AddIfNotExists( (int)gridPos.x, (int)gridPos.y, newestChunk ) )
        {
            Serial.println( F("Generated new chunk!") );
        }
    }

    unsigned int RoombaGrid::GetAmountOfChunks() 
        { return grid.size(); }

    RoombaChunk* RoombaGrid::GetAnyChunkAt( const unsigned short& index ) 
    {
        RoombaChunk* rg = nullptr;

        rg = &grid[index];

        return rg;
    }

    bool RoombaGrid::GetChunkAt( const short& posX, const short& posY, RoombaChunk* foundRoombaChunk )
    {
        for ( int i = 0; i < grid.size(); i++ )
        {
            RoombaChunk* rc = &grid[i];

            if ( rc->posX == posX && rc->posY == posY )
            {
                foundRoombaChunk = rc;
                return true;
            }
        }

        return false;
    }

    bool RoombaGrid::GetChunkAt( Vec2 gridPos )
    {
        RoombaChunk* rc = nullptr;

        return GetChunkAt( (short)gridPos.x, (short)gridPos.y, rc );
    }

    bool RoombaGrid::GetChunkAt( Vec2 gridPos, RoombaChunk* rc ) 
        { return GetChunkAt( (short)gridPos.x, (short)gridPos.y, rc ); }

    bool RoombaGrid::GetChunkAt( Vec2 pos, float gridSize, RoombaChunk& foundRoombaChunk )
    {
        Vec2 roundedPos = RealPos2GridPos( pos, gridSize );

        return GetChunkAt( (short)roundedPos.x, (short)roundedPos.y, &foundRoombaChunk );
    }

    RoombaChunk* RoombaGrid::GetNewestChunk()
        { return this->newestChunk; }

    // ----------------
    // Private Methods:
    // ----------------
    bool RoombaGrid::AddIfNotExists( const short& posX, const short& posY )
    {
        RoombaChunk* newRC = nullptr;

        return AddIfNotExists( posX, posY, newRC );
    }

    bool RoombaGrid::AddIfNotExists( const short& posX, const short& posY, RoombaChunk* newRC )
    {
        // Look through the list if this chunk already exists.
        // If it does, just return.
        for ( int i = 0; i < this->grid.size(); i++ )
        {
            RoombaChunk* rc = &grid[i];

            if ( rc->posX == posX && rc->posY == posY )
            {
                return false;
            }
        }

        // If it doesn't exist create it and store it.
        // Add this RoombaChunk at the end of the grid list
        grid.push_back( RoombaChunk( posX, posY ) );

        newRC = &grid[ grid.size() - 1 ];
        return true;
    }
// -------------------- ---------------- -------------------- //
// ---------------- </RoombaAI::RoombaGrid> ----------------- //
// -------------------- ---------------- -------------------- //



// ------------------ -------------------- ------------------ //
// ---------------- <RoombaAI::RoombaChunk> ----------------- //
// ------------------ -------------------- ------------------ //
    // ----------------
    // Public Methods:
    // ----------------
    RoombaChunk::RoombaChunk( const short& posX, const short& posY )
    {
        this->posX = posX;
        this->posY = posY;
    }
// -------------------- ---------------- -------------------- //
// ---------------- </RoombaAI::RoombaChunk> ---------------- //
// -------------------- ---------------- -------------------- //
}
