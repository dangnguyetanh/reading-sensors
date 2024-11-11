/*
  Title: Control your Arduino IoT projects with a MongoDB database
  Author: donsky (www.donskytech.com)
*/
#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "DHT.h"

// SSID and Password
const char *ssid = "Nguyet Anh";
const char *password = "khoa5470";

// The REST API endpoint - Change the IP Address
const char *base_rest_url = "http://192.168.100.22:5000/";

WiFiClient client;
HTTPClient http;

// Read interval
unsigned long previousMillis = 0;
const long readInterval = 5000;

char dhtObjectId[30] = "66f3b456800ad272c6426353";
#define DHTPIN 23 // Digital pin connected to the DHT sensor

// DHT11 config
#define DHTTYPE DHT11 // Sử dụng cảm biến DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Struct để lưu giá trị đọc từ DHT11
struct DHT11Readings
{
  float temperature;
  float humidity;
};

// Size of the JSON document. Sử dụng ArduinoJSON JSONAssistant
const int JSON_DOC_SIZE = 384;

// HTTP GET Call
StaticJsonDocument<JSON_DOC_SIZE> callHTTPGet(const char *sensor_id)
{
  char rest_api_url[200];
  // Gọi tới API server
  sprintf(rest_api_url, "%sapi/sensors?sensor_id=%s", base_rest_url, sensor_id);
  Serial.println(rest_api_url);

  http.useHTTP10(true);
  http.begin(client, rest_api_url);
  http.addHeader("Content-Type", "application/json");
  http.GET();

  StaticJsonDocument<JSON_DOC_SIZE> doc;
  // Parse response
  DeserializationError error = deserializeJson(doc, http.getStream());

  if (error)
  {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return doc;
  }

  http.end();
  return doc;
}

// Gửi dữ liệu DHT11 thông qua HTTP PUT
void sendDHT11Readings(const char *objectId, DHT11Readings dhtReadings)
{
  char rest_api_url[200];
  // Gọi tới API server
  sprintf(rest_api_url, "%sapi/sensors/%s", base_rest_url, objectId);
  Serial.println(rest_api_url);

  // Chuẩn bị dữ liệu JSON
  String jsondata = "";
  StaticJsonDocument<JSON_DOC_SIZE> doc;
  JsonObject readings = doc.createNestedObject("readings");
  readings["temperature"] = dhtReadings.temperature;
  readings["humidity"] = dhtReadings.humidity;

  serializeJson(doc, jsondata);
  Serial.println("JSON Data...");
  Serial.println(jsondata);

  http.begin(client, rest_api_url);
  http.addHeader("Content-Type", "application/json");

  // Gửi PUT request
  int httpResponseCode = http.PUT(jsondata);
  if (httpResponseCode > 0)
  {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  }
  else
  {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
    http.end();
  }
}

// Lấy ObjectId của DHT11
void getDHT11ObjectId(const char *sensor_id)
{
  StaticJsonDocument<JSON_DOC_SIZE> doc = callHTTPGet(sensor_id);
  if (doc.isNull() || doc.size() > 1)
    return;
  for (JsonObject item : doc.as<JsonArray>())
  {
    Serial.println(item);
    const char *objectId = item["_id"]["$oid"]; // "dht11_1"
    strcpy(dhtObjectId, objectId);

    return;
  }
  return;
}

// Đọc cảm biến DHT11
DHT11Readings readDHT11()
{
  // Đọc độ ẩm và nhiệt độ
  float humidity = dht.readHumidity();
  float temperatureInC = dht.readTemperature();

  return {temperatureInC, humidity};
}

void setup()
{
  Serial.begin(115200);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  for (uint8_t t = 2; t > 0; t--)
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  // Khởi động cảm biến DHT11
  dht.begin();
  // Lấy ObjectId của DHT11 sensor
  getDHT11ObjectId("dht11_1");
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= readInterval)
  {
    // Lưu lại thời gian lần cuối
    previousMillis = currentMillis;

    Serial.println("---------------");
    // Gửi dữ liệu cảm biến DHT11
    Serial.println("Sending latest DHT11 readings");
    DHT11Readings readings = readDHT11();
    
    // Kiểm tra nếu việc đọc dữ liệu thất bại
    if (isnan(readings.humidity) || isnan(readings.temperature))
    {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    
    Serial.print("Temperature :: ");
    Serial.println(readings.temperature);
    Serial.print("Humidity :: ");
    Serial.println(readings.humidity);
    
    // Gửi dữ liệu lên server
    sendDHT11Readings(dhtObjectId, readings);
  }
}
