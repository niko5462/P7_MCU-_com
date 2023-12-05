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
      Serial.println("Received : " + data);
      mavlink_message_t msg;
      uint8_t buf[MAVLINK_MAX_PACKET_LEN];

      // Pack the message
      mavlink_msg_statustext_pack(2, 200, &msg, MAV_SEVERITY_INFO, data.c_str());

      // Convert the message to a sendable buffer
      uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
      // Write the buffer to the serial port
      cubeOrange.write(buf, len);

      delay(5);
    }
  } else {
    Serial.println("Client disconnected.");
    delay(1000);

    // Attempt to accept a new client connection
    client = server.available();
  }
}
