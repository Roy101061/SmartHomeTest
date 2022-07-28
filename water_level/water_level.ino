int OutPin = 36;
int Water_level = 0;

void setup() {
  Serial.begin(115200);
  pinMode(OutPin,INPUT);
}

void loop() {
  Water_level = digitalRead(OutPin);
  Serial.print("Water_level= ");
  Serial.println(Water_level);
  if(Water_level==0){

  }
  delay(1000); //delay 1s
}
