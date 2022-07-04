#include <analogWrite.h> 
int Signal = 18;
int PowerPin = 19;

void setup() {
  Serial.begin(115200);
  pinMode(Signal,INPUT);
  pinMode(PowerPin,OUTPUT);
}

void loop() {

}
