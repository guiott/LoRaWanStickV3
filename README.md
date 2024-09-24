This is a test Arduino project for an Heltech Wireless Stick(V3): https://heltec.org/project/wireless-stick-v3/.
In order to save battery charge, the Stick has been modified in the way I described in documentation folder.
The Stick is arranged in a portable container supplied with a 18650 3000mAh battery.
The purpose is to verify of far from my Seeedstudio Capsense gateway it can be received, and how long the battery charge can last, setting different duty cycles.
The portable box contains also a Wurth Elektronics dev board for temperature and humidity sensor, to return usefull data: https://www.we-online.com/en/components/products/WSEN-HIDS.
The project requires Heltech libraries: https://github.com/HelTecAutomation/Heltec_ESP32 and Sensirion libraries for the sensor SHT40 (fully compatible with Wurth WSEN_HIDS): https://github.com/Sensirion/arduino-i2c-sht4x

The repository contains also the javascript code for the gateway codec to parse the packet to MQTT broker.
