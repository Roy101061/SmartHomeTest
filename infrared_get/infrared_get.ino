#include <IRremote.h>
int SignalPin = 3;
int ControllerPin = 18;

void setup() {
  Serial.begin(115200);
	pinMode(SignalPin,INPUT);
	pinMode(ControllerPin,OUTPUT);
  IrReceiver.begin(SignalPin, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData);
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume();
  }
}
