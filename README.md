# IoT-Octopus
The umbrella repository [Codename: ***'Octopus'***] of all the experiments/assignments/hands-on as a part of learning and exploration in the field of Internet of Things.

## Hardware Requirements
* __Lolin NodeMCU ESP8266 CP2012 NodeMCU WiFi Serial Wireless Module__
* __MB102 Breadboard__
* __USB Data Cable__
* __1kΩ Resistor__
* __LED__
* _16 Sensor Modules( [Quad Store](https://www.quadstore.in) 16 in 1 Sensor Kit ) Arduino Uno R3, Mega 2560_
  - __DHT 11 Temperature and Humidity Sensor__
* __Jumper Wires__
  - Male-to-Male type
  - Male-to-Female type
  - Female-to-Female type

## Installation
1. Download [Arduino IDE](https://www.arduino.cc/en/Main/Software) and install using recommended settings.

1. Do remember to check the type of __COM Port__ present in your machine, under __Device Manager > Ports__.

1. In Arduino IDE, under __Tools > Board__, select __NodeMCU x.x (ESP-12E Module)__.  [x.x denotes the version number, we are currently using __v1.0__]

1. Under __Sketch > Include Library > Manage Libraries__, search and install the following:
   - __DHT Sensor Library by Adafruit__ (use latest version, we're currently using __v1.3.4__), make sure DHT 11 is mentioned in the description.

1. [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor.git) contains __*necessary*__ files to get your sketch up and running.
Visit the link, clone, extract and copy-paste (with replacement) in the library where your Arduino packages reside.
   - If you installed [Arduino IDE](https://www.arduino.cc/en/Main/Software) in the default location,
   
     > (C:\Users\\{your_username}\Documents\Arduino)
     
     path should contain your library packages on a Windows machine.
     

## Contributing
Pull requests are welcome.

__NOTE:__ Contributors with push access are requested to push into the respective file/folder.

## License
[MIT](https://choosealicense.com/licenses/mit/)
