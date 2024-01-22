#include <math.h>

#define PEDESTRIAN_BUTTON_PIN 2
#define PEDESTRIAN_LIGHT_G_PIN 5
#define PEDESTRIAN_LIGHT_R_PIN 6
#define TRAFFIC_LIGHT_G_PIN 9
#define TRAFFIC_LIGHT_Y_PIN 10
#define TRAFFIC_LIGHT_R_PIN 11

#define PEDESTRIAN_GREEN 0
#define PEDESTRIAN_RED 1

#define TRAFFIC_GREEN 0
#define TRAFFIC_YELLOW 1
#define TRAFFIC_RED 2

unsigned long lastFlickerTime = 0;
bool isFlickering = false;

bool pedestrianButtonPressed = 0;
unsigned long previousMillis = 0;
unsigned long lastPrintTime = 0;
const long printInterval = 50;
const long greenInterval = 15000;
const long yellowInterval = 5000;
const long redInterval = 8000;
const long redAdditionalInterval = 7000;
uint8_t* currentLightPtr = nullptr;

uint8_t trafficLights[] = { TRAFFIC_LIGHT_G_PIN, TRAFFIC_LIGHT_Y_PIN, TRAFFIC_LIGHT_R_PIN };
uint8_t pedestrianLights[] = { PEDESTRIAN_LIGHT_G_PIN, PEDESTRIAN_LIGHT_R_PIN };
// enum trafficLightState {GREEN, YELLOW, RED};

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(PEDESTRIAN_BUTTON_PIN, INPUT_PULLUP);
  for (int i = 0; i < 3; i++) {
    pinMode(trafficLights[i], OUTPUT);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(pedestrianLights[i], OUTPUT);
  }

  currentLightPtr = &trafficLights[TRAFFIC_GREEN];
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long elapsedMillis = currentMillis - previousMillis;
  if (!digitalRead(PEDESTRIAN_BUTTON_PIN) && pedestrianButtonPressed == 0) {
    if (*currentLightPtr == TRAFFIC_LIGHT_G_PIN) {
      previousMillis = currentMillis;
      elapsedMillis = 0;
      // Button pressed during green phase, transition to yellow immediately
      delay(50);
      currentLightPtr = &trafficLights[TRAFFIC_YELLOW];
      Serial.print("CHANGE YELLOW");
    }
    turnOffLights(trafficLights);
    pedestrianButtonPressed = 1;
  }
  char buffer[50];

  switch (*currentLightPtr) {
    case TRAFFIC_LIGHT_G_PIN:
      if (elapsedMillis >= greenInterval) {
        switchLights(trafficLights, TRAFFIC_YELLOW, currentMillis);
        Serial.print("CHANGE YELLOW ");
      } else if (elapsedMillis >= greenInterval - 3000) {
        // Gradually fade out the green light as it approaches the interval
        int fadeValue = map(elapsedMillis, greenInterval - 3000, greenInterval, 255, 0);
        if (currentMillis - lastFlickerTime >= 500) {
        // Toggle between full brightness and fadeValue
        if (isFlickering) {
          analogWrite(*currentLightPtr, fadeValue);
        } else {
          analogWrite(*currentLightPtr, 0);
        }
        isFlickering = !isFlickering;
        lastFlickerTime = currentMillis;
      }
      } else {
      analogWrite(*currentLightPtr, 255);
      }
      break;
    case TRAFFIC_LIGHT_Y_PIN:
      analogWrite(*currentLightPtr, 255);
      if (elapsedMillis >= yellowInterval) {
        switchLights(trafficLights, TRAFFIC_RED, currentMillis);
        Serial.print("CHANGE RED ");
      }
      break;
    case TRAFFIC_LIGHT_R_PIN:
      analogWrite(*currentLightPtr, 1);
      if (elapsedMillis >= redInterval + redAdditionalInterval * pedestrianButtonPressed) {
        switchLights(trafficLights, TRAFFIC_GREEN, currentMillis);
        Serial.print("CHANGE GREEN");
        pedestrianButtonPressed = 0;
      }
      break;
  }

  if (currentMillis - lastPrintTime >= printInterval) {
    char buffer[50];
    sprintf(buffer, "%d %lu %d %lu - %lu %d", *currentLightPtr, elapsedMillis, pedestrianButtonPressed, currentMillis / 1000, previousMillis / 1000);
    Serial.println(buffer);
    lastPrintTime = currentMillis;  // Update the last print time
  }
}

void switchLights(uint8_t* lights, int light, unsigned long& currentMillis) {
  turnOffLights(lights);
  currentLightPtr = &lights[light];
  previousMillis = currentMillis;
}

void turnOffLights(uint8_t* lights) {
  int numberOfLights = sizeof(lights) + 1;
  for (int i = 0; i < numberOfLights; i++) {
    digitalWrite(lights[i], LOW);
  }
}
