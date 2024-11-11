#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
unsigned long lastDHTReadTime = 0;
const unsigned long DHTReadInterval = 2000;

//===========================WiFi=========================//
const char* ssid = "Nguyet Anh";
const char* passwifi = "khoa5470";
WiFiClient espClient;

//===========================DHT11=========================//
#define DHTTYPE DHT11
#define DHTPIN 23
DHT dht(DHTPIN, DHTTYPE);

void setupWiFi() 
{
  delay(10);
  Serial.println();
  Serial.print("Connecting WiFi to ");
  Serial.print(ssid);
  WiFi.begin(ssid, passwifi);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void setup() 
{
  Serial.begin(115200);
  setupWiFi();
}

void dht11Read()
{
  // Kiểm tra thời gian đọc cuối cùng
  if (millis() - lastDHTReadTime >= DHTReadInterval) {
    lastDHTReadTime = millis();

    // Đọc giá trị từ cảm biến DHT11
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // Kiểm tra nếu việc đọc thất bại và báo lỗi
    if (isnan(h) || isnan(t)) 
    {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));
  }
}

void loop() 
{

  dht11Read();
  delay(2000);
}