/* To interface DHT11 sensor with Arduino/Raspberry Pi/NodeMCU and write a program to
print temperature and humidity readings. */

#include "DHT.h"

#define DHTPIN 2  //GPIO 2 i.e. D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);// speed of nodemcu

  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);
  
  Serial.print("Initialising DHT");
  Serial.println(DHTTYPE);
  delay(500);
  dht.begin();
  
  Serial.println("Humidity (%)\tTemperature (℃)");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  float h = dht.readHumidity();
  delay(1000);
  float t = dht.readTemperature();
  
  if (isnan(h))
    h=0;
  if (isnan(t))
    t=0;

  delay(500);
  Serial.print("   ");
  Serial.print(h);  Serial.print("\t\t");
  Serial.print("    ");
  Serial.print(t);  Serial.print("\n");
}
