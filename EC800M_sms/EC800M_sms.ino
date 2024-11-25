#include <HardwareSerial.h>

#define simSerial Serial2
#define MCU_SIM_BAUDRATE 115200
#define MCU_SIM_TX_PIN 17
#define MCU_SIM_RX_PIN 16
#define PHONE_NUMBER "+84903788860"

void sim_at_wait() {
  delay(100);
  while (simSerial.available()) {
    Serial.write(simSerial.read());
  }
}

bool sim_at_cmd(String cmd) {
  simSerial.println(cmd);
  sim_at_wait();
  return true;
}

bool sim_at_send(char c) {
  simSerial.write(c);
  return true;
}

void sms() {
  Serial.println("Sending command: AT+CMGF=1");
  sim_at_cmd("AT+CMGF=1");
  String temp = "AT+CMGS=\"";
  temp += (String)PHONE_NUMBER;
  temp += "\"";
  sim_at_cmd(temp);
  sim_at_cmd("TEst SMS from ESP32");

  sim_at_send(0x1A);
}

void setup() {

  delay(20);
  Serial.begin(115200);
  Serial.println("\n\n\n\n-----------------------\nSystem started!!!!");
  simSerial.begin(MCU_SIM_BAUDRATE, SERIAL_8N1, MCU_SIM_RX_PIN, MCU_SIM_TX_PIN);
  sim_at_cmd("AT+CFUN=1,1");
  sms();
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    simSerial.write(c);
  }
  sim_at_wait();
}