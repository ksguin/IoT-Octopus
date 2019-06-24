#include <DHT.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>


#define SERVER            "io.adafruit.com"
#define SERVERPORT        1883
#define MQTT_USERNAME     ""   //write your MQTT username
#define MQTT_KEY          ""   //write your adafruit key
#define USERNAME          ""   //write your adafruit username
#define PREAMBLE          "feeds/"
#define T_TEMPERATURE     "Temparature"
#define T_HUMIDITY        "Humidity"
#define T_COMMAND         "command"

const char* ssid="IIESTS";
const char* password = "";


int  prevtemp=0;
int  prevhum=0;
int ledPin = LED_BUILTIN;
#define DHTPIN 2  //GPIO2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


//unsigned long entry;
//byte clientStatus, prevClientStatus = 99;
//float luminosity, prevLumiosity = -1;
char valueStr[5];

WiFiClient WiFiClient;
// create MQTT object
PubSubClient client(WiFiClient);



void setup()
{
  pinMode(ledPin,OUTPUT);
  //digitalWrite(ledPin,LOW);
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
  WiFi.printDiag(Serial);

  client.setServer(SERVER, SERVERPORT);
  //client.setCallback(callback);
  
}

void loop()
{
  delay(2000);

  yield();
  if (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(USERNAME , MQTT_USERNAME, MQTT_KEY)) {
      Serial.println("connected");
      // ... and resubscribe
      //client.subscribe(USERNAME PREAMBLE T_COMMAND, 1);
      //client.subscribe(USERNAME PREAMBLE "test", 1);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  
  
  //Serial.println(digitalRead(DHTPIN));
  float humidit = dht.readHumidity();
  //delay(5000);
  float temperature = dht.readTemperature();
  if (isnan(humidit) || isnan(temperature)) { humidit=0; temperature=0; }
  Serial.print("   ");
  Serial.print(temperature);  
  Serial.print("\t\t");
  Serial.print("    ");
  Serial.print(humidit);  
  Serial.print("\n");
  
    
   if (client.connected() && (prevtemp != temperature || prevhum!=humidit)) 
   {
    Serial.println("Publish temperature");
    String hi = (String)temperature;
    hi.toCharArray(valueStr, 5);
    client.publish(USERNAME PREAMBLE T_TEMPERATURE, valueStr);
    prevtemp=temperature;

    Serial.println("Publish humidity");
    String hi1 = (String)humidit;
    hi1.toCharArray(valueStr, 5);
    client.publish(USERNAME PREAMBLE T_HUMIDITY, valueStr);
    prevhum=humidit;
  
   }
   delay(8000);
  
}
