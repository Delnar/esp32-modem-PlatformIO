// https://github.com/olikraus/u8g2/
  // Each Symbol is 8x8 pixels
  // Waiting is 0,0
  // Error is 0,0    -- Replaces Waiting as they are mutually exclusive
  // Wifi is 8,0
  // Connected is 16,0

  // https://github.com/olikraus/u8g2/wiki/fntgrpiconic
  // https://github.com/olikraus/u8g2/wiki/fntlist8

  // u8g2_font_open_iconic_www_1x_t   contains the Wifi Symbol      (R) (https://raw.githubusercontent.com/wiki/olikraus/u8g2/fntpic/u8g2_font_open_iconic_www_1x_t.png)
  // u8g2_font_open_iconic_www_1x_t   contains the Connected Symbol (T) (https://raw.githubusercontent.com/wiki/olikraus/u8g2/fntpic/u8g2_font_open_iconic_www_1x_t.png)
  // u8g2_font_open_iconic_check_1x_t contains the error Symbol (E) (https://raw.githubusercontent.com/wiki/olikraus/u8g2/fntpic/u8x8_font_open_iconic_check_1x1.png)
  // u8g2_font_open_iconic_check_1x_t contains the Waiting Symbol (D) (https://raw.githubusercontent.com/wiki/olikraus/u8g2/fntpic/u8x8_font_open_iconic_check_1x1.png)

  // X, Y, Font, and Text

#include <Arduino.h>
#include <U8g2lib.h>
#include <config.h>

#include "display_helper.h"


// Text is 8 pixels tal

DisplayHelper::DisplayHelper() : _u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE) 
{ 
  iconSettingsArray[DISPLAY_ERROR]     = IconSettings { 0,   12, "D", u8g2_font_open_iconic_check_1x_t };
  iconSettingsArray[DISPLAY_WAITING]   = IconSettings { 0,   12, "E", u8g2_font_open_iconic_check_1x_t };
  iconSettingsArray[DISPLAY_WIFI]      = IconSettings { 12,  12, "Q", u8g2_font_open_iconic_www_1x_t   };
  iconSettingsArray[DISPLAY_CONNECTED] = IconSettings { 24,  12, "S", u8g2_font_open_iconic_www_1x_t   };

}

void DisplayHelper::_DrawStatus() {

  if (ShowAllSymbols) {
    _DrawIcon(DISPLAY_ERROR);
    _DrawIcon(DISPLAY_WIFI);
    _DrawIcon(DISPLAY_CONNECTED);
    return;
  } 

  if (ShowErrorSymbol) {
    _DrawIcon(DISPLAY_ERROR);
  } else if (ShowWatingForInputSignal) {
    _DrawIcon(DISPLAY_WAITING);
  } 

  if (ShowWifiSymbol) {
    _DrawIcon(DISPLAY_WIFI);
  }
  if (ShowConnectedSymbol) {
    _DrawIcon(DISPLAY_CONNECTED);
  }
}

void DisplayHelper::_DrawIcon(DisplayElementEnum displayElement) {
  if (displayElement < 0) return;
  if (displayElement >= MAX_DISPLAY_ELEMENTS) return;

  _u8g2.setFont(iconSettingsArray[displayElement].fontData);
  _u8g2.setCursor(iconSettingsArray[displayElement].x, iconSettingsArray[displayElement].y);
  _u8g2.print(iconSettingsArray[displayElement].text);
}

void DisplayHelper::ClearTextElements() {
  for (int i = 0; i < MAX_TEXT_ELEMENTS; i++) {
    textSettingsArray[i] = TextSettings();
  }
}

void DisplayHelper::AddTextElement(int x, int y, FontEnum fontIndex, const char* format, ...) {
  char buffer[128];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  for (int i = 0; i < MAX_TEXT_ELEMENTS; i++) {
      if (textSettingsArray[i].Text == "") {
          textSettingsArray[i] = TextSettings(x, y, String(buffer), fontIndex);
          return;
      }
  }
}

void DisplayHelper::SetTextElement(int index, int x, int y, FontEnum fontIndex, const char* format, ...) {
  if (index < 0) return;
  if (index >= MAX_TEXT_ELEMENTS) return;

  char buffer[128];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);  

  textSettingsArray[index] = TextSettings(x, y, String(buffer), fontIndex);
}


void DisplayHelper::_DrawText() {
  for (int i = 0; i < MAX_TEXT_ELEMENTS; i++) {
    if (textSettingsArray[i].Text != "") {
      _u8g2.setFont(fonts[textSettingsArray[i].FontIndex]);
      _u8g2.setCursor(textSettingsArray[i].x, textSettingsArray[i].y);
      _u8g2.print(textSettingsArray[i].Text);
    }
  }
}

void DisplayHelper::Draw() {
  _u8g2.begin();
  _u8g2.clearBuffer();
  _DrawStatus();
  _DrawText();
  _u8g2.sendBuffer();
}

// Update Wifi display
//   void updateLed() {
// 	if (WiFi.status() == WL_CONNECTED) {
// 	  digitalWrite(LED_PIN, LOW);  // on
// 	} else {
// 	  digitalWrite(LED_PIN, HIGH); //off
// 	}
//   }
  
DisplayHelper displayHelper;
