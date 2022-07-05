int Trig = 4;
int Echo = 16;

void setup() {
  Serial.begin(115200);
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
}
int Distance(int EchoTime){
  return EchoTime*34/2/1000;
}

void loop() {
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10); 
  digitalWrite(Trig, LOW); 
  
  float EchoTime = pulseIn(Echo, HIGH); 
  Serial.print(Distance(EchoTime));
  Serial.println("cm");

  if(Distance(EchoTime)<=10 || Distance(EchoTime)>=1000){
    Serial.println("True");
  }
  else{
    
  }

  delay(500); //delay 0.5s
}
