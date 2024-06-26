#include "LedControl.h" // Library for communication with 7-segment display

// Number of MAX7219 chips
const int numChips = 3;

// Initialize the LedControl object (DIN, CLK, LOAD, number of MAX7219 chips)
LedControl lc = LedControl(12, 11, 10, numChips);

// Variables to hold current scores
int scorePlayerOne = 0;
int scorePlayerTwo = 0;

// Switches pin connection to Arduino UNO
const int switchPlayerOne = 4;
const int switchPlayerTwo = 3;

// FUTURE USE:
const int switch_teamOne_name = 2;
const int switch_teamOne_score = 3;
const int switch_teamTwo_name = 4;
const int switch_teamTwo_score = 5;
const int switch_inning = 6;
const int switch_balls = 7;
const int switch_strikes = 8;
const int switch_outs = 9;

// Function to initialize the 7-segment display
void initializeDisplay()
{
  for (int chip = 0; chip < numChips; chip++)
  {
    lc.shutdown(chip, false); // Wake up MAX7219
    lc.setIntensity(chip, 7); // Set brightness to medium
    lc.clearDisplay(chip);    // Clear all displays connected to MAX7219 chip
    // Initialize all displays to show zeros
    for (int digit = 0; digit < 8; digit++)
    {
      Serial.print("initialize digit ");
      Serial.print(chip);
      Serial.print(digit);
      lc.setDigit(chip, digit, 8, false);
    }
  }
}

// Function to update the display for a given player
void updateDisplay(int chip, int player, int score)
{
  // TODO: Once we validate that this works with one chip, we'll update this
  // with multiple switches and more score displays
  int rightDigit = score % 10;
  int leftDigit = (score % 100) / 10;
  int digitOffset = (player == 1) ? 0 : 2;
  lc.setDigit(chip, digitOffset, leftDigit, false);
  lc.setDigit(chip, digitOffset + 1, rightDigit, false);
}

// Function to handle button press for a given player
void handleButtonPress(int chip, int switchPin, int &score)
{
  if (!digitalRead(switchPin))
  {
    score++; // Increase score by 1
    if (score > 9) {
      score = 0;
    }
    
    Serial.print("Switch on pin ");
    Serial.print(switchPin);
    Serial.print(" pressed. New score: ");
    Serial.println(score);

    
    lc.setDigit(chip, 0, score, false);
    // Wait until switch is released to continue
    while (!digitalRead(switchPin))
    {
    }
    delay(500); // Small delay to debounce the switch
  }
}

void setup()
{
  Serial.begin(9600); // Initialize Serial communication at 9600 baud rate
  pinMode(switchPlayerOne, INPUT_PULLUP);
  //pinMode(switchPlayerTwo, INPUT_PULLUP);
  //initializeDisplay();
  //lc.setDigit(0, 0, 8, false);
  lc.shutdown(0, false);  // Wake up displays
  lc.setIntensity(0, 8);  // Set intensity levels
  lc.clearDisplay(0);    
  lc.setDigit(0, 0, 0, false); 
}

void loop()
{
  handleButtonPress(0, switchPlayerOne, scorePlayerOne);

  //lc.setDigit(0, 0, 3, true);
  //handleButtonPress(0, switchPlayerTwo, scorePlayerTwo, 2);
}