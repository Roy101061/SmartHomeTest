int OutPin = 36;

void setup() {
  Serial.begin(115200);
  pinMode(OutPin,INPUT);
}

void loop() {
  int Water_level = 0;
  Water_level = analogRead(OutPin);
  Serial.print("Water_level= ");
  Serial.println(Water_level);
  if(Water_level!=0){

  }
  delay(1000); //delay 1s
}
