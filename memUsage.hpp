#ifndef memUsage_HPP
#define memUsage_HPP
#include <Arduino.h>

#ifndef ESP32
extern char *__brkval;
#endif

void PrintMemUsage( const String& str );
void PrintMemUsage();
int freeMemory();

#endif