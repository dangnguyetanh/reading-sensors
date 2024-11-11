// Khai báo các biến và hằng số
volatile int pulseCount = 0;     // Biến đếm xung
float flowRate = 0.0;            // Lưu tốc độ dòng chảy (lít/phút)
float totalLitres = 0.0;         // Tổng lượng nước chảy (lít)
unsigned long previousMillis = 0; // Thời gian trước
const int interval = 1000;       // Chu kỳ đo lường (1 giây)
const int sensorPin = 14;        // Chân tín hiệu nối với GPIO14 trên ESP32

// Hằng số để tính toán lưu lượng
const float calibrationFactor = 4.5; // Hệ số hiệu chỉnh cho cảm biến YF-S201

// Thiết lập ngắt và cài đặt cảm biến
void IRAM_ATTR pulseCounter() {
  pulseCount++; // Tăng biến đếm mỗi khi nhận được xung
}

void setup() {
  Serial.begin(115200);            // Khởi động Serial Monitor
  pinMode(sensorPin, INPUT_PULLUP); // Cài đặt chân tín hiệu làm đầu vào với pull-up nội bộ

  // Gắn hàm ngắt cho cảm biến lưu lượng nước
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING); 
}

void loop() {
  unsigned long currentMillis = millis();  // Lấy thời gian hiện tại

  // Cập nhật mỗi giây
  if (currentMillis - previousMillis >= interval) {
    // Kiểm tra xem có đếm được xung hay không
    if (pulseCount > 0) {
      // Tính toán lưu lượng nước
      flowRate = ((1000.0 / (currentMillis - previousMillis)) * pulseCount) / calibrationFactor;
      
      // Tính tổng số lít nước
      totalLitres += (flowRate / 60.0);
      
      // In dữ liệu ra Serial Monitor
      Serial.print("Flow rate: ");
      Serial.print(flowRate);
      Serial.print(" L/min, Total: ");
      Serial.print(totalLitres);
      Serial.println(" L");
    } else {
      // Nếu không có xung, in thông báo không có dòng chảy
      Serial.println("No flow detected");
    }

    // Đặt lại biến đếm xung và thời gian
    pulseCount = 0;
    previousMillis = currentMillis;
  }
}
