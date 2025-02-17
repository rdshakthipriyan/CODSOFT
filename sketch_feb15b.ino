/*
  Arduino AI-Powered Crop Monitoring System
  Supports Wi-Fi (ESP32/ESP8266) and Non-Wi-Fi (Arduino Uno)
  Reads soil moisture, light, temperature, humidity, CO₂, air quality
  Compares readings with selected crop's optimal conditions
  Alerts on console and webpage if conditions are out of range
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
#endif

#define DHTPIN 5
#define DHTTYPE DHT11
#define SOIL_MOISTURE_PIN A0
#define LIGHT_SENSOR_PIN A1
#define CO2_SENSOR_PIN A2
#define AIR_QUALITY_PIN A3

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* serverURL = "http://yourserver.com/data";

struct Crop {
  String name;
  int soilMoistureMin, soilMoistureMax;
  int lightMin, lightMax;
  int tempMin, tempMax;
  int humidityMin, humidityMax;
  int co2Min, co2Max;
  int airQualityMin, airQualityMax;
};

Crop crops[] = {
  {"Wheat", 50, 70, 30000, 50000, 10, 22, 50, 70, 400, 600, 0, 50},
  {"Rice", 100, 100, 40000, 60000, 20, 35, 70, 90, 400, 800, 0, 50},
  {"Maize", 60, 80, 40000, 60000, 18, 32, 60, 80, 400, 600, 0, 50},
  {"Soybean", 50, 70, 35000, 50000, 20, 30, 60, 75, 400, 700, 0, 50},
  {"Potato", 70, 85, 25000, 50000, 15, 22, 60, 80, 400, 800, 0, 50},
  {"Tomato", 60, 80, 40000, 60000, 18, 28, 60, 70, 600, 1000, 0, 50}
};

int selectedCrop = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Select Crop");

  #ifdef ESP32 || ESP8266
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting...");
    }
    Serial.println("Connected!");
  #endif
}

void loop() {
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  int lightIntensity = analogRead(LIGHT_SENSOR_PIN);
  int co2Level = analogRead(CO2_SENSOR_PIN);
  int airQuality = analogRead(AIR_QUALITY_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Crop crop = crops[selectedCrop];
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(crop.name);
  lcd.setCursor(0, 1);
  lcd.print("Temp: " + String(temperature) + "C");
  
  String alertMessage = "";

  if (soilMoisture < crop.soilMoistureMin) {
    alertMessage += "Increase irrigation by " + String(crop.soilMoistureMin - soilMoisture) + " units. ";
  } else if (soilMoisture > crop.soilMoistureMax) {
    alertMessage += "Reduce irrigation by " + String(soilMoisture - crop.soilMoistureMax) + " units. ";
  }
  if (lightIntensity < crop.lightMin || lightIntensity > crop.lightMax) {
    alertMessage += "Adjust light intensity. ";
  }
  if (temperature < crop.tempMin) {
    alertMessage += "Increase temperature by " + String(crop.tempMin - temperature) + "°C. ";
  } else if (temperature > crop.tempMax) {
    alertMessage += "Decrease temperature by " + String(temperature - crop.tempMax) + "°C. ";
  }
  if (humidity < crop.humidityMin) {
    alertMessage += "Increase humidity by " + String(crop.humidityMin - humidity) + "%. ";
  } else if (humidity > crop.humidityMax) {
    alertMessage += "Decrease humidity by " + String(humidity - crop.humidityMax) + "%. ";
  }
  if (co2Level < crop.co2Min || co2Level > crop.co2Max) {
    alertMessage += "Adjust CO2 levels. ";
  }
  if (airQuality < crop.airQualityMin || airQuality > crop.airQualityMax) {
    alertMessage += "Improve air quality. ";
  }

  if (alertMessage.length() > 0) {
    Serial.println("ALERT: " + alertMessage);
    lcd.setCursor(0, 1);
    lcd.print("Check Console!");
  }

  #ifdef ESP32 || ESP8266
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverURL);
    http.addHeader("Content-Type", "application/json");
    String jsonData = "{";
    jsonData += "\"temperature\": " + String(temperature) + ",";
    jsonData += "\"humidity\": " + String(humidity) + ",";
    jsonData += "\"alert\": \"" + alertMessage + "\"}";
    http.POST(jsonData);
    http.end();
  #endif

  delay(5000);
}
