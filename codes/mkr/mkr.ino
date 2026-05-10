#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial1.begin(9600);
  if (!LoRa.begin(915E6)) {
    while (1);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String data = "";
    while (LoRa.available()) {
      data += (char)LoRa.read();
    }
    Serial1.println(data);
  }
}