 #include "UltrasonicSensors.h"

    void UltrasonicSensors::init(){
    if(&pcf8574 != NULL)
      pcf8574.pinMode(trigPin, OUTPUT);
    else
      pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  UltrasonicSensors::UltrasonicSensors(PCF8574& pcf8574, uint8_t echoPin, uint8_t trigPin) : pcf8574(pcf8574){
    this->echoPin = echoPin;
    this->trigPin = trigPin;
    init();
  }
  // UltrasonicSensors::UltrasonicSensors(uint8_t echoPin, uint8_t trigPin){
  //   this->echoPin = echoPin;
  //   this->trigPin = trigPin;
  //   init();
  // }

  char* UltrasonicSensors::getCurrentStatus() const {
    return currentStatus;
  }

  long UltrasonicSensors::getDistanceFromMicro() {
    if(&pcf8574 != NULL){
      pcf8574.digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      pcf8574.digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      pcf8574.digitalWrite(trigPin, LOW);
    }
    else{
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
    }
    
    long microsec = pulseIn(echoPin, HIGH) / 29 / 2;
    if(microsec < maxEchoDistance){
      changeCurrentStatusState(microsec, currentStatus);
      return microsec;
    }
    return maxEchoDistance;
  }

    void UltrasonicSensors::changeCurrentStatusState(const int& distance, char*& currentStatus) {
    if (distance == 0){
      currentStatus = const_cast<char*>(status[0]); // none
    } else if (distance < minDistancetoSayItsVeryClose) {
      currentStatus = const_cast<char*>(status[4]); // very close
    } else if (distance < minDistancetoSayItsVeryClose * 2) {
      currentStatus = const_cast<char*>(status[3]); // close
    } else if (distance < minDistancetoSayItsVeryClose * 4) {
      currentStatus = const_cast<char*>(status[2]); // medium
    } else if (distance < minDistancetoSayItsVeryClose * 6) {
      currentStatus = const_cast<char*>(status[1]); // very close
    } else {
      currentStatus = const_cast<char*>(status[0]); // none
    }
  }

