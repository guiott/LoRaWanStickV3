This is a test Arduino project for an Heltech Wireless Stick(V3): https://heltec.org/project/wireless-stick-v3/.
In order to save battery charge, the Stick has been modified in the way I described in documentation folder. Please also look at other hardware issues described in the same folder.
The Stick is arranged in a portable container supplied with a 18650 3000mAh battery.
The purpose is to verify of far from my Seeedstudio Capsense gateway it can be received, and how long the battery charge can last, setting different duty cycles.
The portable box contains also a Wurth Elektronics dev board for temperature and humidity sensor, to return usefull data: https://www.we-online.com/en/components/products/WSEN-HIDS.
The project requires Heltech libraries: https://github.com/HelTecAutomation/Heltec_ESP32 and Sensirion libraries for the sensor SHT40 (fully compatible with Wurth WSEN_HIDS): https://github.com/Sensirion/arduino-i2c-sht4x

The original LoRaWan_APP library has been modified because all the functions related to the display are not compatible with Wireless Stick(V3). They are replaced by the ones in Display.ino. 
<<<<<<< HEAD
In LoRaWan_APP there also are the functions to display communication data on display.
=======
Please put "**DOC/ModifiedLibs/GoLoRaWan_APP**" in "**Arduino/libraries/Heltec-ESP32-Dev-Boards/src/**" and remove the original ones.
>>>>>>> 49bfd3c8262e6aa2bfe602944d53f1e90d7c0dd2

Also the original RegionCommon library has been modified in order to export Tx Power data and show it on display.

Please put **"DOC/ModifiedLibs/GoLoRaWan_APP.c and .h"** in **"Arduino/libraries/Heltec-ESP32-Dev-Boards/src/"** and remove the original ones.

Please put **"DOC/ModifiedLibs/RegionCommon.c and .h"** in **"Arduino/libraries/Heltec-ESP32-Dev-Boards/src/loramac/region"** and remove the original ones.
 
To start working rename Config.h_TEMPLATE in Config.h and edit keys to your own needs.

The repository contains also the javascript code for the gateway codec to parse the packet to MQTT broker.
