#include <ESP8266WiFi.h>
#include <PubSubClient.h>
//#include <SoftwareSerial.h>
 

// WiFi
const char *ssid = "mdhi2000"; // Enter your WiFi name Mohammad's iPhone            mdhi2000
const char *password = "troplonglaissetomber";  // Enter WiFi password   troplonglaissetomber

// MQTT Broker
const char *mqtt_broker = "mqtt.mdhi.dev";
const char *topic = "smarthome/#";
const char *mqtt_username = "smarthome";
const char *mqtt_password = "troplonglaissetomber";
const int mqtt_port = 1883;
// IPAddress mqtt_broker(185,202,113,239);

//software com serial 
//SoftwareSerial linkSerial(3, 1);

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("smarthome","123456789");
  
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
  Serial.println("AP IP adress:");
  Serial.print(WiFi.softAPIP());
  Serial.println();
}

void callback(char* topic, byte* message, unsigned int length) {
 // Serial.print("Message arrived on topic: ");
  //Serial.print(topic);
  //Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  Serial.println("<" + String(topic) + ":"+messageTemp+">");
//  Serial.print(topic);
//  Serial.print(":");
//  Serial.print(messageTemp);
//  Serial.print("-");
  
}

void reconnect() {
  // // Loop until we're reconnected
  while (!client.connected()) {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
 // pinMode(LED,OUTPUT);
  //digitalWrite(LED,HIGH);
  setup_wifi();
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);

//  linkSerial.begin(4800);
}

void loop() {
  if (!client.connected()) {
    
    reconnect();
    client.publish("smarthome/status","connected");
  }
  
  client.loop();

  if(Serial.available()){
    String payload = Serial.readString();

  }
}
