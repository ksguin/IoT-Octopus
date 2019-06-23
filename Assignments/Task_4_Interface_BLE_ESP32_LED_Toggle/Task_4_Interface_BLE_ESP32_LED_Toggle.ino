/* To interface Bluetooth with NodeMCU ESP32 and write a program to turn LED ON/OFF when ‘1’/’0’ is received from smartphone using Bluetooth. */

#include "BluetoothSerial.h"

BluetoothSerial SerialBT;   //Serial BT object

int LED_PIN = 2;    //GPIO 2, i.e. D2 on ESP-WROOM-32.
bool ledState = false;

bool ledStateCheck(char val) {
  if(val == '0')
    return false;
  else
    return true;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin("ESP32_LED_Toggle");   //SerialBT device name
  Serial.println("Bluetooth Device is ready to Pair");

  pinMode(LED_PIN, OUTPUT);  //setting LED pin as output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(SerialBT.available())    //to check if we are receiving anything from BT
  {
    ledState = ledStateCheck(SerialBT.read());
    Serial.println(ledState);

    if(ledState == true)
    {
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(LED_BUILTIN, HIGH);
      SerialBT.println("LED ON");
    }
    else
    {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(LED_BUILTIN, LOW);
      SerialBT.println("LED OFF");
    }

    delay(20);
  }
}
