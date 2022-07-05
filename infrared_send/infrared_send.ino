#include <IRremote.h>
int SignalPin = 5;
int ControllerPin = 18;
IRsend irsend;

void setup() {
  Serial.begin(115200);
	pinMode(SignalPin,INPUT);
	pinMode(ControllerPin,OUTPUT);
}

void loop() {
  int chose;
  if( (chose = Serial.read()) != -1) {
  unsigned long code = 0x0;
   switch(chose){
      case '1':
        code = 0x77E14050;
      break;
      case '2':
        code = 0x77E12050;
      break;
      case '3':
        code = 0x77E1D050;
      break;
      case '4':
        code = 0x77E1B050;
      break;
      case '5':
        code = 0x77E1E050;
      break;
      case '6':
        code = 0x77E11050;
      break;
    }
  
  if(code != 0x0){
      Serial.print("read ");
      Serial.print(chose);
      Serial.print(", IR send ");
      Serial.println(code, HEX);
      irsend.sendNEC(code, 32);
    }
  }
}
