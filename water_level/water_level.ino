#include <analogWrite.h> 
int OutPin = 18;
int ADJ_Pin = 19;

void setup() {
  Serial.begin(115200);
  pinMode(OutPin,INPUT);
  pinMode(ADJ_Pin,INPUT); // Wondering how to use or useless.
  int Water_level = 0;
}

void loop() {
  Water_level = digitalRead(OutPin);
  Serial.print("Water_level= ");
  Serial.println(Water_level);
  if(Water_level!=0){

  }
  delay(30000); //delay 30s
}
