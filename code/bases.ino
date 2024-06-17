#define LED_PIN_FIRST 2
#define LED_PIN_SECOND 3
#define LED_PIN_THIRD 4
#define BUTTON_PIN_FIRST 12
#define BUTTON_PIN_SECOND 10
#define BUTTON_PIN_THIRD 8

byte lastButtonStateFirst = LOW;
byte lastButtonStateSecond = LOW;
byte lastButtonStateThird = LOW;
byte ledStateFirst = LOW;
byte ledStateSecond = LOW;
byte ledStateThird = LOW;

void setup() {
  Serial.begin(9600); // Initialize Serial communication at 9600 baud rate
  pinMode(LED_PIN_FIRST, OUTPUT);
  pinMode(LED_PIN_SECOND, OUTPUT);
  pinMode(LED_PIN_THIRD, OUTPUT);
  pinMode(BUTTON_PIN_FIRST, INPUT);
  pinMode(BUTTON_PIN_SECOND, INPUT);
  pinMode(BUTTON_PIN_THIRD, INPUT);
}
void loop() {
for (int base = 1; base <= 3; base++) {

  int buttonPin;
  int ledPin;
  byte *lastButtonState;
  byte *ledState;

  if (base == 1) {
    buttonPin = BUTTON_PIN_FIRST;
    ledPin = LED_PIN_FIRST;
    lastButtonState = &lastButtonStateFirst;
    ledState = &ledStateFirst;
  } else if (base  == 2) {
    buttonPin = BUTTON_PIN_SECOND;
    ledPin = LED_PIN_SECOND;
    lastButtonState = &lastButtonStateSecond;
    ledState = &ledStateSecond;
  } else {
    buttonPin = BUTTON_PIN_THIRD;
    ledPin = LED_PIN_THIRD;
    lastButtonState = &lastButtonStateThird;
    ledState = &ledStateThird;
  }

  byte buttonState = digitalRead(buttonPin);
  if (buttonState != *lastButtonState) {
    Serial.print("Pressed\n");
    Serial.print(buttonPin);
    Serial.print("\n");
    Serial.print("State\n");
    Serial.print(*ledState);
    Serial.print("\n");
    *lastButtonState = buttonState;
    if (buttonState == LOW) {
      Serial.print("Released\n");
      Serial.print(buttonPin);
      Serial.print("\n");
      *ledState = (*ledState == HIGH) ? LOW: HIGH;
      digitalWrite(ledPin, *ledState);
      Serial.print("State\n");
      Serial.print(*ledState);
      Serial.print("\n");
    }
  }
}

}