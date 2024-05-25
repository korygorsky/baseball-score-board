#include "LedControl.h"  // Library for communication with 7-segment display

// Initialize the LedControl object (DIN, CLK, LOAD, number of MAX7219 chips)
LedControl lc = LedControl(12, 11, 10, 1);  

// Variables to hold current scores
int scorePlayerOne = 0;
int scorePlayerTwo = 0;

// Switches pin connection to Arduino UNO
const int switchPlayerOne = 2;
const int switchPlayerTwo = 3;

// Function to initialize the 7-segment display
void initializeDisplay() {
  lc.shutdown(0, false);  // Wake up MAX7219
  lc.setIntensity(0, 7);  // Set brightness to medium
  lc.clearDisplay(0);     // Clear all displays connected to MAX7219 chip
  // Initialize both displays to show zeros
  lc.setDigit(0, 0, 0, false);  
  lc.setDigit(0, 1, 0, false);
  lc.setDigit(0, 2, 0, false);
  lc.setDigit(0, 3, 0, false);
}

// Function to update the display for a given player
void updateDisplay(int player, int score) {
  int rightDigit = score % 10;
  int leftDigit = (score % 100) / 10;
  int digitOffset = (player == 1) ? 0 : 2;
  lc.setDigit(0, digitOffset, leftDigit, false);
  lc.setDigit(0, digitOffset + 1, rightDigit, false);
}

// Function to handle button press for a given player
void handleButtonPress(int switchPin, int &score, int player) {
  if (!digitalRead(switchPin)) {
    score++;  // Increase score by 1
    updateDisplay(player, score);
    // Wait until switch is released to continue
    while (!digitalRead(switchPin)) {}
    delay(5);  // Small delay to debounce the switch
  }
}

void setup() {
  pinMode(switchPlayerOne, INPUT_PULLUP);
  pinMode(switchPlayerTwo, INPUT_PULLUP);
  initializeDisplay();
}

void loop() {
  handleButtonPress(switchPlayerOne, scorePlayerOne, 1);
  handleButtonPress(switchPlayerTwo, scorePlayerTwo, 2);
}