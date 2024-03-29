#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define GPS_BAUDRATE 9600  // The default baudrate of NEO-6M is 9600
#define RX2 19
#define TX2 18
#define PCK_INTERVAL 200

TinyGPSPlus gps;  // the TinyGPS++ object
EspSoftwareSerial::UART ss;

char gpsData[100];

struct Data {
  double Lat = 0;
  double Long = 0;
  double Alt = 0;
  double Time = 0;
} Loc;

void getData() {
  //Serial.println(F("GPS Signal: (lat, lng, alt)"));
  Loc.Lat = gps.location.lat();
  Loc.Long = gps.location.lng();
  Loc.Alt = gps.altitude.meters();
}

void setup() {
  Serial.begin(9600);

  ss.begin(GPS_BAUDRATE, SWSERIAL_8N1, RX2, TX2);
  Serial.println("GPS module activating...");
}

void loop() {
  if (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (gps.location.isValid()) {
        getData();
        sprintf(gpsData, "%.8f,%.8f,%.2f", Loc.Lat, Loc.Long, Loc.Alt);
        Serial.println(gpsData);

        if (millis() > 5000 && gps.charsProcessed() < 10) {
          Serial.println(F("No GPS data received: check wiring"));
        }
      }
    }
  }
}
