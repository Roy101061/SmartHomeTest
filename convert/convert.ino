int Trig = 4;
int Echo = 16;
int DataPin = 17;
float Celsius,Humidity,Fahrenheit;
#include "DHT.h"
#define DHTPIN DataPin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  pinMode(DataPin,INPUT);
  dht.begin();
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

  if(Distance(EchoTime)>=10){
    
  }
  else{
    
  }

  Humidity = dht.readHumidity();
  Celsius = dht.readTemperature();
  Fahrenheit = dht.readTemperature(true);

  if (isnan(Celsius)||isnan(Humidity)||isnan(Fahrenheit)){
    Serial.println("Fail to read data from DHT!");
    Serial.println(Celsius);
    Serial.println(Humidity);
    Serial.println(Fahrenheit);
  }
  else{
    float IndexFahrenheit = dht.computeHeatIndex(Fahrenheit, Humidity);
    float IndexCelsius = dht.computeHeatIndex(Celsius, Humidity, false);
    Serial.print(F("Humidity: "));
    Serial.print(Humidity);
    Serial.print(F("%  Temperature: "));
    Serial.print(Celsius);
    Serial.print(F("°C "));
    Serial.print(Fahrenheit);
    Serial.print(F("°F  Heat index: "));
    Serial.print(IndexCelsius);
    Serial.print(F("°C "));
    Serial.print(IndexFahrenheit);
    Serial.println(F("°F"));
  }

  delay(5000); //delay 5s
}
