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
  int Code;
  int type = 0; //NEC = 1 , SONY = 2 , RC5 = 3 , RC6 = 4 , UNKNOWN = 5
  unsigned long Address;
  unsigned long Command;
  if( (chose = Serial.read()) != -1) {
   switch(chose){
      case '1':
        Address = 0x0;
        type = 1;
        Command = 0x45;
      break;
      case '2':
        Address = 0x0;
        type = 1;
        Command = 0x46;
      break;
      case '3':
        Address = 0x0;
        type = 1;
        Command = 0x47;
      break;
      case '4':
        Address = 0x0;
        type = 1;
        Command = 0x44;
      break;
      case '5':
        Address = 0x0;
        type = 1;
        Command = 0x40;
      break;
      case '6':
        Address = 0x0;
        type = 1;
        Command = 0x43;
      break;
      case '7':
        Address = 0x0;
        type = 1;
        Command = 0x7;
      break;
      case '8':
        Address = 0x0;
        type = 1;
        Command = 0x15;
      break;
      case '9':
        Address = 0x0;
        type = 1;
        Command = 0x9;
      break;
    }
  
  if(type != 0){
      if(type!=0){
        switch(type){
          case '1':
            IrSender.sendNEC(Address, Command, true, 0);
            Serial.println("send check1!");
          break;
          case '2':
            IrSender.sendSony(Address, Command, true, 0);
            Serial.println("send check2!");
          break;
          case '3':
            IrSender.sendRC5(Address, Command, true, 0);
            Serial.println("send check3!");
          break;
          case '4':
            IrSender.sendRC6(Address, Command, true, 0);
            Serial.println("send check4!");
          break;
          default :
            IrSender.sendNECRaw(Code);
            Serial.println("send check5!");
          break;
        }
      }
    }
  }
}
