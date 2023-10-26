#include <WiFi.h>
#include <mavlink.h>

const char* apSSID = "followDrone";
const char* apPassword = "AndersOst";

WiFiServer server(80);
WiFiClient client;
HardwareSerial cubeOrange(2);

void setup() {
  Serial.begin(115200);
  cubeOrange.begin(57600);
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
      cubeOrange.println(data + "per pik");      
     // mavlink_message_t msg;
     // uint8_t buf[MAVLINK_MAX_PACKET_LEN];
     // uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
     // cubeOrange.write(buf, len);
      delay(1000);
    }
  } else {
    Serial.println("Client disconnected.");
    delay(1000);

    // Attempt to accept a new client connection
    client = server.available();
  }
}