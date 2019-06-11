/* To interface LED with Arduino/Raspberry Pi/NodeMCU and write a program to turn ON
LED for 1 second after every 2 seconds. */

const int LED = 2;  //GPIO2 i.e. D4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);// speed of nodemcu
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);  //LED ON
  Serial.println("ON for 1s");
  delay(1000);              //1 second delay
  digitalWrite(LED, LOW);   //LED OFF
  Serial.println("OFF for 2s");
  delay(2000);              //2 second delay
}

//Using a resistor with cathode of the LED.
