#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WifiClient.h>
#include <PubSubClient.h>

WiFiClient wifiClient;
PubSubClient client;

String ssid = "XXXXX";
String password = "XXXXX";

String mqtt_broker = "192.168.1.8";
String topic = "python/esp8266";
int mqtt_port = 1883;

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.write("Message arrived in topic: ");
    writeString(topic);
    Serial.write("\n'");
    for (int i = 0; i < length; i++) {
        writeString(String((char)payload[i]));
    }
    Serial.write("'\n-----------------------");
}

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.write("Connecting..\n");
 
  }
  
  Serial.write("Connected to Wi-Fi!, Hello from ESP8266!\n");


  Serial.write("Connecting to MQTT server...\n");
  
  client.setClient(wifiClient);
  client.setServer("192.168.1.8", 1883);
  client.setCallback(callback);
  while (!client.connected()) {
      String client_id = "esp8266-client-2";
      
      if (client.connect(client_id.c_str())) {
      } else {
          Serial.write("failed with state ");
          writeString(String(client.state()));
          Serial.write("\n");
          delay(1000);
      }
  }

  Serial.write("Connected to MQTT Broker! subscribing to 'python/esp8266'\n");
  
  client.publish(topic.c_str(), "Initial ESP8266 message!");
  client.subscribe("python/esp8266");

  Serial.write("Awaiting for messages to 'python/esp8266' topic through MQTT...\n");
}

void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }

}

void loop() {
  client.loop();
}
