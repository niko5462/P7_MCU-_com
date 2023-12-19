#include <mavlink.h> // Assuming mavlink.h is in the same directory as the source file
#include <Arduino.h> // Arduino standard library
#include <HardwareSerial.h> // Arduino standard library's hardware serial

HardwareSerial cubeOrange(2);

void setup() {
  cubeOrange.begin(57600);
  Serial.begin(115200);
}

void loop() {
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
  mavlink_msg_statustext_pack(2, 200, &msg, MAV_SEVERITY_INFO, "---------hello cube bitch------");
  
  // Convert the message to a sendable buffer
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  
  // Write the buffer to the serial port
  cubeOrange.write(buf, len);
  
  delay(5);
}