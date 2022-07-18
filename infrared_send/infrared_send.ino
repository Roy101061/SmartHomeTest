#include <IRremote.h>
int SignalPin = 5;
int ControllerPin = 18;
IRsend irsend;

void setup() {
  Serial.begin(115200);
	pinMode(SignalPin,INPUT);
	pinMode(ControllerPin,OUTPUT);
  IrReceiver.begin(ControllerPin, ENABLE_LED_FEEDBACK);
}

void loop() {
  int chose;
  int Code;
  int bits;
  int type = 0;
  unsigned long Address;
  unsigned long Command;
  if( (chose = Serial.read()) != -1) {
   switch(chose){
      case '1':
        Address = 0x0;
        type = 1;
        Command = 0x45;
        bits = 32;
        Serial.println("chose1");
      break;
      case '2':
        Address = 0x0;
        type = 2;
        Command = 0x46;
        bits = 32;
        Serial.println("chose2");
      break;
      case '3':
        Address = 0x0;
        type = 3;
        Command = 0x47;
        bits = 32;
        Serial.println("chose3");
      break;
      case '4':
        Address = 0x0;
        type = 4;
        Command = 0x44;
        bits = 32;
        Serial.println("chose4");
      break;
      case '5':
        Address = 0x0;
        type = 5;
        Command = 0x40;
        bits = 32;
        Serial.println("chose5");
      break;
      case '6':
        Address = 0x0;
        type = 1;
        Command = 0x43;
        bits = 32;
        Serial.println("chose6");
      break;
      case '7':
        Address = 0x0;
        type = 1;
        Command = 0x7;
        bits = 32;
        Serial.println("chose7");
      break;
      case '8':
        Address = 0x0;
        type = 1;
        Command = 0x15;
        bits = 32;
        Serial.println("chose8");
      break;
      case '9':
        Address = 0x0;
        type = 1;
        Command = 0x9;
        bits = 32;
        Serial.println("chose9");
      break;
    }
  Serial.println(type);
  if(type != 0){
      switch(type){
        case 1:
          IrSender.sendNEC(Address, Command, 0, false);
          Serial.println("send check1!");
        break;
        case 2:
          IrSender.sendSamsung(Address, Command, 0);
          Serial.println("send check2!");
        break;
        case 3:
          IrSender.sendSony(Address, Command, 0, bits);
          Serial.println("send check3!");
        break;
        case 4:
          IrSender.sendPanasonic(Address, Command, 0);
          Serial.println("send check4!");
        break;
        case 5:
          IrSender.sendDenon(Address, Command, 0, false);
          Serial.println("send check5!");
        break;
        case 6:
          IrSender.sendSharp(Address, Command, 0);
          Serial.println("send check6!");
        break;
        case 7:
          IrSender.sendLG(Address, Command, 0, false, false);
          Serial.println("send check7!");
        break;
        case 8:
          IrSender.sendJVC(Address, Command, 0);
          Serial.println("send check8!");
        break;
        case 9:
          IrSender.sendRC5(Address, Command, 0, true);
          Serial.println("send check9!");
        break;
        case 10:
          IrSender.sendRC6(Address, Command, 0, true);
          Serial.println("send check10!");
        break;
        case 11:
          IrSender.sendKaseikyo_JVC(Address, Command, 0);
          Serial.println("send check11!");
        break;
        case 12:
          IrSender.sendKaseikyo_Denon(Address, Command, 0);
          Serial.println("send check12!");
        break;
        case 13:
          IrSender.sendKaseikyo_Sharp(Address, Command, 0);
          Serial.println("send check13!");
        break;
        case 14:
          IrSender.sendKaseikyo_Mitsubishi(Address, Command, 0);
          Serial.println("send check14!");
        break;
        case 15:
          IrSender.sendOnkyo(Address, Command, 0, true);
          Serial.println("send check15!");
        break;
        case 16:
          IrSender.sendApple(Address, Command, 0, false);
          Serial.println("send check16!");
        break;
        case 17:
          IrSender.sendBoseWave(Command, 0);
          Serial.println("send check17!");
        break;
        case 18:
          //IrSender.sendLegoPowerFunctions(Code, false);
          Serial.println("send check18!");
        default :
          IrSender.sendNECRaw(Code);
          Serial.println("send check19!");
        break;
      }
    }
  }
}
