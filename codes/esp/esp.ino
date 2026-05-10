#define BLYNK_TEMPLATE_ID "TMPL62NLfpaXB"
#define BLYNK_TEMPLATE_NAME "SMART AGRICULTURE"
#define BLYNK_AUTH_TOKEN "BZ1oHmOAWSLLHkBPZVZYhRHlRl4z-IhO"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

HardwareSerial MKRSerial(2);

char ssid[] = "HUAWEI_H112_DEA2";
char pass[] = "17ARQN13NFE";

void setup() {
  Serial.begin(115200);
  MKRSerial.begin(9600, SERIAL_8N1, 16, 17);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  
  Serial.println("ESP32 READY (SERIAL + BLYNK)");
}

void loop() {
  Blynk.run();

  if (MKRSerial.available()) {
    String data = MKRSerial.readStringUntil('\n');
    data.trim();

    Serial.println("\n========================");
    Serial.println("RAW: " + data);

    String v[10];
    int i = 0;
    while (data.length() > 0 && i < 10) {
      int comma = data.indexOf(',');
      if (comma == -1) {
        v[i++] = data;
        break;
      }
      v[i++] = data.substring(0, comma);
      data = data.substring(comma + 1);
    }

    // ================= BOARD 1 =================
    if (v[0] == "1") {
      Serial.println("BOARD 1 RECEIVED");
      Serial.println("--- VALUES ---");
      Serial.println("Soil:       " + v[1]);
      Serial.println("pH:         " + v[2]);
      Serial.println("Temp:       " + v[3]);
      Serial.println("Humidity:   " + v[4]);
      Serial.println("Probe Temp: " + v[5]);
      Serial.println("Water:      " + v[6]);
      Serial.println("Soil Pump:  " + v[7]);
      Serial.println("PH Pump:    " + v[8]);
      Serial.println("Fan:        " + v[9]);

      Blynk.virtualWrite(V0, v[1]);
      Blynk.virtualWrite(V1, v[2]);
      Blynk.virtualWrite(V2, v[3]);
      Blynk.virtualWrite(V3, v[4]);
      Blynk.virtualWrite(V4, v[5]);
      Blynk.virtualWrite(V5, v[6]);
      Blynk.virtualWrite(V6, v[7]);
      Blynk.virtualWrite(V7, v[8]);
      Blynk.virtualWrite(V8, v[9]);
    }

    // ================= BOARD 2 =================
    else if (v[0] == "2") {
      Serial.println("BOARD 2 RECEIVED");
      Serial.println("--- VALUES ---");
      Serial.println("Soil:       " + v[1]);
      Serial.println("Temp:       " + v[2]);
      Serial.println("Humidity:   " + v[3]);
      Serial.println("Probe Temp: " + v[4]);
      Serial.println("Water:      " + v[5]);
      Serial.println("Soil Pump:  " + v[6]);
      Serial.println("Fan:        " + v[7]);

      Blynk.virtualWrite(V10, v[1]);
      Blynk.virtualWrite(V11, v[2]);
      Blynk.virtualWrite(V12, v[3]);
      Blynk.virtualWrite(V13, v[4]);
      Blynk.virtualWrite(V14, v[5]);
      Blynk.virtualWrite(V15, v[6]);
      Blynk.virtualWrite(V16, v[7]);
    }

    Serial.println("========================\n");
  }
}