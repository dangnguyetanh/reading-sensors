#include <SPI.h>
#include <MFRC522.h>

// Khai báo chân kết nối cho SDA và RST
#define SS_PIN 53
#define RST_PIN 8

MFRC522 rfid(SS_PIN, RST_PIN);  // Khởi tạo đối tượng RFID

// Danh sách mã thẻ tương ứng với các màu
byte redCard[] = {0x93, 0x2C, 0x8E, 0xFA};    // Mã thẻ màu đỏ
byte blueCard[] = {0xB9, 0xFB, 0xB1, 0xA3};   // Mã thẻ màu xanh dương
byte greenCard[] = {0x01, 0x35, 0x51, 0x1C};  // Mã thẻ màu xanh lá

void setup() {
  // Khởi tạo giao tiếp serial để theo dõi dữ liệu
  Serial.begin(9600);

  // Khởi tạo SPI bus
  SPI.begin();

  // Khởi tạo RC522
  rfid.PCD_Init();
  Serial.println("Vui lòng quét thẻ RFID...");
}

void loop() {
  // Kiểm tra nếu có thẻ gần module
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Kiểm tra nếu có thể đọc thẻ
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // In UID của thẻ ra màn hình Serial với tiền tố 0x
  Serial.print("UID của thẻ: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print("0x");  // Thêm tiền tố 0x
    Serial.print(rfid.uid.uidByte[i], HEX);  // In ra dạng hex
    if (i < rfid.uid.size - 1) {
      Serial.print(" ");  // Thêm khoảng trắng giữa các byte
    }
  }
  Serial.println();  // Xuống dòng sau khi in xong UID

  // Kiểm tra nếu mã thẻ là màu đỏ
  if (compareUID(rfid.uid.uidByte, redCard)) {
    Serial.println("Thẻ màu đỏ đã được nhận diện!");
    // Thực hiện hành động cho màu đỏ
  }
  // Kiểm tra nếu mã thẻ là màu xanh dương
  else if (compareUID(rfid.uid.uidByte, blueCard)) {
    Serial.println("Thẻ màu xanh dương đã được nhận diện!");
    // Thực hiện hành động cho màu xanh dương
  }
  // Kiểm tra nếu mã thẻ là màu xanh lá
  else if (compareUID(rfid.uid.uidByte, greenCard)) {
    Serial.println("Thẻ màu xanh lá đã được nhận diện!");
    // Thực hiện hành động cho màu xanh lá
  } else {
    Serial.println("Thẻ không hợp lệ!");
  }

  // Dừng giao tiếp với thẻ hiện tại
  rfid.PICC_HaltA();
}

// Hàm so sánh mã UID của thẻ
bool compareUID(byte *uid, byte *validCard) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != validCard[i]) {
      return false;
    }
  }
  return true;
}
