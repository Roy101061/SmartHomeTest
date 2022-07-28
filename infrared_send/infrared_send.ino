#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

//=============================
const char* ssid = "Apex_TPLink";
const char* password = "ACME70472615";
//const char* ssid = "JASON";
//const char* password = "96116157";
//=============================
const char* mqtt_server = "210.68.227.123";
const char* clientID = "ESP32";      // 用戶端ID，隨意設定。
const char* mqttUserName = "acme";  // mqtt使用者名稱
const char* mqttPwd = "85024828";  // MQTT密碼
const char* pub_topic = "Light";
const char* sub_topic = "Light";
//=============================
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
//=============================
unsigned long times = 0;
int gBoardID = -1;
//=============================
DynamicJsonDocument doc(1024);

void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String info = "";
  for (int i = 0; i < length; i++) {
    info += (char)payload[i];
    //Serial.print((char)payload[i]);
  }
  Serial.println(info);
  GetJSON(info);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientID, mqttUserName, mqttPwd)) {
      Serial.println("connected");
      //=======================================================================
      //client.publish(pub_topic, "ESP8266 connected");
      client.subscribe(sub_topic);
      //=======================================================================
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 3 seconds");
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  gBoardID = getBoardID(WiFi.macAddress());
  delay(10);
  setup_wifi();
  client.setServer(mqtt_server, 3881);
  client.setCallback(callback);
  delay(1);
  Serial.println(gBoardID);
}

void loop() {
  if (millis() - times > 1000) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    times = millis();
  }  
}

void GetJSON(String str_json) {
  //id:null,power:0
  deserializeJson(doc, str_json);
  JsonObject obj = doc.as<JsonObject>();
  int esp_id = obj["id"];
  bool esp_power = obj["power"];
  Serial.print("id:");
  Serial.print(esp_id);
  Serial.print(",power:");
  Serial.println(esp_power);
  if (esp_id == gBoardID) {
    Serial.println("This is my ID, so I'll doing something!!");
    Serial.println(gBoardID);
  }
}

//=======================================================================
int getBoardID(String MacAddress)
{
  String mac0 = getValue(MacAddress, ':', 0);
  String mac4 = getValue(MacAddress, ':', 4);
  String mac5 = getValue(MacAddress, ':', 5);

  int rtn = hexToDec(mac0) * hexToDec(mac4) * hexToDec(mac5);

  return rtn;
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

int hexToDec(String Hex)
{
  int stringLen = Hex.length() + 1;

  char hexInChar[stringLen];
  Hex.toCharArray(hexInChar, stringLen);

  return strtol(hexInChar, 0, 16);
}


#include <Arduino.h>
#include <IRremote.h>
#define NO_LED_FEEDBACK_CODE

int SignalPin = 5;
int ControllerPin = 4;

void setup() {
  Serial.begin(115200);
	pinMode(SignalPin,INPUT);
	pinMode(ControllerPin,OUTPUT);
  IrSender.begin(ControllerPin);
}

void loop() {
  int chose;
  int Code;
  int bits;
  int type = 0;
  uint16_t Address;
  uint16_t Command;

  if( (chose = Serial.read()) != -1) {
   switch(chose){
      case '1':
        Address = 0xB24D;
        type = 2;
        Command = 0x13B2;
        bits = 48;
        Serial.println("chose1");
      break;
      case '2':
        Address = 0x0;
        type = 1;
        Command = 0x46;
        bits = 32;
        Serial.println("chose2");
      break;
      case '3':
        Address = 0x0;
        type = 1;
        Command = 0x47;
        bits = 32;
        Serial.println("chose3");
      break;
      case '4':
        Address = 0x0;
        type = 1;
        Command = 0x44;
        bits = 32;
        Serial.println("chose4");
      break;
      case '5':
        Address = 0x0;
        type = 1;
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
          IrSender.sendSony(Address, Command, 3, bits);
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
        break;
        case 19:
          IrSender.sendShuzu(Address, Command, 0);
          Serial.println("send check19!");
        break;
        default :
          IrSender.sendNECRaw(Code);
          Serial.println("send check20!");
        break;
      }
    }
  }
}
