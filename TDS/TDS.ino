#define TdsSensorPin A0
#define VREF 5.0              // Điện áp tham chiếu ADC (Volt)
#define SCOUNT 30             // Số điểm mẫu

int analogBuffer[SCOUNT];     // Mảng lưu giá trị analog
int analogBufferTemp[SCOUNT]; // Mảng tạm cho bộ lọc trung vị
int analogBufferIndex = 0;

float averageVoltage = 0;
float tdsValue = 0;
float temperature = 40;       // Nhiệt độ hiện tại cho bù nhiệt

// Hàm lọc trung vị để ổn định dữ liệu
int getMedianNum(int bArray[], int iFilterLen) {
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++) {
    bTab[i] = bArray[i];
  }

  for (int j = 0; j < iFilterLen - 1; j++) {
    for (int i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        int bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }

  if (iFilterLen % 2 == 1) {
    return bTab[(iFilterLen - 1) / 2];
  } else {
    return (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  }
}

// Hàm đọc và in giá trị TDS
void readTDS() {
  static unsigned long analogSampleTimepoint = millis();
  if (millis() - analogSampleTimepoint > 40U) {  // Mỗi 40ms đọc 1 lần
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);  // Đọc và lưu vào buffer
    analogBufferIndex = (analogBufferIndex + 1) % SCOUNT;  // Vòng tròn chỉ số buffer
  }

  static unsigned long printTimepoint = millis();
  if (millis() - printTimepoint > 800U) {  // In ra mỗi 800ms
    printTimepoint = millis();

    // Sao chép giá trị sang mảng tạm và lọc trung vị
    for (int i = 0; i < SCOUNT; i++) {
      analogBufferTemp[i] = analogBuffer[i];
    }

    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * VREF / 1024.0;

    // Bù nhiệt độ
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
    float compensationVoltage = averageVoltage / compensationCoefficient;

    // Chuyển đổi sang giá trị TDS (ppm)
    tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage
                - 255.86 * compensationVoltage * compensationVoltage
                + 857.39 * compensationVoltage) * 0.5;

    // In ra Serial Monitor
    Serial.print("TDS Value: ");
    Serial.print(tdsValue, 0);
    Serial.println(" ppm");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(TdsSensorPin, INPUT);
}

void loop() {
  readTDS();
}
