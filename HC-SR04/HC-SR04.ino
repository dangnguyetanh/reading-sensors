// Khai báo các chân của cảm biến siêu âm
const int trigPin = A6;
const int echoPin = A7;

void setup() {
  // Khởi tạo serial monitor để kiểm tra dữ liệu
  Serial.begin(9600);
  
  // Đặt chế độ cho các chân
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Đặt chân TRIG ở mức thấp để đảm bảo không có tín hiệu trước khi bắt đầu
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Kích hoạt TRIG để phát ra xung
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Đọc tín hiệu từ chân ECHO (thời gian tín hiệu phản hồi)
  long duration = pulseIn(echoPin, HIGH);

  // Tính toán khoảng cách (tốc độ âm thanh là 343m/s hoặc 0.0343 cm/us)
  float distance = duration * 0.0343 / 2;  // Chia cho 2 vì tín hiệu đi và về

  // In khoảng cách ra serial monitor
  Serial.print("Khoang cach: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Đợi 500ms trước khi đo lại
  delay(500);
}
