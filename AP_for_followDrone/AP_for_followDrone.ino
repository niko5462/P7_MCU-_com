#include <WiFi.h>

const char* apSSID = "followDrone";
const char* apPassword = "AndersOst";

WiFiServer server(80);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.softAP(apSSID, apPassword);

  IPAddress apIP(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(apIP, apIP, subnet);
  
  server.begin();
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  if (client.connected()) {
    if (client.available()) {
      String data = client.readStringUntil('\n');
      Serial.println(data);
    }
  } else {
    Serial.println("Client disconnected.");
    delay(1000);

    // Attempt to accept a new client connection
    client = server.available();
  }
}
