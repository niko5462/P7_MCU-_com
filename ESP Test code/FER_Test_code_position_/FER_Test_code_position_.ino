
#include <WiFi.h>

#define RX2 16
#define TX2 17
#define PCK_INTERVAL 200
#define PCK_VOLUME 2000

const char* ssid = "followDrone";    // Same as the access point SSID
const char* password = "AndersOst";  // Same as the access point password

const char* serverIP = "192.168.1.1";  // IP address of the receiver ESP32
const int serverPort = 80;

double cnt = 1;

WiFiClient client;

char dataSend[100];
 
void sendDataLoop(char *array, int dataVolume) {
  double f1 = (57000+cnt)/1000;
  double f2 = (9000+cnt)/1000;
  sprintf(array, "%.3f,%.3f,%.2f", f1, f2, double(millis()));
  client.println(array);                      // sends the data to the client
  Serial.println("Data sent: " + String(array));
  array[0] = '\0';
  cnt += 1;
  if (cnt >= PCK_VOLUME){
    Serial.println("Client Disconnected");
    client.stop();
  }

    /*
    for (int i = 0; i < dataVolume; i++){
        float f1 = (57000+i)/1000;
        float f2 = (9000+i)/1000;
        sprintf(array, "%.3f,%.3f,%.2f", f1, f2, i);
        client.println(array);                      // sends the data to the client
        Serial.println("Data sent: " + String(array));
        array[0] = '\0';                            // emptying the char array  
    }
    */
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
        sendDataLoop(dataSend, PCK_VOLUME);
        delay(PCK_INTERVAL);
    } else {
        Serial.println("Connection lost. Reconnecting...");
        connectToServer();
        delay(5000);  // Retry every 5 seconds
    }
}
