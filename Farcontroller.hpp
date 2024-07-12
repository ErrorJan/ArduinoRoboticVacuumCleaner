#ifndef Farcontroller_hpp
#define Farcontroller_hpp
#include "Lib/IrRemote/IRremote.h" //include the library
#include "RoombaHardware.hpp"
#define Dance 0xFFA25D //defines the adress as Dance
#define mForward 0xFF629D
#define tRight 0xFFC23D
#define mBack 0xFFA857
#define tLeft 0xFF22DD
uint32_t Previous; 
int receiver = 13; //initialize pin 13 as recevier pin.
IRrecv irrecv(receiver); //create a new instance of receiver
decode_results results;


void setupFcontroll() { 
 
 irrecv.enableIRIn(); //start the receiver
}
void ControllerCheck() {
    char cDirectx10;
 if (irrecv.decode(&results)) { //if we have received an IR signal
  if (results.value==0xFFFFFFFF) { 
      results.value=Previous;
      }

    switch(results.value) {
           case Dance : Serial.print("Dance Dance revolutioN? "); break;
           case mForward : Serial.print("vorwärtz "); hardware.MoveForward(); break;
           case mBack : Serial.print("rückwärtz ");  hardware.MoveBackward(); break;
           case tRight : Serial.print("Dreh Rechts "); hardware.TurnRight(); break;
           case tLeft : Serial.print("Dreh Links "); hardware.TurnLeft(); break;
           
      } 
  // Serial.println (results.value, HEX); //display HEX results 
 
 irrecv.resume(); //next value
 }
 }

#endif