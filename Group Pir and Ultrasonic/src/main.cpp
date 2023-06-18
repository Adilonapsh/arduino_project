#include <Arduino.h>

const int pir= 0;
const int trigPin = 5;
const int echoPin = 4;

long duration;
int distance;

void setup() {
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH);

  distance= duration*0.034/2;

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);

  long state = digitalRead(pir);
    if(state == HIGH) {
      Serial.println("Motion detected!");
      delay(1000);
    }
    else {
      Serial.println("Motion absent!");
      delay(1000);
      }
}