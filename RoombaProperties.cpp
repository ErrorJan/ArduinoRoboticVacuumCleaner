#include "RoombaProperties.hpp"

#include "Vec2.hpp"
#include <Arduino.h>

Vec2 Direction2Vector( RoombaDirection dir )
{
    switch ( dir )
    {
        case RoombaDirection::NORTH:
            return Vec2( 0, 1 );
        case RoombaDirection::EAST:
            return Vec2( 1, 0 );
        case RoombaDirection::SOUTH:
            return Vec2( 0, -1 );
        case RoombaDirection::WEST:
            return Vec2( -1, 0 );
        default:
            return Vec2( 0, 0 );
    }
}

RoombaDirection Vector2Direction( Vec2 dir )
{
    if ( dir == Vec2( 0, 1 ) )
        return RoombaDirection::NORTH;
    else if ( dir == Vec2( 1, 0 ) )
        return RoombaDirection::EAST;
    else if ( dir == Vec2( 0, -1 ) )
        return RoombaDirection::SOUTH;
    else if ( dir == Vec2( -1, 0 ) )
        return RoombaDirection::WEST;
    else
        return RoombaDirection::NODIRECTION;
}

RoombaDirection RightSideDirection( RoombaDirection currentDirection )
{
    Vec2 currentDirectionVec = Direction2Vector( currentDirection );
    Vec2 rightSideVec = Vec2( currentDirectionVec.y, currentDirectionVec.x * -1 );
    return Vector2Direction( rightSideVec );
}

RoombaDirection LeftSideDirection( RoombaDirection currentDirection )
{
    Vec2 currentDirectionVec = Direction2Vector( currentDirection );
    Vec2 rightSideVec = Vec2( currentDirectionVec.y * -1, currentDirectionVec.x );
    return Vector2Direction( rightSideVec );
}

void PrintDirection( RoombaDirection dir )
{
    switch ( dir )
    {
        case RoombaDirection::NORTH:
            Serial.println( F("North") );
            break;
        case RoombaDirection::EAST:
            Serial.println( F("East") );
            break;
        case RoombaDirection::SOUTH:
            Serial.println( F("South") );
            break;
        case RoombaDirection::WEST:
            Serial.println( F("West") );
            break;
        default:
            Serial.println( F("Unknown Direction") );
    }
}

Vec2 RealPos2GridPos( Vec2 pos, float gridSize )
{
    Vec2 roundedPos;

    roundedPos.x = round( pos.x / gridSize );
    roundedPos.y = round( pos.y / gridSize );

    return roundedPos;
}
