void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  delay(2000);
  Serial.println("Ready");
}

void loop() {
    String s = "";
    boolean t = false;
    while(Serial1.available()) {
       s = Serial1.readString();
       t = true;
    }

    if (t){
      Serial.println("Received message from ESP8266!");
      Serial.println(s);
    }
}
