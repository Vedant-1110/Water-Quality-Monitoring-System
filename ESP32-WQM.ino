/************ BLYNK CONFIG ************/
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3qk9tbRUz"
#define BLYNK_TEMPLATE_NAME "WATER QUALITY MONITORING"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

/************ LIBRARIES ************/
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/************ WIFI ************/
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

/************ PINS ************/
#define TDS_PIN        34
#define TURBIDITY_PIN  35
#define ONE_WIRE_BUS   4

/************ OBJECTS ************/
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
BlynkTimer timer;

/************ VARIABLES ************/
float voltage, tdsValue;
float lastTemp = 0.0;
int lastTurbidity = 0;
float lastTDS = 0.0;
bool csvHeaderSent = false;

/************ TDS FUNCTION ************/
void readTDS() {
  int analogValue = analogRead(TDS_PIN);
  voltage = analogValue * (3.3 / 4095.0);

  tdsValue = (133.42 * voltage * voltage * voltage
             - 255.86 * voltage * voltage
             + 857.39 * voltage) * 0.5;

  lastTDS = tdsValue;
  Blynk.virtualWrite(V0, tdsValue);
}

/************ TURBIDITY FUNCTION ************/
void readTurbidity() {
  int turbidityValue = analogRead(TURBIDITY_PIN);
  int kal = (turbidityValue - 2717.6) / -18.189;

  lastTurbidity = kal;

  String status;
  if (kal > 0 && kal < 49) status = "Clear";
  else if (kal >= 50 && kal < 75) status = "Cloudy";
  else if (kal >= 76) status = "VeryCloudy";
  else status = "Invalid";

  Blynk.virtualWrite(V1, kal);
  Blynk.virtualWrite(V4, status);

  lcd.setCursor(0, 0);
  lcd.print("Turb:");
  lcd.print(kal);
  lcd.print("    ");

  lcd.setCursor(0, 1);
  lcd.print(status);
  lcd.print("    ");
}

/************ TEMPERATURE FUNCTION ************/
void readTemperature() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  if (tempC == DEVICE_DISCONNECTED_C) {
    return;
  }

  lastTemp = tempC;
  Blynk.virtualWrite(V2, tempC);
}

/************ CSV LOGGER FUNCTION ************/
void logCSV() {
  if (!csvHeaderSent) {
    Serial.println("Time(ms),Temperature(C),Turbidity,TDS");
    csvHeaderSent = true;
  }

  Serial.print(millis());
  Serial.print(",");
  Serial.print(lastTemp);
  Serial.print(",");
  Serial.print(lastTurbidity);
  Serial.print(",");
  Serial.println(lastTDS);
}

/************ SETUP ************/
void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  lcd.begin(16, 2);
  lcd.backlight();

  sensors.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  WiFi.setSleep(false);

  timer.setInterval(1000L, readTDS);
  timer.setInterval(1500L, readTurbidity);
  timer.setInterval(2000L, readTemperature);
  timer.setInterval(3000L, logCSV);   // CSV append every 3 sec

  Serial.println("System Started");
}

/************ LOOP ************/
void loop() {
  Blynk.run();
  timer.run();
}
