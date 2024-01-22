#define SHIFT_REGISTER_CLOCK 2
#define SHIFT_REGISTER_LATCH 3
#define SHIFT_REGISTER_DATA 4
#define PIEZO_BUZZER 5

// ShiftRegister class for controlling a shift register
class ShiftRegister {
private:
  uint8_t clockPin;
  uint8_t latchPin;
  uint8_t dataPin;

  // Private initialization method to set pin modes
  void init() {
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    writeShiftRegister(0, 0);
  };

public:
  // Constructor for the ShiftRegister class, initializes pins and calls init()
  ShiftRegister(uint8_t clockPin, uint8_t latchPin, uint8_t dataPin) {
    this->clockPin = clockPin;
    this->latchPin = latchPin;
    this->dataPin = dataPin;
    init();
  }

  // Public method to write data to the shift register
  void writeShiftRegister(uint8_t data, bool bitOrder) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, bitOrder, data);
    digitalWrite(latchPin, HIGH);
  }
};

// Declare an instance of ShiftRegister class
ShiftRegister shiftRegister1(SHIFT_REGISTER_CLOCK, SHIFT_REGISTER_LATCH, SHIFT_REGISTER_DATA);

// Define timing constants
const long sevenSegmentInterval = 1000;
const long buzzerInterval = 500;

// Variables for timing and tone control
unsigned long currentInterval = 0;
unsigned long previousMillis = 0;
unsigned long previousBuzzerMillis = 0;
long buzzerTone = 500;

// Define 7-segment display patterns
// Common anode 7-segment display
const uint8_t num[] = {0b10100000, 0b11111001, 0b11000100, 0b11010000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b100000000, 0b100010000};

// Variables for state and control
uint8_t flipFlag = 1;
uint8_t currentNumber = 0;
uint8_t buzzingCounter = 0;
bool isBuzzing = false;
bool buzzerToneFlag = false;

void setup() {
  // put your setup code here, to run once:
  currentInterval = sevenSegmentInterval;
  // Set the ShiftRegister data to binary 11111111(255) to turn off the 7-segment display
  shiftRegister1.writeShiftRegister(0b11111111, MSBFIRST);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();

  // Check if it's time to update the display
  if (currentMillis - previousMillis >= currentInterval) {
    // Check if buzzing is active
    if (isBuzzing) {
      // Increment buzzing counter and check if it reaches the limit
      if (++buzzingCounter == 6) {
        // Reset buzzing-related variables when limit is reached
        isBuzzing = false;
        currentInterval = sevenSegmentInterval;
        buzzingCounter = 0;
        flipFlag *= -1;
        noTone(PIEZO_BUZZER);
      }
    }

    // Update the 7-segment display if not in buzzing state
    if (!isBuzzing) {
      // Update the current number based on the flipFlag
      // flipFlag is postive if it's increasing and the opposite if it's decreasing
      currentNumber += flipFlag;
      // Update the 7-segment display with the new number
      shiftRegister1.writeShiftRegister(num[currentNumber], MSBFIRST);
    }

    // Update the timing variable
    previousMillis = currentMillis;

    // Check if the current number is 9 or 0
    if (currentNumber == 9 || currentNumber == 0) {
      // Activate buzzing state
      isBuzzing = true;
      // Switch the interval for the buzzer
      currentInterval = buzzerInterval;
      // Calculate the tone modifier for the buzzer
      int buzzerToneModifier = buzzingCounter * flipFlag * 90;

      // Alternate between tone per buzzerInterval and blink the 7-segment display
      if (buzzerToneFlag) {
        tone(PIEZO_BUZZER, buzzerTone - buzzerTone * cos(buzzerToneModifier));
        shiftRegister1.writeShiftRegister(0b11111111, MSBFIRST);
      } else {
        tone(PIEZO_BUZZER, buzzerTone + buzzerTone * sin(buzzerToneModifier));
        shiftRegister1.writeShiftRegister(num[currentNumber], MSBFIRST);
      }
      
      buzzerToneFlag = !buzzerToneFlag;
    }
  }
}
