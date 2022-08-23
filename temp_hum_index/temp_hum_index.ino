#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define DataPin 17
float Celsius,Humidity,Fahrenheit;
#include "DHT.h"
#define DHTPIN DataPin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

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
const char* pub_topic = "Humidity_Temperature";
//const char* sub_topic = "Test";
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
      //client.subscribe(sub_topic);
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

  Serial.begin(115200);
  pinMode(DataPin,INPUT);
  dht.begin();
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

void loop() {
  if (millis() - times > 1000) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    times = millis();
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
    Serial.print(F("Humidity: "));
    Serial.print(Humidity);
    Serial.print(F("Temperature: "));
    Serial.print(Celsius);
    Serial.print(F("°C "));
    Serial.print(Fahrenheit);
    Serial.println(F("°F"));
    client.beginPublish(pub_topic, 49, false);

    client.print(F("Humidity: "));
    client.print(Humidity);
    client.print(F("Temperature: "));
    client.print(Celsius);
    client.print(F("°C "));
    client.print(Fahrenheit);
    client.println(F("°F "));
    client.endPublish();
  }

  delay(10000); //delay 10s
}
