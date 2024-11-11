#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
//===========================WiFi=========================//
const char* ssid = "Fuvitech_L2";
const char* passwifi = "fuvitech.vn";
WiFiClient espClient;
//===========================Telegram=========================//
#define BOT_TOKEN "7280807656:AAH_r4JbzFHJgA-FGrywOtcrAPim-vqJc2s"
#define CHAT_ID "5137060434"  // Replace with your chat ID
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
void setupWiFi() 
{
  delay(10);
  Serial.println();
  Serial.print("Connecting WiFi to ");
  Serial.print(ssid);
  WiFi.begin(ssid, passwifi);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void setup() {
  Serial.begin(9600);
  setupWiFi();
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  String message = "Fall detection Start";
  bot.sendMessage(CHAT_ID, message, "");
}


void loop() {
  // put your main code here, to run repeatedly:

}
