#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


unsigned long systemTime;
int drawerCounter = 1;
float systemTemp;
bool fastRun = false;
unsigned long fastRunStartTime = 0;
const unsigned long fastRunDuration = 5 * 60 * 1000; // 5 minutes in milliseconds
const int buttonPin = 2; // Example button pin, adjust as needed
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0; // Last time the output pin was toggled
unsigned long debounceDelay = 50;   // The debounce time; adjust as needed
const int drawerPins[16][3] = {
    {11, 13, 12}, // Drawer 1: Floor 1 R, L, M
    {10, 9, 8},   // Drawer 2: Floor 2 R, L, M
    {29, 7, 6},   // Drawer 3: Floor 3 R, L, M
    {27, 23, 25}, // Drawer 4: Floor 4 R, L, M
    {24, 26, 28}, // Drawer 5: Assumed Floor 5 R, L, M
    {30, 32, 34}, // Drawer 6: Assumed Floor 6 R, L, M
    {36, 53, 51}, // Drawer 7: Assumed Floor 7 R, L, M
    {49, 47, 45}, 
};
// The order is maybe not obligatory but we are going to work with it anyway

void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(buttonPin, INPUT_PULLUP);

  // Array of non-sequential pin numbers initialized directly in the loop
  int pins[] = {13, 12, 11, 10, 9, 8, 7, 6, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53};

  // Loop to set the pinMode for the pins in the array
  for (int i = 0; i < sizeof(pins)/sizeof(pins[0]); i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH); // Set most pins to HIGH as per the original setup
  }

  // The pin 38 is an exception and needs to be set LOW
  pinMode(38, OUTPUT);
  digitalWrite(38, LOW);
}

void loop() {
  static uint32_t oldTime = millis();
  bool reading = digitalRead(buttonPin);
  
  // Check for button state change due to bounce or press
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state.
    if (reading == LOW) {
      fastRun = !fastRun;
      fastRunStartTime = millis();
      while(digitalRead(buttonPin) == LOW); // Wait for button release to avoid multiple toggles
    }
  }

  lastButtonState = reading;

  // Check if fast run should be turned off after 5 minutes
  if (fastRun && (millis() - fastRunStartTime >= fastRunDuration)) {
    fastRun = false;
  }

  sensors.requestTemperatures();
  systemTemp = sensors.getTempCByIndex(0);
  
  // Safety checks
  Serial.println(systemTemp);
  if(systemTemp > 12.5 && systemTemp != -127.00)
    digitalWrite(37, HIGH);
  if(systemTemp < 11 && systemTemp != -127.00)
    digitalWrite(37, LOW);

  // Time interval between drawer actions
  unsigned long interval = fastRun ? 6000 : 60000; // Adjusted for fast run
  if ((millis() - oldTime) > interval) {
    oldTime = millis();
    Serial.println(systemTemp);
    drawerAirOn(drawerCounter);
    drawerCounter = drawerCounter % 16 + 1; // Loop back after 16
  }
}

void drawerAirOn(int drawerNumber) {
  if(systemTemp < 12.5) {
    int delayShort = fastRun ? 250 : 500; // Shorter delay if fast run
    int delayLong = fastRun ? 2500 : 5000; // Longer delay if fast run

    for (int action = 0; action < 3; action++) {
      // Actuate Right, Left, then Center
      digitalWrite(drawerPins[drawerNumber - 1][action], LOW);
      delay(delayShort);
      digitalWrite(drawerPins[drawerNumber - 1][action], HIGH);

      if (action < 2) { // Delay after Right and Left
        delay(delayLong);
      } else { // Special handling for Center
        for(int repeat = 0; repeat < 3; repeat++) { // Repeat action for Center
          delay(delayLong);
          digitalWrite(drawerPins[drawerNumber - 1][action], LOW);
          delay(delayShort);
          digitalWrite(drawerPins[drawerNumber - 1][action], HIGH);
        }
      }
    }
  }
}

