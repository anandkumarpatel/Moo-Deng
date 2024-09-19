#include <Keyboard.h>

bool isGameStart = false;
const int TARGET_TEMPERATURE = 420;
const int TARGET_WATER_LEVEL = 150;
const int TARGET_LIGHT = 50;
const int tempPin = A5;
bool tempDone = false;
const int waterPin = A0;
bool waterDone = false;
const int soundPin = 2;
bool soundDone = false;
const int coinPin = 8;
const int lightPin = A4;

bool isMoving = false;
bool lightDone = false;

const int led1 = 12;

void setup() {
  Serial.begin(9600);
  pinMode(coinPin, INPUT_PULLUP);
  pinMode(led1, OUTPUT);

  isGameStart = false;
  tempDone = false;
  waterDone = false;
  soundDone = false;
  isMoving = false;
  lightDone = false;


  Keyboard.begin();
}
void loop() {

  if (!isGameStart && digitalRead(coinPin) == LOW) {
    Keyboard.write(32);
    Serial.println("space");
    isGameStart = true;
    digitalWrite(led1, HIGH);
    delay(1000);
   }

  if(!isGameStart) {
    return;
  }

  if (!tempDone) {
    int temperature = analogRead(tempPin);
    // Serial.print("temperature: ");
    // Serial.println(temperature);
    if (temperature <= TARGET_TEMPERATURE) {
      tempDone = true;
      Serial.println("temp reached");
    }
  }

  // unsigned long currentTime = millis();
  // Serial.print("Current time: ");
  // Serial.println(currentTime);
  if (!waterDone) {
    int waterLevel = analogRead(waterPin);
    // Serial.print("waterLevel: ");
    // Serial.println(waterLevel);
    if (waterLevel <= TARGET_WATER_LEVEL) {
      waterDone = true;
      Serial.println("water reached");
    }
  }

  int soundHeard = digitalRead(soundPin);
  if(soundHeard == HIGH){
    Serial.println("sound");
    soundDone = true;
  } else {
    soundDone = false;
  }


  if (!lightDone) {
    int lightValue = analogRead(lightPin);
    if (lightValue < TARGET_LIGHT) {
    lightDone = true;
      Serial.println("light reached");
    }
  }

  if (lightDone && tempDone && waterDone && soundDone) {
    Keyboard.write(10);
    Serial.println("konami");
    tempDone = false;
    waterDone = false;
    soundDone = false;
    lightDone = false;
    delay(30000);
    Serial.println("konami done");
  }
}
