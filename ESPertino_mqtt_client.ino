/*
 Basic ESPertino MQTT example
 
 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESPertino board/library.

 It connects to an MQTT server then:
  - publishes "Hello ESPertinos #%ld" to the topic "ESPertino/Test1"  every 10 seconds

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.
 
 Notes:
 PubSubClient library source code is available here: https://github.com/knolleary/pubsubclient/
 This is a modified version of the "mqtt_esp8266.ino" example from Nick O'Leary available here:https://github.com/knolleary/pubsubclient/tree/master/examples/mqtt_esp8266

*/
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// WiFi network params
const char* ssid = "XXXXXXXXX";
const char* password = "XXXXXXXXX";
const char* mqtt_server = "test.mosquitto.org";

//MQTT params
const char* pubTopic = "ESPertino/Test1";
#define MQTT_SEND_PERIOD_MS 10000 //10sec

//Espertino LEDs
#define LED4_PIN 5
#define LED5_PIN 13
#define MQTT_CONNECTION_LED LED5_PIN

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {  
  pinMode(MQTT_CONNECTION_LED, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      digitalWrite(MQTT_CONNECTION_LED, LOW);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  long now = millis();
  if (now - lastMsg > MQTT_SEND_PERIOD_MS) {
    
    if (!client.connected()) {
      digitalWrite(MQTT_CONNECTION_LED, HIGH);
      reconnect();
    }
    client.loop();

    lastMsg = now;
    ++value;
    snprintf (msg, 75, "Hello ESPertinos #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(pubTopic, msg);
  }
}
