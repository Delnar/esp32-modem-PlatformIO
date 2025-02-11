#pragma once
#include <arduino.h>
#include <config_defines.h>

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

struct ConfigSettings {
	String ssid, password, busyMsg;
	int serialspeed = 8;
	bool echo = true;
	bool autoAnswer = false;
	int tcpServerPort = LISTEN_PORT;
	bool telnet = false; // Is telnet control code handling enabled
	bool verboseResults = false;
	bool petTranslate = false; // Fix PET MCTerm 1.26C Pet->ASCII encoding to actual ASCII
	byte flowControl = F_NONE; // Use flow control

	byte pinPolarity = P_INVERTED;
	String speedDials[10];

	unsigned long connectTime = 0;
	bool callConnected = false; // Are we currently in a call
};

extern ConfigSettings settings;
extern String build;

void writeSettings();
void readSettings();
void defaultEEPROM();
void displayCurrentSettings();
void setup_eeprom();

String getEEPROM(int startAddress, int len);
void setEEPROM(String inString, int startAddress, int maxLen);