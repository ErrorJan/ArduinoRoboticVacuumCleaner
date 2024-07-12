#ifndef RoombaProperties_HPP
#define RoombaProperties_HPP

#include "Vec2.hpp"
#include <Arduino.h>

//----------------------------------------------------------------
// Helper file for functions for the roomba
//
// Example:
// Convert Direction into a Vector.
// Set a direction.
// Get the right side of the roomba.
//----------------------------------------------------------------

// Every direction the roomba is allowed to be facing.
enum class RoombaDirection : uint8_t
{
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NODIRECTION
};

/**
 * @brief Convert a Direction into a Vector
 * If the direction is invalid, it will return a vector of (0, 0)
 * 
 * @param dir The direction to be converted.
 * @return The Vector of the direction.
 */
Vec2 Direction2Vector( RoombaDirection dir );

/**
 * @brief Convert a Vector into a Direction
 * If the Vector is invalid, it will return a Direction of NODIRECTION
 * 
 * @param dir The direction to be converted.
 * @return The Direction of the Vector.
 */
RoombaDirection Vector2Direction( Vec2 dir );

/**
 * @brief The right side of the roomba based on the current direction.
 * 
 * @param currentDirection The current direction that the roomba is towards at.
 * @return The direction on the right side.
 */
RoombaDirection RightSideDirection( RoombaDirection currentDirection );

/**
 * @brief The left side of the roomba based on the current direction.
 * 
 * @param currentDirection The current direction that the roomba is towards at.
 * @return The direction on the left side.
 */
RoombaDirection LeftSideDirection( RoombaDirection currentDirection );

/**
 * @brief Print the direction to the console.
 * 
 * @param dir The direction to be printed.
 */
void PrintDirection( RoombaDirection dir );

/**
 * @brief Takes in a position and the grid size and returns a Vec2 of the position on the grid.
 * 
 * @param pos The Real world position
 * @param gridSize The size of each chunk/ the grid size
 * @return Vec2 The position on the grid.
 */
Vec2 RealPos2GridPos( Vec2 pos, float gridSize );

#endif