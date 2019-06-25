/* A program on NodeMCU ESP8266 to upload Temperature and Humidity data to ThingSpeak platform. */

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <WiFiClient.h>

#define DHTPIN 2  //GPIO2, i.e. D4 on ESP8266
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "IIESTS";
const char* password = "";

//ThingSpeak credentials
unsigned long myChannelNumber = ; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = ""; //Your Write API Key

WiFiClient client;

#define TempField 1
#define HumidityField 2
/* ------------------------------------------------------------------------ */

float prevtemp = 0;
float prevhum = 0;

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

  //Reading Data from DHT11 sensor
  float temp_data = dht.readTemperature();
  delay(200);
  float humidity_data = dht.readHumidity();
  
  //If either one is NaN, discard that reading
  if (isnan(humidity_data) || isnan(temp_data)) { humidity_data = 0; temp_data = 0; }

  if (WiFi.status() == WL_CONNECTED) 
  {
    //Only if there is a change in value, upload, to reduce data redundancy
    if (prevtemp != temp_data || prevhum != humidity_data) 
    { //Publish the values to ThingSpeak
    
      // set the fields with the values
      ThingSpeak.setField(TempField, temp_data);
      ThingSpeak.setField(HumidityField, humidity_data);
      // writing multiple values to the ThingSpeak channel in one transaction
      int status = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
      //checking if data was successfully written.
      if(status == 200){
        Serial.print("Channel Update success:- Temp: ");
        Serial.print(temp_data);
        Serial.print("°C, Humidity: ");
        Serial.print(humidity_data);
        Serial.println("%");
      }
      else {
        Serial.println("Problem updating channel. HTTP error code " + String(status));
      }

      //set the current values as previous values
      prevtemp = temp_data;
      prevhum = humidity_data;
    } else {
      Serial.println("NaN/Duplicate Data Discarded");
    }
  } else {
    Serial.println("WiFi disconnected.");
 }
  delay(16000); // ThingSpeak will only accept updates atleast after every 15 seconds, so 16 seconds for safety
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
