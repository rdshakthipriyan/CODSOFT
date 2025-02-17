/*
//                LIGHT INTENSITY SENSOR
                
int sensorPin = A0;  // Sensor output connected to A0
int sensorValue = 0;  // Variable to store sensor value

void setup() {
    Serial.begin(9600);  // Start serial communication
}

void loop() {
    sensorValue = analogRead(sensorPin);  // Read analog value
    Serial.print("Light Intensity: ");
    Serial.println(sensorValue);  // Print value to Serial Monitor
    delay(500);  // Wait for half a second
}
*/

/*
//                  GAS SENSOR

int gasAnalogPin = A0;  // Analog pin connected to sensor AO
int gasValue = 0;        // Variable to store sensor reading

void setup() {
    Serial.begin(9600);  // Start serial communication
}

void loop() {
    gasValue = analogRead(gasAnalogPin);  // Read gas sensor data
    Serial.print("Gas Sensor Value: ");
    Serial.println(gasValue);  // Print value in Serial Monitor
    delay(1000);  // Delay for readability
}
*/
/*
int gasAnalogPin = A0;  // Connect AO to A0
int gasDigitalPin = 2;  // Connect DO to D2
int gasValue = 0;
int gasStatus = 0;

void setup() {
    Serial.begin(9600);
    pinMode(gasDigitalPin, INPUT);
}

void loop() {
    gasValue = analogRead(gasAnalogPin);  // Read gas level
    gasStatus = digitalRead(gasDigitalPin);  // Check if above threshold

    Serial.print("Gas Sensor Value: ");
    Serial.print(gasValue);
    Serial.print(" | Digital Output: ");
    Serial.println(gasStatus);  // 0 (Safe) or 1 (Gas Detected)

    delay(1000);
}
*/
/*
//              WATER QUALITY SENSOR
#define TdsSensorPin A0
#define VREF 5.0  // Reference voltage (5V for Arduino Uno)
#define SCOUNT 30  // Number of samples for averaging

int analogBuffer[SCOUNT];  // Store analog readings
int analogBufferIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 25;

void setup() {
    Serial.begin(9600);
}

void loop() {
    static unsigned long analogSampleTime = millis();
    
    // Read analog values
    if (millis() - analogSampleTime > 40) {
        analogSampleTime = millis();
        analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);
        analogBufferIndex++;
        if (analogBufferIndex == SCOUNT) {
            analogBufferIndex = 0;

            // Calculate average voltage
            long sum = 0;
            for (int i = 0; i < SCOUNT; i++) sum += analogBuffer[i];
            averageVoltage = sum / SCOUNT * VREF / 1024.0;

            // Convert voltage to TDS (ppm)
            float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
            float compensationVoltage = averageVoltage / compensationCoefficient;
            tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage -
                        255.86 * compensationVoltage * compensationVoltage + 
                        857.39 * compensationVoltage) * 0.5;

            Serial.print("TDS Value: ");
            Serial.print(tdsValue);
            Serial.println(" ppm");
        }
    }
    delay(100);
}
*/
/*
  // LIGHT SENSOR

#define SENSOR_PIN 2 // Digital Output (DO) to D2

void setup() {
    Serial.begin(9600);
    pinMode(SENSOR_PIN, INPUT);
}

void loop() {
    int lightStatus = digitalRead(SENSOR_PIN); // Read the sensor output

    if (lightStatus == HIGH) {
        Serial.println("🌑 Low Light Detected!");
    } else {
        Serial.println("💡 Bright Light Detected!");
    }

    delay(1000);
}
*/
/*
#include <DHT.h>

#define DHTPIN 2       // Data pin connected to D2
#define DHTTYPE DHT22  // Using DHT22 sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    Serial.println("DHT22 Sensor Initialized");
    dht.begin();
}

void loop() {
    float temperature = dht.readTemperature(); // Get temperature in °C
    float humidity = dht.readHumidity(); // Get humidity in %

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT22 sensor!");
        return;
    }

    Serial.print("🌡️ Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    Serial.print("💧 Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    delay(2000); // Wait 2 seconds before reading again
}
*//*
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2       // Data pin connected to D2
#define DHTTYPE DHT22  // Define sensor type as DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing DHT22...");
    dht.begin();
}

void loop() {
    float temperature = dht.readTemperature(); // Read temperature in Celsius
    float humidity = dht.readHumidity(); // Read humidity in %

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Error: Failed to read from DHT22 sensor!");
        return;
    }

    Serial.print("🌡️ Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    Serial.print("💧 Humidity: ");
    Serial.print(humidity);
    Serial.println("%");

    delay(2000);
}
*/
/*
//    WATER QUALITY SENSOR
#define TDS_PIN A0  // Analog pin connected to TDS sensor
#define VREF 5.0    // Arduino voltage reference (5V)
#define ADC_RES 1024.0 // 10-bit ADC resolution

void setup() {
    Serial.begin(9600);
    Serial.println("TDS Sensor Initialized...");
}

void loop() {
    int sensorValue = analogRead(TDS_PIN);
    float voltage = sensorValue * (VREF / ADC_RES); // Convert ADC value to voltage
    float tdsValue = (133.42 * voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * 0.5; // TDS formula

    Serial.print("💧 TDS Value: ");
    Serial.print(tdsValue);
    Serial.println(" ppm");

    delay(1000);
}
*/
/*

//                     ESP8266 Wifi module
#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3); // RX, TX (Use pins D2 & D3)

void setup() {
    Serial.begin(9600);    // Serial Monitor Baud Rate
    espSerial.begin(115200); // ESP8266 Default Baud Rate

    Serial.println("ESP8266 Test Starting...");
    espSerial.println("AT"); // Send AT Command to ESP8266
}

void loop() {
    if (espSerial.available()) {
        Serial.write(espSerial.read()); // Read from ESP and print to Serial Monitor
    }
    if (Serial.available()) {
        espSerial.write(Serial.read()); // Send data to ESP
    }
}
