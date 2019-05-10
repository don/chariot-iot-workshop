// IoT Workshop
// Control a LED via MQTT

#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>

#include "config.h"

WiFiSSLClient net;
MqttClient mqtt(net);

String ledTopic = "workshop/" + DEVICE_ID + "/led";

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);

  // Uncomment next line to wait for a serial connection
  // while (!Serial) { }
 
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Connecting WiFi");
  connectWiFi();

  // define function for incoming MQTT messages
  mqtt.onMessage(messageReceived);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!mqtt.connected()) {
    connectMQTT();
  }
  
  // poll for new MQTT messages and send keep alives
  mqtt.poll();
}

void connectWiFi() {
  // Check for the WiFi module
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  Serial.print("WiFi firmware version ");
  Serial.println(WiFi.firmwareVersion());
  
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(WIFI_SSID);
  Serial.print(" ");

  while (WiFi.begin(WIFI_SSID, WIFI_PASSWORD) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(3000);
  }

  Serial.println("Connected to WiFi");
  printWiFiStatus();

}

void connectMQTT() {
  Serial.print("Connecting MQTT...");
  mqtt.setId(DEVICE_ID);
  mqtt.setUsernamePassword(MQTT_USER, MQTT_PASSWORD);

  while (!mqtt.connect(MQTT_BROKER, MQTT_PORT)) {
    Serial.print(".");
    delay(5000);
  }

  mqtt.subscribe(ledTopic);
  Serial.println("connected.");
}

void messageReceived(int messageSize) {
  String topic = mqtt.messageTopic();
  String payload = mqtt.readString();
  Serial.println("incoming: " + topic + " - " + messageSize + " ");
  Serial.println(payload);
  if (payload == "ON") {
    // turn the LED on
    digitalWrite(LED_BUILTIN, HIGH);
  } else if (payload == "OFF") {
    // turn the LED off
    digitalWrite(LED_BUILTIN, LOW);    
  }
}

void printWiFiStatus() {
  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
