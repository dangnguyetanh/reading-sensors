#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;
const float g = 9.8;
const float scaleFactor = 16384.0;  // Tỷ lệ chuyển đổi từ giá trị thô sang g trong ±2g mode

void setup() {
    Serial.begin(115200);
    while (!Serial);
    Wire.begin();
    Serial.println("Initializing MPU6050...");
    mpu.initialize();

    if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed");
        while (1);
    } else {
        Serial.println("MPU6050 connection successful");
    }

    Serial.println("Calibrating MPU6050...");
    
    // Cân chỉnh offset cho MPU6050
    mpu.CalibrateAccel(6);  // Hiệu chỉnh gia tốc
    mpu.CalibrateGyro(6);   // Hiệu chỉnh con quay

    // In ra giá trị offset sau khi cân chỉnh
    Serial.println("Cân chỉnh hoàn tất. Đây là các giá trị offset:");
    mpu.PrintActiveOffsets();
}

void loop() {
    // Đọc dữ liệu gia tốc để kiểm tra
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);
    
    // Chuyển đổi từ giá trị thô của cảm biến sang đơn vị m/s²
    float ax_m_s2 = (ax / scaleFactor) * g;
    float ay_m_s2 = (ay / scaleFactor) * g;
    float az_m_s2 = (az / scaleFactor) * g;

    // Tính gia tốc tổng hợp
    float total_acceleration = sqrt(pow(ax_m_s2, 2) + pow(ay_m_s2, 2) + pow(az_m_s2, 2));

    Serial.print("Total acceleration: ");
    Serial.println(total_acceleration);
    delay(500);
}
