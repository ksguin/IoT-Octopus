/* ***
[IMPORTANT] From Play Store, Download "nRF Connect" App to view BLE Service Data & "Bluetooth Terminal" to view BT Serial Data.
*** */

/* To interface Bluetooth with NodeMCU ESP32 and write a program to send sensor data to smartphone using Bluetooth. */

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "BluetoothSerial.h"

//Using On-Board Maxim Integrated DS18B20 Temperature Sensor on ESP32 for measuring in-chip temperature
#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Bluetooth Serial object
BluetoothSerial SerialBT;
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {

  Serial.begin(115200);   //speed of ESP32
  Serial.println("Initializing BLE... Name: MyESP32");

  BLEDevice::init("MyESP32");   //name of BLE device
  SerialBT.begin("ESP32");  //SerialBT device name
  BLEServer *pServer = BLEDevice::createServer();   //ESP32 as BLE Server
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);    //Creating Service for the Server with UUID
  //defining characteristic of the Service(here READ only because the Client needs to only read sensor data)
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID,
                    BLECharacteristic::PROPERTY_READ);
  //setting value
  pCharacteristic->setValue("0");

  pService->start();
  Serial.println("Service started...");

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  Serial.println("Advertising...");
}

void loop() {
  delay(2000);
  if (deviceConnected) {
    //float txValue = random(1, 9) / 3.14 ;
    float txValue = (temprature_sens_read() - 32)*5 / 9;    //converting °F to °C
    char txString[8];
    dtostrf(txValue, 1, 2, txString); // float_val, min_width, digits_after_decimal, char_buffer
    pCharacteristic->setValue(txString);
    //writing to serial BT
    SerialBT.println(txString);
    Serial.print("Data Written: ");
    Serial.print(txString);
    Serial.println("°C");
  }
  delay(3000);
}
