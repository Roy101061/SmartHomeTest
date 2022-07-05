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
  Serial.println(Distance(EchoTime));

  if(Distance(EchoTime)>=5){
    
  }
  else{
    
  }

  delay(500); //delay 0.5s
}
