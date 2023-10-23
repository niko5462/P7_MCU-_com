#include <WiFi.h>

const char* ssid = "followDrone";    // Same as the access point SSID
const char* password = "AndersOst";  // Same as the access point password

const char* serverIP = "192.168.1.1";  // IP address of the receiver ESP32
const int serverPort = 80;

const int pckInterval = 500;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi.");
  connectToServer();
}

void connectToServer() {
  client.connect(serverIP, serverPort);
  if (client.connected()) {
    Serial.println("Connected to the server.");
  } else {
    Serial.println("Connection to the server failed.");
  }
}

String dataToSend() {
  const String positionObject = " per pik";  //TODO: DENNE LINJE SKAL ERSTATTES MED LONG LAT ALT FRA GPS SIGNAL
  return positionObject;
}

void sendData(String dataToSend) {
  client.println(dataToSend);
  Serial.println("Data sent: " + dataToSend);
}

void loop() {
  if (client.connected()) {
      sendData(dataToSend());
      delay(pckInterval);
    } else {
    Serial.println("Connection lost. Reconnecting...");
    connectToServer();
    delay(5000);  // Retry every 5 seconds
  }
}
