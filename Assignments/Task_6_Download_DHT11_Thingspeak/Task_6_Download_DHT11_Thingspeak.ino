/* A program on NodeMCU ESP8266 to Download Temperature and Humidity data from ThingSpeak platform. */

#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <WiFiClient.h>

const char* ssid = "IIESTS";
const char* password = "";

//ThingSpeak credentials
unsigned long myChannelNumber = ; //Your Channel Number (Without Brackets)
const char *myReadAPIKey = ""; //Your Read API Key

WiFiClient client;

unsigned int TempField = 1;
unsigned int HumidityField = 2;
int statusCode = 0;
/* ------------------------------------------------------------------------ */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);// speed of ESP8266
  pinMode(LED_BUILTIN, OUTPUT);

  WiFiconnect();  //connect to WiFi
  ThingSpeak.begin(client);  // Initialize ThingSpeak with client
}

void loop() {
  // put your main code here, to run repeatedly:
  //If client isn't connected, reconnect to WiFi
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Reconnecting...");
    delay(1000);
    WiFiconnect();
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    //Read Temperature Field from ThingSpeak
    float temp_data =  ThingSpeak.readFloatField(myChannelNumber, TempField, myReadAPIKey);
    statusCode = ThingSpeak.getLastReadStatus();
    if (statusCode == 200) {
      Serial.print("Temperature: ");
      Serial.print(temp_data);
      Serial.print("°C, ");
    }
    else {
      Serial.print(statusCode);
      Serial.println(": Unable to read Temperature.");
    }
    //delay(1000);

    //Read Humidity Field from ThingSpeak
    float humidity_data =  ThingSpeak.readFloatField(myChannelNumber, HumidityField, myReadAPIKey);
    statusCode = ThingSpeak.getLastReadStatus();
    if (statusCode == 200) {
      Serial.print("Humidity: ");
      Serial.print(humidity_data);
      Serial.println("%");
    }
    else {
      Serial.print(statusCode);
      Serial.println(": Unable to read Humidity.");
    }
  } else {
    Serial.println("WiFi disconnected.");
  }

  delay(16000);
}

void WiFiconnect() {
  //LED OFF when WiFi isn't connected
  digitalWrite(LED_BUILTIN, HIGH);  //Built-in LED works opposite

  WiFi.begin(ssid,password);
  Serial.println();
  Serial.print("WiFi connecting to ");
  Serial.println(ssid);

  //connecting dots
  Serial.print("Connecting");
  while( WiFi.status() != WL_CONNECTED ){
      delay(800);
      Serial.print(".");
  }
  //LED ON when WiFi connection established
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println();
  Serial.print("Connection Established! ");
  Serial.print("NodeMCU IP Address: ");
  Serial.println(WiFi.localIP());
}
