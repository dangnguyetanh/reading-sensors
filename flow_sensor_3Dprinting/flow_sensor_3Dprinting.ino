#define RAIN_PIN A0 

volatile int rainCount = 0; 
void setup() {
  Serial.begin(9600);
  pinMode(RAIN_PIN, INPUT_PULLUP);  // Chân tín hiệu đầu vào với Pull-up
}

void loop() 
{
  if (digitalRead(RAIN_PIN) == LOW) 
  {
    while(digitalRead(RAIN_PIN) == LOW)  {}
    rainCount++;  
    Serial.print("Tipping count: ");
    Serial.println(rainCount);
  }

  float rainfall = rainCount * 0.25; 
  Serial.print("Lượng mưa: ");
  Serial.print(rainfall);
  Serial.println(" mm");
}
