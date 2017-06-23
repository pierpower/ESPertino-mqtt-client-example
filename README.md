# ESPertino-mqtt-client-example

This is an MQTT client example to be used with [ESPertino board](http://it.emcelettronica.com/la-nuova-scheda-espertino-per-liot)

##Application description
The sample application connects to `test.mosquitto.org` MQTT broker and publishes every 10 second the message *Hello ESPertinos #xx* on the topic *ESPertino/Test1*

##Resources
The MQTT client library is available [here](https://github.com/knolleary/pubsubclient/).

##How To Build
1. Install the latest version of [Arduino IDE](https://www.arduino.cc/en/main/software)
1. Install the [ESP32 SDK] (https://github.com/espressif/arduino-esp32)
1. Import the PubSubClient library into Arduino IDE.
1. Open the `ESPertino_mqtt_client.ino` file with Arduino IDE.
1. On the top of the file substitute `const char* ssid = "XXXXXXXXX"` and `const char* password = "XXXXXXXXX"` with your WiFi network SSID and password.
1. Connect the ESPertino board to your PC
1. Press the *Load* button

##How To Run
1. Open a serial terminal and connect to the ESPertino board. Verify that the board can connect to the WiFi network.
1. Open a Linux terminal and subscribe to the ESPertino/Test1 topic by typing: `mosquitto_sub -h test.mosquitto.org -t ESPertino/Test1 -v`. This i
1. On the Linux terminal you should see the "Hello ESPertinos" message appearing every 10sec

##Note
This is a modified version of the "mqtt_esp8266.ino" example available [here](https://github.com/knolleary/pubsubclient/tree/master/examples/mqtt_esp8266)
