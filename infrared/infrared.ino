#include <IRremote.h>
int SignalPin = 5;
int ControllerPin = 18;
IRrecv irrecv(SignalPin);
decode_results results;

void setup() {
  Serial.begin(115200);
	pinMode(SignalPin,INPUT);
	pinMode(ControllerPin,OUTPUT);
  irrecv.blink13(true);
	irrecv.enableIRIn(); 
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("results value is ");
    Serial.print(results.value, HEX);
    Serial.print(", bits is ");
    Serial.print(results.bits);
    Serial.print(", decode_type is ");
    Serial.println(results.decode_type);
    irrecv.resume();
  }
}
