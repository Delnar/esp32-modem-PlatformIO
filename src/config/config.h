#pragma once
#include <arduino.h>
#include <config\config_defines.h>

enum flowControl_t
{
	F_NONE,
	F_HARDWARE,
	F_SOFTWARE
};
enum pinPolarity_t
{
	P_INVERTED,
	P_NORMAL
}; 

extern String build;

class ConfigSettings {
	public:
		String Ssid, Password, BusyMsg;
		int Serialspeed = 8;
		bool Echo = true;
		bool AutoAnswer = false;
		int TcpServerPort = LISTEN_PORT;
		bool Telnet = false; // Is telnet control code handling enabled
		bool VerboseResults = false;
		bool PetTranslate = false; // Fix PET MCTerm 1.26C Pet->ASCII encoding to actual ASCII
		byte FlowControl = F_NONE; // Use flow control

		byte PinPolarity = P_INVERTED;
		String SpeedDials[10];

		unsigned long ConnectTime = 0;
		bool CallConnected = false; // Are we currently in a call

		ConfigSettings();

		void WriteSettings();
		void ReadSettings();
		void DefaultEEPROM();
		void DisplayCurrentSettings();
		void DisplayStoredSettings();		
		void SetupEEPROM();

	private:
		String _GetEEPROM(int startAddress, int len);
		void   _SetEEPROM(String inString, int startAddress, int maxLen);
};

extern ConfigSettings settings;

