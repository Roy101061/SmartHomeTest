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
  int type;
  if( (chose = Serial.read()) != -1) {
  unsigned long code = 0x0;
   switch(chose){
      case '1':
        code = 0xFFA25D;
        type = 8;
      break;
      case '2':
        code = 0xFF629D;
        type = 8;
      break;
      case '3':
        code = 0xFFE21D;
        type = 8;
      break;
      case '4':
        code = 0xFF22DD;
        type = 8;
      break;
      case '5':
        code = 0xFF02FD;
        type = 8;
      break;
      case '6':
        code = 0xFFC23D;
        type = 8;
      break;
      case '7':
        code = 0xFFE01F;
        type = 8;
      break;
      case '8':
        code = 0xFFA857;
        type = 8;
      break;
      case '9':
        code = 0xFF906F;
        type = 8;
      break;
    }
  
  if(code != 0x0){
      Serial.print("read ");
      Serial.print(chose);
      Serial.print(", IR send ");
      Serial.println(code, HEX);
      if(type!=-1){
        switch(type){
          case '1':
            irsend.sendNEC(code, 32);
          break;
          case '2':
            irsend.sendSony(code, 32);
          break;
          case '3':
            irsend.sendRC5(code, 32);
          break;
          case '4':
            //irsend.sendRC6(code, 32);
          break;
          case '5':
            irsend.sendDISH(code, 32);
          break;
          case '6':
            irsend.sendSharp(code, 32);
          break;
          case '7':
            irsend.sendPanasonic(code, 32);
          break;
          case '8':
            //irsend.sendJVC(code, 32);
          break;
          case '9':
            //irsend.sendSanyo(code, 32);
          break;
          default :
            //irsend.sendKaseikyo_Mitsubishi(code, 32);
          break;
        }
      }
    }
  }
}
