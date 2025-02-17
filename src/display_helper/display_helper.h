#pragma once

#include <U8g2lib.h>

#define MAX_TEXT_ELEMENTS 10
class DisplayHelper {
	public:
		enum FontEnum {
			FONT_6x10 = 0,
			FONT_10x20 = 1,
			FONT_6x10_MF = 2,
			FONT_10x20_MR = 3,
			MAX_FONTS
		};

		DisplayHelper();
		void Draw();


		bool ShowAllSymbols = false;
		bool ShowWatingForInputSignal = false;
		bool ShowWifiSymbol = false;
		bool ShowConnectedSymbol = false;
		bool ShowErrorSymbol = false;

		void ClearTextElements();
		void AddTextElement(int x, int y, FontEnum fontIndex, const char* format, ...);
		void SetTextElement(int index, int x, int y, FontEnum fontIndex, const char* format, ...);
				
	private:
		U8G2_SSD1306_128X64_NONAME_F_HW_I2C _u8g2;

		enum DisplayElementEnum {
			DISPLAY_ERROR = 0,
			DISPLAY_WAITING = 1,
			DISPLAY_WIFI = 2,
			DISPLAY_CONNECTED = 3,	
			MAX_DISPLAY_ELEMENTS
		};

		struct IconSettings {
			int x = 0;
			int y = 16;
			String text = "";
			const uint8_t* fontData = nullptr;
            // Default constructor
            IconSettings() = default;
			IconSettings(int x, int y, String text, const uint8_t* fontData)
			: x(x), y(y), text(text), fontData(fontData) {}
		};

		IconSettings iconSettingsArray[MAX_DISPLAY_ELEMENTS];

		struct TextSettings {
			int x = 0;
			int y = 0;
			String Text = "";
			FontEnum FontIndex = FONT_6x10;
			// Default constructor
			TextSettings() = default;
			TextSettings(int x, int y, String text, FontEnum fontIndex) : x(x), y(y), Text(text), FontIndex(fontIndex) {}
		};
		TextSettings textSettingsArray[MAX_TEXT_ELEMENTS];

		const uint8_t* fonts[MAX_FONTS] = {u8g2_font_6x10_tf, u8g2_font_10x20_tf, u8g2_font_6x10_mf, u8g2_font_10x20_mr};

		void _DrawIcon(DisplayElementEnum element);
		void _DrawStatus();
		void _DrawText();
};



extern DisplayHelper displayHelper;
