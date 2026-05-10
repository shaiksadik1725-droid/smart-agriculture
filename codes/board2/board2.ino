#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define SOIL A1
#define WATER A2
#define SOIL_RELAY 2
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
int fan;
void setup() {
  Serial.begin(9600);
  pinMode(SOIL_RELAY, OUTPUT);
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
  Serial.println("BOARD 2 READY");
}
void loop() {
  int soil = analogRead(SOIL);
  int water = analogRead(WATER);
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
  // FAN CONTROL
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
  // WATER LEVEL SYSTEM
  if (water < 200) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, HIGH);
  }
  else if (water > 200 && water < 900) {
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
  Serial.print(" | Fan: ");
  Serial.println(fan ? "ON" : "OFF");
  // LORA SEND
  LoRa.beginPacket();
  LoRa.print("2,");
  LoRa.print(soil);
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
  LoRa.print(fan);
  LoRa.endPacket();
  delay(3000);
}