#include "DHT.h"
//#include "Adafruit_sensor.h"
#include <ESP8266WiFi.h>

const char* ssid="IIESTS";
const char* password = "";



int ledPin = LED_BUILTIN;
#define DHTPIN 2  //GPIO 2 i.e. D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  delay(500);
  dht.begin();
  Serial.begin(9600);// speed of nodemcu
  Serial.println();  
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }

  digitalWrite( ledPin , HIGH);
  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );
  
  Serial.println();
  
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);
  Serial.println("Humidity (%)\tTemperature (C)");
}

void loop()
{
  delay(2000);
  //Serial.println(digitalRead(DHTPIN));
  float h = dht.readHumidity();
  //delay(2000);
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) { h=0; t=0; }
  Serial.print("   ");
  Serial.print(h);  Serial.print("\t\t");
  Serial.print("    ");
  Serial.print(t);  Serial.print("\n");
  delay(1000);
}
