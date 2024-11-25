#include <HardwareSerial.h>

#define simSerial               Serial2
#define MCU_SIM_BAUDRATE        115200
#define MCU_SIM_TX_PIN          17
#define MCU_SIM_RX_PIN          16

void test_send_cmd() 
{
    Serial.println("Sending command: AT+QMTCFG=?");
    simSerial.println("AT+QMTCFG=?");
    waitForResponse();
}

void connect_mqtt() {
    Serial.println("Sending command: AT+QMTCLOSE=0");
    simSerial.println("AT+QMTCLOSE=0");
    waitForResponse();

    Serial.println("Sending command: AT+QMTCFG=\"version\",0,4");
    simSerial.println("AT+QMTCFG=\"version\",0,4");
    waitForResponse();

    // Lệnh mở kết nối MQTT
    Serial.println("Sending command: AT+QMTOPEN=0,\"mqtt.fuvitech.vn\",1883");
    simSerial.println("AT+QMTOPEN=0,\"mqtt.fuvitech.vn\",1883");
    waitForResponse();

    // Lệnh kết nối MQTT client
    Serial.println("Sending command: AT+QMTCONN=0,\"uniqueClientID\"");
    simSerial.println("AT+QMTCONN=0,\"uniqueClientID\"");
    waitForResponse();

    // Lệnh đăng ký topic
    Serial.println("Sending command: AT+QMTSUB=0,123,\Anhchamchi\,1");
    simSerial.println("AT+QMTSUB=0,1,\"Anhchamchi\",1");
    waitForResponse();
}

void publish_mqtt() {
    // Gửi lệnh publish MQTT
    // Serial.println("Sending command: AT+QMTPUBEX=0,0,0,0,\Anhsiengnang\,5");
    simSerial.println("AT+QMTPUBEX=0,0,0,0,\"Anhsiengnang\",5");

    // Chờ phản hồi từ module
    unsigned long start_time = millis();
    String response = "";
    unsigned long timeout = 10000; // Thời gian chờ 10 giây

    while (millis() - start_time < timeout) {
        if (simSerial.available()) {
            char c = simSerial.read();
            response += c;
            Serial.write(c); // In từng ký tự phản hồi để debug

            // Kiểm tra nếu nhận được ký tự '>'
            if (c == '>') {
                Serial.println("\nReceived '>', sending message: hello");
                simSerial.println("hello"); // Gửi tin nhắn "hello"
                break; // Thoát khỏi vòng lặp sau khi gửi tin nhắn
            }
        }
    }

    // Serial.println("\nResponse from module:");
    // Serial.println(response); // In toàn bộ phản hồi
}


void waitForResponse() {
    unsigned long start_time = millis();
    String response = "";
    unsigned long timeout = 3000; // Thời gian chờ 10 giây

    while (millis() - start_time < timeout) {
        if (simSerial.available()) {
            char c = simSerial.read();
            response += c;
            Serial.write(c); // In từng ký tự phản hồi để debug
        }
    }

    Serial.println("\nResponse from module:");
    Serial.println(response); // In toàn bộ phản hồi
}

void setup() 
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("System started!");
    simSerial.begin(MCU_SIM_BAUDRATE, SERIAL_8N1, MCU_SIM_RX_PIN, MCU_SIM_TX_PIN);
    delay(1000);

    test_send_cmd();
    connect_mqtt();
    publish_mqtt();
}

void loop() {

}
