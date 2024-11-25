#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 mpu;

#define INTERRUPT_PIN 2      // Pin ngắt của MPU6050
#define FALL_THRESHOLD 45.0  // Ngưỡng phát hiện té ngã (thay đổi theo yêu cầu)

bool DMPReady = false;
uint16_t packetSize;
uint8_t FIFOBuffer[64];

Quaternion q;
VectorFloat gravity;
float ypr[3];

// Biến lưu giá trị góc tham chiếu ban đầu
float initialPitch = 0, initialRoll = 0, initialYaw = 0;
bool initialSet = false;  // Biến kiểm tra nếu góc ban đầu đã được thiết lập

volatile bool MPUInterrupt = false;
void DMPDataReady() {
  MPUInterrupt = true;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  Serial.println("Initializing MPU6050...");
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1)
      ;
  } else {
    Serial.println("MPU6050 connection successful");
  }

  Serial.println("Initializing DMP...");
  uint8_t devStatus = mpu.dmpInitialize();

  if (devStatus == 0) {
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    Serial.println("DMP ready! Waiting for first interrupt...");
    mpu.setDMPEnabled(true);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), DMPDataReady, RISING);
    packetSize = mpu.dmpGetFIFOPacketSize();
    DMPReady = true;
  } else {
    Serial.print("DMP Initialization failed (code ");
    Serial.print(devStatus);
    Serial.println(")");
  }
}

void loop() {
  if (!DMPReady) return;

  if (mpu.dmpGetCurrentFIFOPacket(FIFOBuffer)) {
    mpu.dmpGetQuaternion(&q, FIFOBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    if (!initialSet) {
      initialYaw = ypr[0];
      initialPitch = ypr[1];
      initialRoll = ypr[2];
      initialSet = true;

      Serial.println("Initial angles set:");
      Serial.print("Initial Pitch: ");
      Serial.print(initialPitch * 180 / M_PI);
      Serial.print("°\tInitial Roll: ");
      Serial.print(initialRoll * 180 / M_PI);
      Serial.print("°\tInitial Yaw: ");
      Serial.println(initialYaw * 180 / M_PI);
    }

    // Tính góc lệch so với góc ban đầu cố định
    float pitchOffset = abs((ypr[1] - initialPitch) * 180 / M_PI);
    float rollOffset = abs((ypr[2] - initialRoll) * 180 / M_PI);
    float yawOffset = abs((ypr[0] - initialYaw) * 180 / M_PI);

    // Tính góc tổng hợp (2D)
    float totalAngle = sqrt(pitchOffset * pitchOffset + rollOffset * rollOffset);

    // Tính góc tổng hợp (2D)
    float totalAngle3D = sqrt(pitchOffset * pitchOffset + rollOffset * rollOffset + yawOffset * yawOffset);

    Serial.print("Pitch Offset: ");
    Serial.print(pitchOffset);
    Serial.print("°\tRoll Offset: ");
    Serial.print(rollOffset);
    Serial.print("°\tYaw Offset: ");
    Serial.print(yawOffset);
    Serial.print("°\tTotal Angle: ");
    Serial.print(totalAngle);
    Serial.println("°");
    Serial.print("Total Angle 3D: ");
    Serial.print(totalAngle3D);
    Serial.println("°");
  }
  delay(300);
}
