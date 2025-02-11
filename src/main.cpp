
// 0 to 16 is yellow
// 17 to 63 is blue
#include <Arduino.h>

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <EEPROM.h>

#include <WiFiClient.h>


#include <Wire.h>
#include <U8g2lib.h>

#include <config_defines.h>
#include <config.h>

#include <serial_helpers.h>
#include <display_helper.h>


String cmd = "";           // Gather a new AT command to this string from serial
bool cmdMode = true;       // Are we in AT command mode or connected mode

unsigned long lastRingMs = 0; // Time of last "RING" message (millis())
char plusCount = 0;        // Go to AT mode at "+++" sequence, that has to be counted
unsigned long plusTime = 0;// When did we last receive a "+++" sequence
unsigned long ledTime = 0;

uint8_t txBuf[TX_BUF_SIZE];

byte ringCount = 0;

bool hex = false;
bool txPaused = false;          // Has flow control asked us to pause?

unsigned long oledTimer = 0;

WebServer webServer(80);
MDNSResponder mdns;




void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // off
  pinMode(SWITCH_PIN, INPUT);
  digitalWrite(SWITCH_PIN, HIGH);
  pinMode(DCD_PIN, OUTPUT);
  pinMode(RTS_PIN, OUTPUT);
  digitalWrite(RTS_PIN, LOW); // ready to receive data
  pinMode(CTS_PIN, INPUT);

  setup_eeprom();
  setup_display();

  // put your setup code here, to run once:
  // Serial.begin(bauds[settings.serialspeed]);


}

void loop() {

}
