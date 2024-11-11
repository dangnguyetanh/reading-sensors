#include <Servo.h>
Servo myServo;  // Tạo đối tượng Servo

int servoPin = A0; // Chân PWM kết nối với servo
int angle = 0; // Góc bắt đầu của servo
int gocxoay = 100;
void setup() {
  // Gắn servo vào chân đã chọn
  myServo.attach(servoPin);

  // Bắt đầu ở vị trí 0 độ
  myServo.write(angle);
  delay(1000); // Chờ 1 giây trước khi bắt đầu di chuyển
}

void xoay()
{
  // Quay servo từ 0 đến 180 độ từ từ
  for (angle = 0; angle <= gocxoay; angle += 1) {
    myServo.write(angle); // Di chuyển servo tới góc hiện tại
    delay(5); // Chờ 15ms giữa mỗi bước (tốc độ di chuyển)
  }
  delay(1000);
  // Quay servo từ 180 về 0 độ từ từ
  for (angle = gocxoay; angle >= 0; angle -= 1) {
    myServo.write(angle); // Di chuyển servo tới góc hiện tại
    delay(5); // Chờ 15ms giữa mỗi bước (tốc độ di chuyển)
  }

  delay(1000); // Chờ 1 giây sau khi hoàn thành mỗi vòng quay 
}

void loop() 
{
  // xoay();
  myServo.write(gocxoay);
}
