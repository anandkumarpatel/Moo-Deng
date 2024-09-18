#include <Keyboard.h>
#include <IRremote.h>

const int trigPin = 9;
const int echoPin = 10;
float duration, distance;
bool isGameStart = false;


const int tempPin = A5;

const int waterPin = A0;

const int soundPin = 2;

void setup() {
  // make pin 2 an input and turn on the
  // pullup resistor so it goes high unless
  // connected to ground:

  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(5, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  //if the button is pressed
  if (!isGameStart && digitalRead(5) == LOW) {
    //Send an ASCII '<space>',
    Keyboard.write(32);
    Serial.println("space");
    isGameStart = true;
   delay(100);
   

  }

if(!isGameStart) {
  return;
}

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2; // cm
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);

  Serial.println(analogRead(tempPin));
  Serial.println(analogRead(waterPin));
  
  if(digitalRead(soundPin) == HIGH){
  Serial.println("sound");
delay(100);
  }



}