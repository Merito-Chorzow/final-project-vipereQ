#include <Arduino.h>

// ===== PINY =====
#define LED_RED     23
#define LED_YELLOW  22
#define LED_GREEN   21
#define BUTTON_PIN  19

// ===== CZASY (ms) =====
#define TIME_GREEN   5000
#define TIME_YELLOW  2000
#define TIME_RED     5000
#define SAFE_BLINK   500
#define LONG_PRESS   3000
#define DEBOUNCE_MS  200

// ===== FSM =====
enum State { GREEN, YELLOW, RED, SAFE };
State state = GREEN;

// ===== CZAS =====
unsigned long stateStartTime = 0;
unsigned long pressStartTime = 0;
unsigned long lastBlinkTime = 0;
unsigned long lastButtonEvent = 0;

// ===== PRZYCISK =====
bool buttonPrev = HIGH;
bool longPressArmed = false;

// ===== INNE =====
bool safeLedOn = false;
unsigned long cycles = 0;

void goToNextState() {
  stateStartTime = millis();

  switch (state) {
    case GREEN:
      state = YELLOW;
      Serial.println("GREEN -> YELLOW");
      break;

    case YELLOW:
      state = RED;
      Serial.println("YELLOW -> RED");
      break;

    case RED:
      state = GREEN;
      cycles++;
      Serial.println("RED -> GREEN");
      break;

    default:
      break;
  }
}

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("START: Sygnalizacja swiatel");

  stateStartTime = millis();
}

void loop() {
  unsigned long now = millis();
  bool buttonNow = digitalRead(BUTTON_PIN);

  // ===== ZBOCZE: WCISNIĘCIE =====
  if (buttonPrev == HIGH && buttonNow == LOW) {
    pressStartTime = now;
    longPressArmed = true;
  }

  // ===== ZBOCZE: PUSZCZENIE (KRÓTKIE) =====
  if (buttonPrev == LOW && buttonNow == HIGH) {
    if (longPressArmed &&
        (now - pressStartTime < LONG_PRESS) &&
        (now - lastButtonEvent > DEBOUNCE_MS)) {

      Serial.println("Przycisk: szybkie przejscie");
      goToNextState();                 // NATYCHMIAST
      lastButtonEvent = now;
    }
    longPressArmed = false;
  }

  // ===== LONG PRESS → SAFE =====
  if (longPressArmed &&
      buttonNow == LOW &&
      (now - pressStartTime >= LONG_PRESS) &&
      state != SAFE) {

    state = SAFE;
    longPressArmed = false;
    safeLedOn = false;
    lastBlinkTime = now;

    Serial.println("!!! SAFE AKTYWOWANY !!!");
  }

  buttonPrev = buttonNow;

  // ===== FSM =====
  if (state != SAFE) {
    unsigned long duration = 0;

    switch (state) {
      case GREEN:  duration = TIME_GREEN;  break;
      case YELLOW: duration = TIME_YELLOW; break;
      case RED:    duration = TIME_RED;    break;
    }

    if (now - stateStartTime >= duration) {
      goToNextState();
    }

    digitalWrite(LED_GREEN, state == GREEN);
    digitalWrite(LED_YELLOW, state == YELLOW);
    digitalWrite(LED_RED, state == RED);
  }
  else {
    // ===== SAFE =====
    if (now - lastBlinkTime >= SAFE_BLINK) {
      safeLedOn = !safeLedOn;
      digitalWrite(LED_YELLOW, safeLedOn);
      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      lastBlinkTime = now;
    }
  }
}
