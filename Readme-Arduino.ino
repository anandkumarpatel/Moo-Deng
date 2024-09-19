#include <Keyboard.h>
const int trigPin = 9;
const int echoPin = 10;
bool isGameStart = false;
const int TARGET_DISTANCE = 10;
const int DISTANCE_DELTA = 2;
const int TARGET_TEMPERATURE = 420;
const int TARGET_WATER_LEVEL = 150;
const int tempPin = A5;
bool tempDone = false;
const int waterPin = A0;
bool waterDone = false;
const int soundPin = 2;
bool soundDone = false;
const int coinPin = 8;

const int movePin = 10;
bool isMoving = false;
bool moveDone = false;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(movePin, INPUT);
  pinMode(coinPin, INPUT_PULLUP);
  Keyboard.begin();
}
void loop() {
  if (!isGameStart && digitalRead(coinPin) == LOW) {
    // Keyboard.write(32);
    Serial.println("space");
    isGameStart = true;
    delay(100);
   }
  if(!isGameStart) {
    return;
  }
  int temperature = analogRead(tempPin);
  // Serial.print("temperature: ");
  // Serial.println(temperature);
  if (!tempDone && temperature <= TARGET_TEMPERATURE) {
    tempDone = true;
    Serial.println("temp reached");
  }
  int waterLevel = analogRead(waterPin);
  // Serial.print("waterLevel: ");
  // Serial.println(waterLevel);
  if (!waterDone && waterLevel <= TARGET_WATER_LEVEL) {
    waterDone = true;
    Serial.println("water reached");
  } else {
    waterDone = false;
  }
  int soundHeard = digitalRead(soundPin);
  if(soundHeard == HIGH){
    Serial.println("sound");
    soundDone = true;
  } else {
    soundDone = false;
  }

  int moveVal = digitalRead(movePin);  
  if (moveVal == HIGH) {  
    if (isMoving == false) { 
      Serial.println("Motion detected");  
      isMoving = true;
      moveDone = true;
    } 
  } else { 
    if (isMoving){ 
      Serial.println("The motion has stopped"); 
      isMoving = false;  
    } 
  } 

  if (moveDone && tempDone && waterDone && soundDone) {
    Keyboard.write(10);
    Serial.println("konami");
    tempDone = false;
    waterDone = false;
    soundDone = false;
    delay(30000);
    Serial.println("konami done");
  }
}
