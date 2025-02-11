// https://github.com/olikraus/u8g2/

#include <Arduino.h>
#include <U8g2lib.h>
#include <config.h>
#include <serial_helpers.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Text is 8 pixels tal

void setup_display() {
  char txBuf[20];
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.setCursor(0,32);  // is the first line in the blue area
  sprintf(txBuf, "Baud: %d", bauds[settings.serialspeed]);
  u8g2.print(txBuf);
  // u8g2.setCursor(0,32);
  // u8g2.print(bauds[settings.serialspeed]);

  u8g2.setFont(u8g2_font_10x20_mr);
  u8g2.setCursor(10,48);
  u8g2.print("Waiting for");
  u8g2.setCursor(10,64);
  u8g2.print("Input");
  u8g2.setCursor(10,16);
  u8g2.print("!");
  u8g2.sendBuffer();  
}

  // u8g2.begin();
  // u8g2.clearBuffer();
  // u8g2.setDrawColor(1);
  // u8g2.drawBox(0,0,120,63);
  // u8g2.setFont(u8g2_font_6x10_mf);
  // u8g2.setCursor(0,starty);
  // u8g2.print("Baud:");
  // u8g2.sendBuffer();

// Update Wifi display
//   void updateLed() {
// 	if (WiFi.status() == WL_CONNECTED) {
// 	  digitalWrite(LED_PIN, LOW);  // on
// 	} else {
// 	  digitalWrite(LED_PIN, HIGH); //off
// 	}
//   }
  