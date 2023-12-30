

#ifdef ENABLE_DEBUG
   #define DEBUG_ESP_PORT Serial
   #define NODEBUG_WEBSOCKETS
   #define NDEBUG
#endif 

#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
#elif defined(ESP32) || defined(ARDUINO_ARCH_RP2040)
  #include <WiFi.h>
#endif

#include "SinricPro.h"
#include "SinricProSwitch.h"
#include<Servo.h>

#define WIFI_SSID         "vivo 1917"
#define WIFI_PASS         "1234567890"
#define APP_KEY           "de5f1717-bff3-4806-ba2e-260f85ce5f48"
#define APP_SECRET        "02c65f6f-7c63-441d-a708-77a1867f32ae-89a14eff-00a7-4dc8-8650-a6ed385dff6a"

#define SWITCH_ID_1       "657fbd0b0c9e5d526c75040c"
//#define RELAYPIN_1        5

#define BAUD_RATE         115200                // Change baudrate to your need

Servo myServo;  // Create a servo object

int servoPin = 14;  // Define the pin connected to the servo

/*bool onPowerState1(const String &deviceId, bool &state) {
 Serial.printf("Device 1 turned %s", state?"on":"off");
// digitalWrite( myServo, state ? HIGH:LOW);
  myServo.write(state ? HIGH:LOW); 
 return true; // request handled properly
}
*/
bool onPowerState1(const String &deviceId, bool &state) {
  Serial.printf("Device 1 turned %s\n", state ? "on" : "off");
  int angle = state ? 180 : 0;  // Assuming 180 is the maximum angle and 0 is the minimum
  myServo.write(angle); 
  delay(1000);
   myServo.write(0);
  return true; // request handled properly
}


// setup function for WiFi connection
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");

  #if defined(ESP8266)
    WiFi.setSleepMode(WIFI_NONE_SLEEP); 
    WiFi.setAutoReconnect(true);
  #elif defined(ESP32)
    WiFi.setSleep(false); 
    WiFi.setAutoReconnect(true);
  #endif

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }

  Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}

// setup function for SinricPro
void setupSinricPro() {
  // add devices and callbacks to SinricPro
 // pinMode(RELAYPIN_1, OUTPUT);
     myServo.attach(servoPin); 
  SinricProSwitch& mySwitch1 = SinricPro[SWITCH_ID_1];
  mySwitch1.onPowerState(onPowerState1);
  
  
  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
   
  SinricPro.begin(APP_KEY, APP_SECRET);
}

// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
  
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}
