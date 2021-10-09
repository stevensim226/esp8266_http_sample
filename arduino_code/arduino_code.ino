#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WifiClient.h>

WiFiClient wifiClient;

String ssid = "XXXXX"; // WiFi Access Point name
String password = "XXXXX"; // WiFi password

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.write("Connecting..");
 
  }
}

void writeString(String stringData) { // Used to serially push out a String with Serial.write()

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);   // Push each char 1 by 1 on each loop pass
  }

}

void loop() {
  delay(3000);
  Serial.write("Hello from ESP8266!\n");

  HTTPClient http;
  http.begin(wifiClient, "http://time.jsontest.com/");
  int httpCode = http.GET();
  String payload = http.getString();

  Serial.write("HTTP Response Code: ");
  writeString(String(httpCode));
  Serial.write("\n");
  writeString(payload);

  
}
