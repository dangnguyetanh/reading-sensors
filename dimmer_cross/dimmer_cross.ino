#define TRIAC_GATE_PIN 27  // Chân điều khiển Triac (thay đổi nếu cần)
#define ZERO_CROSS_PIN 13   // Chân nhận tín hiệu zero-cross

volatile bool zeroCrossDetected = false;  // Biến để theo dõi tín hiệu zero-cross
int alpha = 5400;  // Thời gian trễ để kích hoạt Triac (điều chỉnh tùy theo yêu cầu)

void IRAM_ATTR zeroCrossISR() {
    zeroCrossDetected = true; // Đặt cờ khi phát hiện zero-cross
}

void setup() {
    pinMode(TRIAC_GATE_PIN, OUTPUT);   // Cấu hình chân Triac làm ngõ ra
    pinMode(ZERO_CROSS_PIN, INPUT);     // Cấu hình chân zero-cross làm ngõ vào

    Serial.begin(115200);                // Bắt đầu Serial Monitor

    attachInterrupt(digitalPinToInterrupt(ZERO_CROSS_PIN), zeroCrossISR, RISING); // Gắn hàm ngắt vào chân zero-cross
}

void loop() {
    if (zeroCrossDetected) {
        zeroCrossDetected = false; // Đặt lại cờ

        // Đợi thêm một khoảng thời gian alpha
        delayMicroseconds(alpha);

        // Kích hoạt Triac
        digitalWrite(TRIAC_GATE_PIN, HIGH);
        delayMicroseconds(500); // Giữ Triac HIGH trong 500 microseconds
        digitalWrite(TRIAC_GATE_PIN, LOW); // Tắt Triac

        // In ra giá trị alpha trên Serial Monitor (tùy chọn)
        Serial.print("Alpha: ");
        Serial.println(alpha);
    }
}