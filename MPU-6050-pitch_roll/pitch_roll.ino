#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Khởi tạo MPU-6050
  Serial.println("Initializing MPU6050...");
  mpu.initialize();
  
  // Kiểm tra kết nối
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully!");
  } else {
    Serial.println("MPU6050 connection failed!");
    while (1); // Dừng chương trình nếu không kết nối được
  }
}

void loop() {
  // Đọc dữ liệu gia tốc và con quay hồi chuyển
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Chuyển đổi dữ liệu thô sang giá trị gia tốc và tốc độ góc
  float accelX = ax / 16384.0; // Đơn vị là g (1g = 9.8m/s²)
  float accelY = ay / 16384.0;
  float accelZ = az / 16384.0;
  
  float gyroX = gx / 131.0;    // Đơn vị là độ/s (dps)
  float gyroY = gy / 131.0;
  float gyroZ = gz / 131.0;
  
  // Tính toán góc nghiêng (Pitch, Roll) từ dữ liệu gia tốc kế
  float pitch = atan2(accelY, sqrt(accelX * accelX + accelZ * accelZ)) * 180.0 / PI;
  float roll = atan2(accelX, sqrt(accelY * accelY + accelZ * accelZ)) * 180.0 / PI;

  // Hiển thị dữ liệu trên Serial Monitor
  // Serial.print("Accel X: "); Serial.print(accelX); Serial.print(" g\t");
  // Serial.print("Accel Y: "); Serial.print(accelY); Serial.print(" g\t");
  // Serial.print("Accel Z: "); Serial.print(accelZ); Serial.print(" g\t");

  // Serial.print("Gyro X: "); Serial.print(gyroX); Serial.print(" °/s\t");
  // Serial.print("Gyro Y: "); Serial.print(gyroY); Serial.print(" °/s\t");
  // Serial.print("Gyro Z: "); Serial.print(gyroZ); Serial.print(" °/s\t");

  Serial.print("Pitch: "); Serial.print(pitch); Serial.print(" °\t");
  Serial.print("Roll: "); Serial.println(roll); Serial.print(" °\t");
  
  delay(500); // Đợi 500ms để đọc dữ liệu lần tiếp theo
}
