#include <SoftwareSerial.h>

#define A6board Serial1

#ifndef A6board
SoftwareSerial A6board (2, 3);
#define A6baud 9600
#else
#define A6baud 115200
#endif


String hh;
char buffer[100];
char end_c[2];

void setup() {
  Serial.begin(115200);
  Serial.println(A6baud);
  A6board.begin(A6baud);
  Serial.println("Start");
  end_c[0] = 0x1a;
  end_c[1] = '\0';

}

void loop() {
  if (Serial.available()) {
    hh = Serial.readStringUntil('\n');
    hh.toCharArray(buffer, hh.length() + 1);
    if (hh.indexOf("ende") == 0) {
      A6board.write(end_c);
      Serial.println("ende");
    } else{
      A6board.write(buffer);
      A6board.write('\n');
    }
  }
  if (A6board.available()) {
    Serial.write(A6board.read());
  }
}
