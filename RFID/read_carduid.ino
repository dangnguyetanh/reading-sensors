#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 8
#define SS_PIN 53

int UID[4], i;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Khởi tạo đối tượng RFID

void setup() 
{
    Serial.begin(9600);   
    SPI.begin();    
    mfrc522.PCD_Init();  // Khởi tạo RC522
}

void loop() 
{
    // Kiểm tra nếu có thẻ mới được đưa vào
    if (!mfrc522.PICC_IsNewCardPresent()) { 
        return; 
    }
  
    // Kiểm tra nếu có thể đọc thẻ
    if (!mfrc522.PICC_ReadCardSerial()) {  
        return;  
    }
  
    // In UID của thẻ ra Serial Monitor
    Serial.print("UID của thẻ: ");
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
        Serial.print("0x");
        Serial.print(mfrc522.uid.uidByte[i], HEX);  // In ra dạng hex với tiền tố 0x
        if (i < mfrc522.uid.size - 1) 
        {
            Serial.print(" ");  // Thêm khoảng trắng giữa các byte
        }
    }
    
    Serial.println();  // Xuống dòng sau khi in xong UID

    // Dừng giao tiếp với thẻ hiện tại
    mfrc522.PICC_HaltA();  
    mfrc522.PCD_StopCrypto1();
}
