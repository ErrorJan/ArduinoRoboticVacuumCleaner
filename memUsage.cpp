#include "memUsage.hpp"
#include <Arduino.h>

void PrintMemUsage()
{
    PrintMemUsage("Global: ");
}

void PrintMemUsage( const String& str )
{
    Serial.print( str );
    Serial.print( freeMemory() );
    Serial.println( " - Free SRAM" );  
}

int freeMemory() 
{
    #ifndef ESP32
    
    char top;
    return &top - __brkval;
    
    #else

    return ESP.getFreeHeap();

    #endif
}
