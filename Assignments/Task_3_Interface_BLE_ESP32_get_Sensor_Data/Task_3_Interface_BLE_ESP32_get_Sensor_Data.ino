#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic *pCharacteristic;

void setup() {
  
  Serial.begin(115200);   //speed of ESP32
  Serial.println("Initializing BLE... Name: MyESP32");
  
  BLEDevice::init("MyESP32");   //name of BLE device
  
  BLEServer *pServer = BLEDevice::createServer();   //ESP32 as BLE Server
  
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
    pCharacteristic->setValue("1");
    delay(4000);
    pCharacteristic->setValue("3");
    delay(3000);
}
