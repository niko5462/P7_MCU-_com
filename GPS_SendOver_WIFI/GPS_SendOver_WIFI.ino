#include <TinyGPS++.h>
#include <WiFi.h>

#define GPS_BAUDRATE 9600  // The default baudrate of NEO-6M is 9600
#define RX2 16
#define TX2 17
#define PCK_INTERVAL 200

const char* ssid = "followDrone";    // Same as the access point SSID
const char* password = "AndersOst";  // Same as the access point password

const char* serverIP = "192.168.1.1";  // IP address of the receiver ESP32
const int serverPort = 80;


WiFiClient client;
HardwareSerial gpsSerial(2);
TinyGPSPlus gps;  // the TinyGPS++ object

char gpsData[100];

struct Data {
  double Lat = 0;
  double Long = 0;
  double Alt = 0;
  double Time = 0;
} Loc;

void getData() {
  Loc.Lat = gps.location.lat();
  Loc.Long = gps.location.lng();
  Loc.Alt = gps.altitude.meters();
}

void sendData(String dataToSend) {
  client.println(dataToSend);
  Serial.println("Data sent: " + dataToSend);
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
  gpsSerial.begin(GPS_BAUDRATE);
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
  if (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        getData();
        sprintf(gpsData, "%.8f,%.8f,%.2f", Loc.Lat, Loc.Long, Loc.Alt);
        
        if (millis() > 5000 && gps.charsProcessed() < 10) {
          Serial.println(F("No GPS data received: check wiring"));
        }

        if (client.connected()) {
          sendData(gpsData);
          gpsData[0] = '\0';  // emptying the char array
          delay(PCK_INTERVAL);
        } else {
          Serial.println("Connection lost. Reconnecting...");
          connectToServer();
          delay(5000);  // Retry every 5 seconds
        }
      }
    }
  }
}
