#include <analogWrite.h> 
int OutPin = 18;
int ADJ_Pin = 19;

void setup() {
  Serial.begin(115200);
  pinMode(OutPin,INPUT);
  pinMode(ADJ_Pin,INPUT);
  int water_level = 0;
}

void loop() {

}
