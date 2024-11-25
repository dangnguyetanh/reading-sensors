#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "Nguyet Anh";
const char *password = "khoa5470";
String google_script_id = "AKfycbyt8fp4iUxLnfqHa2sTg3QBEd3Hww9aenPUgf0aMAPw0Pw48BQ_7rdrHwydct9Tpl1y4A";

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("CONNECTED !!!");
}

void loop() {
    int value1 = random(1, 100);
    int value2 = random(101, 200);
    
    Serial.print("Value1: ");
    Serial.print(value1);
    Serial.print("\tValue2: ");
    Serial.println(value2);

    // Tạo chuỗi URL với cả hai giá trị
    String url = String("https://script.google.com/macros/s/") + google_script_id + "/exec?value1=" + String(value1) + "&value2=" + String(value2);

    // Gửi dữ liệu lên Google Sheets
    write_to_google_sheet(url);

    delay(5000); // Gửi dữ liệu cứ sau 5 giây để giảm tải
}

void write_to_google_sheet(String url) {
    HTTPClient http;
    http.begin(url); // Mở URL
    Serial.println(url);
    int httpCode = http.GET(); // Gửi yêu cầu GET
    
    if (httpCode > 0) {
        String payload = http.getString(); // Nhận phản hồi
        Serial.println("Payload: " + payload);
    } else {
        Serial.print("Error on HTTP request: ");
        Serial.println(httpCode); // In lỗi nếu có
    }

    http.end(); // Kết thúc kết nối HTTP
}