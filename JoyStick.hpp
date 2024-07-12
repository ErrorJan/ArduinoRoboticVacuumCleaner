//why is dis still here?
#ifndef JoyStick_HPP
#define JoyStick_HPP

#include "Vec2.hpp"
#include "SetupPins.hpp"

enum class jstix_dir
{
    UP,
    RIGHT,
    LEFT,
    NOTHING
};

jstix_dir GetJoystickDirection() 
{
    Vec2 inputAxis;

    inputAxis.x = round(  ( analogRead( PIN_JSTICK_X_AXIS ) - 512 )       / 512.0 );
    inputAxis.y = round( (( analogRead( PIN_JSTICK_Y_AXIS ) - 512 ) * -1) / 512.0 );

    if ( inputAxis.y == 1 )
        return jstix_dir::UP;

    if ( inputAxis.x == 1 )
        return jstix_dir::RIGHT;
    else if ( inputAxis.x == -1 )
        return jstix_dir::LEFT;

    return jstix_dir::NOTHING;
}


#endif
//yes.