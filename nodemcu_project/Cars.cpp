#include "Cars.h"

    void Cars::init() {
      pcf8574.pinMode(motorDirectionPin_RightIN1, OUTPUT);
      pcf8574.pinMode(motorDirectionPin_RightIN2, OUTPUT);
      pcf8574.pinMode(motorDirectionPin_LeftIN3, OUTPUT);
      pcf8574.pinMode(motorDirectionPin_LeftIN4, OUTPUT);
      pinMode(motorSpeedPin_Right, OUTPUT);
      pinMode(motorSpeedPin_Left, OUTPUT);
      stopMovement();
      currentSpeed = maxSpeed;
    }

    Cars::Cars(PCF8574& pcf8574,uint8_t motorDirectionPin_RightIN1,uint8_t motorDirectionPin_RightIN2, uint8_t motorDirectionPin_LeftIN3, uint8_t motorDirectionPin_LeftIN4, uint8_t motorSpeedPin_Right, uint8_t motorSpeedPin_Left) : pcf8574(pcf8574){
      this->motorDirectionPin_RightIN1 = motorDirectionPin_RightIN1;
      this->motorDirectionPin_RightIN2 = motorDirectionPin_RightIN2;
      this->motorDirectionPin_LeftIN3 = motorDirectionPin_LeftIN3;
      this->motorDirectionPin_LeftIN4 = motorDirectionPin_LeftIN4;
      this->motorSpeedPin_Right = motorSpeedPin_Right;
      this->motorSpeedPin_Left = motorSpeedPin_Left;
      init();
    }

    void Cars::setSpeed(uint8_t speed){
      currentSpeed = speed;
    }

    uint8_t Cars::getSpeed() const {
      return currentSpeed;
    }

    void Cars::moveMotor(uint8_t motorRight_State, uint8_t motorLeft_State, uint8_t motorRight_Speed, uint8_t motorLeft_Speed){
      pcf8574.digitalWrite(motorDirectionPin_RightIN1, motorRight_State);
      pcf8574.digitalWrite(motorDirectionPin_RightIN2, !motorRight_State);
      pcf8574.digitalWrite(motorDirectionPin_LeftIN3, motorLeft_State);
      pcf8574.digitalWrite(motorDirectionPin_LeftIN4, !motorLeft_State);
      analogWrite(motorSpeedPin_Right, motorRight_Speed);
      analogWrite(motorSpeedPin_Left, motorLeft_Speed);
    }

    //By putting the Right and Left motors as HIGH it will move the car forward
    void Cars::moveForward(){
      moveMotor(HIGH, HIGH, currentSpeed, currentSpeed);
      currentState = const_cast<char*>(states[1]); //Forward
    }

    //By putting the Right and Left motors as LOW it will move the car backward
    void Cars::moveBackward(){
      moveMotor(LOW, LOW, currentSpeed, currentSpeed);
      currentState = const_cast<char*>(states[4]); //Backward
    }

    //By putting the Right and Left motors opposite to each other it will rotate the car to either right or left
    void Cars::rotateRight(){
      moveMotor(LOW, HIGH, currentSpeed, currentSpeed);
      currentState = const_cast<char*>(states[7]);
    }
    void Cars::rotateLeft(){
      moveMotor(HIGH, LOW, currentSpeed, currentSpeed);
      currentState = const_cast<char*>(states[8]);
    }

    //By slowing or speeding one of the right or left motor it will make the car turn either to right or left
    void Cars::turnRight(float turnAmount){
      moveMotor(HIGH, HIGH, currentSpeed * turnAmount, currentSpeed);
      currentState = const_cast<char*>(states[2]);
    }
    void Cars::turnLeft(float turnAmount){
      moveMotor(HIGH, HIGH, currentSpeed, currentSpeed * turnAmount);
      currentState = const_cast<char*>(states[3]);
    }

    //Turn the car by 0.5 value to either right or left if no parameter is set
    void Cars::turnRight(){
      turnRight(0.5);
    }
    void Cars::turnLeft(){
      turnLeft(0.5);
    }

    //By slowing or speeding one of the right or left motor it will make the car turn either to right or left
    void Cars::backRight(float turnAmount){
      moveMotor(LOW, LOW, currentSpeed * turnAmount, currentSpeed);
      currentState = const_cast<char*>(states[5]);
    }
    void Cars::backLeft(float turnAmount){
      moveMotor(LOW, LOW, currentSpeed, currentSpeed * turnAmount);
      currentState = const_cast<char*>(states[6]);
    }

      //Turn the car by 0.5 value to either right or left if no parameter is set
    void Cars::backRight(){
      backRight(0.5);
    }
    void Cars::backLeft(){
      backLeft(0.5);
    }

    //Stop the movement of the car by setting the motors as LOW LOW (HIGH HIGH also works)
    void Cars::stopMovement(){
      pcf8574.digitalWrite(motorDirectionPin_RightIN1, LOW);
      pcf8574.digitalWrite(motorDirectionPin_RightIN2, LOW);
      pcf8574.digitalWrite(motorDirectionPin_LeftIN3, LOW);
      pcf8574.digitalWrite(motorDirectionPin_LeftIN4, LOW);
    }

    // void Cars::testMovement(){
    //   moveForward();
    //   delay(2000);
    //   stopMovement();
    //   delay(2000);
    //   moveBackward();
    //   delay(2000);
    //   stopMovement();
    //   delay(2000);
    // }