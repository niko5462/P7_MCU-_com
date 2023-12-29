#include <TinyGPS++.h>

#define GPS_BAUDRATE 9600  // The default baudrate of NEO-6M is 9600
#define RX2 16 //
#define TX2 17
#define PCK_INTERVAL 200


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


void setup() {
  Serial.begin(115200);  
  gpsSerial.begin(GPS_BAUDRATE);
  Serial.println("GPS module connecting...");
}

void loop() {
  if (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
      
        //while(true){
          getData();
          //sprintf(gpsData, "%.8f,%.8f,%.2f", Loc.Lat, Loc.Long, Loc.Alt);
          sprintf(gpsData, "%.8f,%.8f", Loc.Lat, Loc.Long);

          if (millis() > 5000 && gps.charsProcessed() < 10) {
            Serial.println(F("No GPS data received: check wiring"));
            //break;
          }

          Serial.println(gpsData);
          gpsData[0] = '\0';
          delay(PCK_INTERVAL);
       // }
      }
    }
  }
}
