
#include <WiFi.h>

#define RX2 16
#define TX2 17
#define PCK_INTERVAL 200

const char* ssid = "followDrone";    // Same as the access point SSID
const char* password = "AndersOst";  // Same as the access point password

const char* serverIP = "192.168.1.1";  // IP address of the receiver ESP32
const int serverPort = 80;

WiFiClient client;

char dataSend[100];
 
void sendDataLoop(char array, int dataVolume) {
    for (int i = 0; i < dataVolume; i++){
        array = char(57000+i)+', '+char(9000+i);
        client.println(array);                      // sends the data to the client
        Serial.println("Data sent: " + array);
        array[0] = '\0';                            // emptying the char array  
    }
}

void connectToServer() {
  client.connect(serverIP, serverPort);
  if (client.connected()) {
    Serial.println("Connected to the server.");
  } else {
    Serial.println("Connection to the server failed.");
  }
}

void setup() {
  Serial.begin(115200);  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
  connectToServer();
  Serial.println("GPS module activating...");
}

void loop() {
    if (client.connected()) {
        sendDataLoop(dataSend,int 1000);
        delay(PCK_INTERVAL);
    } else {
        Serial.println("Connection lost. Reconnecting...");
        connectToServer();
        delay(5000);  // Retry every 5 seconds
    }
}
