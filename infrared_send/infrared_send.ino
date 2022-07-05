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
        code = 0xFFA25D;
      break;
      case '2':
        code = 0xFF629D;
      break;
      case '3':
        code = 0xFFE21D;
      break;
      case '4':
        code = 0xFF22DD;
      break;
      case '5':
        code = 0xFF02FD;
      break;
      case '6':
        code = 0xFFC23D;
      break;
      case '7':
        code = 0xFFE01F;
      break;
      case '8':
        code = 0xFFA857;
      break;
      case '9':
        code = 0xFF906F;
      break;
      case '10':
        code = 0xFF6897;
      break;
      case '11':
        code = 0xFF0967;
      break;
      case '12':
        code = 0xFFB04F;
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
