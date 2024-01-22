#ifndef CARS_H
#define CARS_H

//Libraries
#include <Arduino.h>
#include <PCF8574.h>

class Cars{
  private:

    //Declare a reference to a PCF8574 object for controlling the I/O expander
    PCF8574& pcf8574;
    
    //Variables that corresponds to direction pins
    uint8_t motorDirectionPin_RightIN1;
    uint8_t motorDirectionPin_RightIN2;
    uint8_t motorDirectionPin_LeftIN3;
    uint8_t motorDirectionPin_LeftIN4;

    //Variables that corresponds to speed pins
    uint8_t motorSpeedPin_Right;
    uint8_t motorSpeedPin_Left;

    //Default variables for speeds
    const uint8_t minSpeed = 10;
    const uint8_t maxSpeed = 255;
    const uint8_t stopSpeed = 0;

    //Current speed variable can be change by setSpeed(uint_8 speed) and get by getSpeed().
    uint8_t currentSpeed;

    const char* states[9] = {
    "Parking",
    "Forward",
    "Forward Right",
    "Forward Left",
    "Backward",
    "Backward Right",
    "Backward Left",
    "Rotating Right",
    "Rotating Left"
    };
    

    //Initialitazion of the cars object.
    //Set the pins as outputs.
    //stop any movement and set the current speed as the max speed value.
    void init();

    public:
    char* currentState;
    //Cars constructor takes pcf8574, IN 1-4 (Direction pins), and EN A & B(Speed pins) as arguments.
    Cars(PCF8574& pcf8574,uint8_t motorDirectionPin_RightIN1,uint8_t motorDirectionPin_RightIN2, uint8_t motorDirectionPin_LeftIN3, uint8_t motorDirectionPin_LeftIN4, uint8_t motorSpeedPin_Right, uint8_t motorSpeedPin_Left);

    //Set the current speed of the car as the parameter
    void setSpeed(uint8_t speed);

    //Return the current speed value of the car as a constant
    uint8_t getSpeed() const;

    //Move the motor based on parameters inputs
    void moveMotor(uint8_t motorRight_State, uint8_t motorLeft_State, uint8_t motorRight_Speed, uint8_t motorLeft_Speed);
    
    //Move forward by putting the value of motor right & left state as HIGHs and set the motor speed as the current speed.
    void moveForward();

    //Move backward by putting the value of motor right & left state as LOWs and set the motor speed as the current speed.
    void moveBackward();

    //Rotate to either right or left by settomg the motor state opposite to each other.
    void rotateRight();
    void rotateLeft();

    //Turn the car by multiplying one of the motors by a scalar either by slowing or speeding them.
    //Default: 0.5.
    void turnRight(float turnAmount);
    void turnRight();
    void turnLeft(float turnAmount);
    void turnLeft();

    void backRight(float turnAmount);
    void backLeft(float turnAmount);
    void backRight();
    void backLeft();
    
    //Stop the movement of the motor by setting the motor speed to 0.
    void stopMovement();
    // void testMovement();
};

#endif


