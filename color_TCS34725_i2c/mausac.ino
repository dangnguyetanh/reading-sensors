#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Khởi tạo cảm biến với tích hợp thời gian và gain mặc định
Adafruit_TCS34725 tcs = Adafruit_TCS34725();

void setup() {
  Serial.begin(9600);
  if (tcs.begin()) {
    Serial.println("TCS34725 được tìm thấy!");
  } else {
    Serial.println("Không tìm thấy TCS34725, vui lòng kiểm tra kết nối.");
    while (1); // Dừng chương trình nếu không tìm thấy cảm biến
  }

  // Tắt đèn LED tích hợp (nếu có)
  tcs.setInterrupt(true);
}

void loop() {
  uint16_t r, g, b, c;
  float red, green, blue;

  // Đọc giá trị màu sắc
  tcs.getRawData(&r, &g, &b, &c);

  // Tính toán giá trị RGB
  red = (float)r / (float)c * 255.0;
  green = (float)g / (float)c * 255.0;
  blue = (float)b / (float)c * 255.0;

  // Hiển thị giá trị RGB
  Serial.print("R: "); Serial.print((int)red);
  Serial.print(" G: "); Serial.print((int)green);
  Serial.print(" B: "); Serial.println((int)blue);

  // Nhận diện màu dựa trên giá trị RGB
  detectColor(red, green, blue);

  delay(1000); // Chờ 1 giây trước khi đọc lại
}

void detectColor(float red, float green, float blue) {
  if (red > 100 && green < 100 && blue < 30) {
    Serial.println("Màu: Vàng");
  } else if (red < 100 && green > 100 && blue < 100) {
    Serial.println("Màu: Xanh lá");
  } else if (red < 100 && green < 100 && blue > 100) {
    Serial.println("Màu: Xanh dương");
  } else {
    Serial.println("Màu không xác định");
  }
}
