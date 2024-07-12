#ifndef Vec2_HPP
#define Vec2_HPP

//----------------------------------------------------------------
// This is the Object of a 2 Dimensional Vector
//----------------------------------------------------------------

#include <Arduino.h>

class Vec2 : public Printable
{
    public:
        // X position in float.
        float x;
        // Y position in float.
        float y;

        /**
         * @brief Construct a new Vector 2D object
         * 
         * @param x The x direction
         * @param y The y direction
         */
        Vec2( float x, float y )
        {
            this->x = x;
            this->y = y;
        }

        Vec2(){}

        // Shorthand of writing Vec2( 0, 0 )
        static Vec2 Zero()
        {
            return Vec2( 0, 0 );
        }

        // Shorthand of writing Vec2( 1, 1 )
        static Vec2 One()
        {
            return Vec2( 1, 1 );
        }

        // The operator for Vec2 == Vec2 ?
        bool operator==( Vec2 v )
        {
            return v.x == this->x && v.y == this->y;
        }

        // Multiplying the Vector with a factor
        Vec2 operator*( float a )
        {
            Vec2 returnVec = Vec2::Zero();

            returnVec.x = this->x * a;
            returnVec.y = this->y * a;

            return returnVec;
        }

        // Adding 2 Vector 2D together
        Vec2 operator+( Vec2 a )
        {
            Vec2 returnVec = Vec2::Zero();

            returnVec.x = this->x + a.x;
            returnVec.y = this->y + a.y;

            return returnVec;
        }

        Vec2 operator-( Vec2 a )
        {
            Vec2 returnVec = Vec2::Zero();

            returnVec.x = this-> x - a.x;
            returnVec.y = this-> y - a.y;

            return returnVec;
        }

        // Allowing the possibility for Vec2 to be printed out.
        size_t printTo( Print& p ) const 
        {
            size_t r = 0;

            r += p.print( '(' );
            r += p.print( this->x );
            r += p.print( ", " );
            r += p.print( this->y );
            r += p.print( ')' );

            return r;
       }
};

#endif