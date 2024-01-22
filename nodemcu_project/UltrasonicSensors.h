#ifndef ULTRASONICSENSORS_H
#define ULTRASONICSENSORS_H

//Libraries
#include <Arduino.h>
#include <PCF8574.h>

class UltrasonicSensors{
  private:
    //Declare a reference to a PCF8574 object for controlling the I/O expander
    PCF8574& pcf8574;

    //Variables that corresponds to ultrasonic sensors pins
    uint8_t echoPin;
    uint8_t trigPin;

    //Default variables
    const uint16_t maxEchoDistance = 500;
    uint8_t minDistancetoSayItsVeryClose = 25;

    //Variables for statuses
    const char* status[5] = {
    "none",
    "far",
    "medium",
    "close",
    "very close"
    };
    char* currentStatus;

    //Initialitazion of the cars object.
    //Set trig as an output and echo as an input.
    void init();

    //Change the current status of the object based on 
    void changeCurrentStatusState(const int& distance, char*& currentStatus);

  public:  

  //UltrasonicSensors constructors takes pcf8574, echo pin, and trig pin as arguments.
  UltrasonicSensors(PCF8574& pcf8574, uint8_t echoPin, uint8_t trigPin);
  //UltrasonicSensors(uint8_t echoPin, uint8_t trigPin);

  //Return the current status as a const
  char* getCurrentStatus() const;

  //Get the distance from an object caught by the ultrasonic pulse.
  //Calculate the distance by converting speed of sound with the formula.
  //And change the current status.
  //If the distance is above maxEchoDistance it will return maxEchoDistance.
  long getDistanceFromMicro();

  // LEGACY
  // const char* getStatus(const int& distance);

};

#endif
