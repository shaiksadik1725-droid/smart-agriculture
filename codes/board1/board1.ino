#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define SOIL A1
#define PH A2
#define WATER A3
#define SOIL_RELAY 2
#define PH_RELAY 3
#define FAN_RELAY 4
#define TEC1 6
#define TEC2 7
#define DHTPIN 5
#define DHTTYPE DHT22
#define PROBE_PIN 8
#define RED_LED 9
#define YELLOW_LED 10
#define GREEN_LED 1
#define BUZZER 12
DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(PROBE_PIN);
DallasTemperature probe(&oneWire);
int soilPump;
int phPump;
int fan;
void setup() {
  Serial.begin(9600);
  pinMode(SOIL_RELAY, OUTPUT);
  pinMode(PH_RELAY, OUTPUT);
  pinMode(FAN_RELAY, OUTPUT);
  pinMode(TEC1, OUTPUT);
  pinMode(TEC2, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  dht.begin();
  probe.begin();
  if (!LoRa.begin(915E6)) {
    Serial.println("LoRa Failed");
    while (1);
  }
  Serial.println("BOARD 1 READY");
}
void loop() {
  int soil = analogRead(SOIL);
  int phRaw = analogRead(PH);
  int water = analogRead(WATER);
  float ph = 14.0 - (phRaw * (14.0 / 1023.0));
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  probe.requestTemperatures();
  float probeTemp = probe.getTempCByIndex(0);
  // SOIL PUMP
  if (soil < 400) {
    digitalWrite(SOIL_RELAY, HIGH);
    soilPump = 1;
  } else {
    digitalWrite(SOIL_RELAY, LOW);
    soilPump = 0;
  }
  // PH PUMP
  if (ph < 6 || ph > 8) {
    digitalWrite(PH_RELAY, HIGH);
    phPump = 1;
  } else {
    digitalWrite(PH_RELAY, LOW);
    phPump = 0;
  }
  // FAN
  if (temp > 30) {
    digitalWrite(FAN_RELAY, HIGH);
    fan = 1;
  } else {
    digitalWrite(FAN_RELAY, LOW);
    fan = 0;
  }
  if (probeTemp > 28) {
    digitalWrite(TEC1, HIGH);
    digitalWrite(TEC2, LOW);
} else if (probeTemp < 24) {
    digitalWrite(TEC1, LOW);
    digitalWrite(TEC2, HIGH);
} else {
    digitalWrite(TEC1, LOW);
    digitalWrite(TEC2, LOW);
}
  //WATER LEVEL SYSTEM
  if (water < 300) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, HIGH);
  }
  else if (water > 300 && water < 990) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, LOW);
  }
  else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER, LOW);
  }
  // SERIAL MONITOR
  Serial.print("Soil: ");
  Serial.print(soil);
  Serial.print(" | PH: ");
  Serial.print(ph);
  Serial.print(" | Temp: ");
  Serial.print(temp);
  Serial.print(" | Hum: ");
  Serial.print(hum);
  Serial.print(" | Probe: ");
  Serial.print(probeTemp);
  Serial.print(" | Water: ");
  Serial.print(water);
  Serial.print(" | SoilPump: ");
  Serial.print(soilPump ? "ON" : "OFF");
  Serial.print(" | PHPump: ");
  Serial.print(phPump ? "ON" : "OFF");
  Serial.print(" | Fan: ");
  Serial.println(fan ? "ON" : "OFF");
  // LORA SEND
  LoRa.beginPacket();
  LoRa.print("1,");
  LoRa.print(soil);
  LoRa.print(",");
  LoRa.print(ph);
  LoRa.print(",");
  LoRa.print(temp);
  LoRa.print(",");
  LoRa.print(hum);
  LoRa.print(",");
  LoRa.print(probeTemp);
  LoRa.print(",");
  LoRa.print(water);
  LoRa.print(",");
  LoRa.print(soilPump);
  LoRa.print(",");
  LoRa.print(phPump);
  LoRa.print(",");
  LoRa.print(fan);
  LoRa.endPacket();
  delay(3000);
}