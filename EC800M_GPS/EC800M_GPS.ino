#include <HardwareSerial.h>

#define SIM               Serial2
#define MCU_SIM_BAUDRATE        115200
#define MCU_SIM_TX_PIN          17
#define MCU_SIM_RX_PIN          16

void require_GPS()
{
  // Serial.println("Sending command: AT+QGPS=0"); 
  SIM.println("AT+QGPS=0"); // Turn on GPS in Stand-alone mode
  waitForResponse();

  // Serial.println("Sending command: AT+QGPS=1"); 
  SIM.println("AT+QGPS=1"); // Turn on GPS in Stand-alone mode
  waitForResponse();


}

void get_location()
{
  // Serial.println("Sending command: AT+QGPSLOC=2"); 
  SIM.println("AT+QGPSLOC=2"); // Request GPS location data
  waitForResponse();
}

void waitForResponse()
{
  unsigned long start_time = millis();
  String response = "";
  unsigned long timeout = 3000; // Timeout set to 3 seconds

  while(millis() - start_time <= timeout)
  {
    if(SIM.available())
    {
      char c = SIM.read();
      response += c;
      Serial.write(c); // Print each character to Serial Monitor for debugging
    }
  }
  
  // Serial.println("\nFull response from module:");
  // Serial.println(response); // Print full response for debugging
}

void setup()
{
  Serial.begin(115200); // Initialize Serial Monitor for debugging
  delay(1000); // Delay to establish Serial Monitor connection
  Serial.println("System started!");

  SIM.begin(MCU_SIM_BAUDRATE, SERIAL_8N1, MCU_SIM_RX_PIN, MCU_SIM_TX_PIN);
  delay(3000); // Wait for SIM module to initialize
  require_GPS(); // Call function to request GPS data
}

void loop()
{
  get_location();
  delay(10000);
}
