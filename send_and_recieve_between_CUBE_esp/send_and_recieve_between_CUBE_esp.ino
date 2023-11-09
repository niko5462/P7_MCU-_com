
#include <mavlink.h>
HardwareSerial cubeOrange(2);
unsigned long oldTime = 0; 

void setup() {
  cubeOrange.begin(57600);
  Serial.begin(115200);
}

void loop() {
mavlink_message_t msg;

uint8_t buf[MAVLINK_MAX_PACKET_LEN];
mavlink_msg_statustext_pack(1, 200, &msg, MAV_SEVERITY_INFO, "-------------------------VICTOR ER LORT MED MASTER YI-------------------------");
uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);

// Send the message
cubeOrange.write(buf, len);
//Read the message
String data = cubeOrange.readStringUntil('\n');
Serial.println("Recieved: "+ data);
// Delay for 1 second
delay(1000);

}
