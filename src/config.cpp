#include <Arduino.h>
#include <config.h>
#include <EEPROM.h>
#include <serial_helpers.h>


ConfigSettings settings;
String build = "20160621182048";

#define VERSIONA 1
#define VERSIONB 2
#define VERSION_ADDRESS 0 // EEPROM address
#define VERSION_LEN 2	  // Length in bytes

#define SSID_ADDRESS 2
#define SSID_LEN 32
#define PASS_ADDRESS 34
#define PASS_LEN 63
#define BUSY_MSG_ADDRESS 700
#define BUSY_MSG_LEN 80

#define BAUD_ADDRESS 111
#define ECHO_ADDRESS 112
#define SERVER_PORT_ADDRESS 113 // 2 bytes
#define AUTO_ANSWER_ADDRESS 115 // 1 byte
#define TELNET_ADDRESS 116		// 1 byte
#define VERBOSE_ADDRESS 117
#define PET_TRANSLATE_ADDRESS 118
#define FLOW_CONTROL_ADDRESS 119
#define PIN_POLARITY_ADDRESS 120

#define DIAL0_ADDRESS 200
#define DIAL1_ADDRESS 250
#define DIAL2_ADDRESS 300
#define DIAL3_ADDRESS 350
#define DIAL4_ADDRESS 400
#define DIAL5_ADDRESS 450
#define DIAL6_ADDRESS 500
#define DIAL7_ADDRESS 550
#define DIAL8_ADDRESS 600
#define DIAL9_ADDRESS 650

const int speedDialAddresses[] = {
	DIAL0_ADDRESS,
	DIAL1_ADDRESS,
	DIAL2_ADDRESS,
	DIAL3_ADDRESS,
	DIAL4_ADDRESS,
	DIAL5_ADDRESS,
	DIAL6_ADDRESS,
	DIAL7_ADDRESS,
	DIAL8_ADDRESS,
	DIAL9_ADDRESS};

#define LAST_ADDRESS 780

void writeSettings() {
	setEEPROM(settings.ssid, SSID_ADDRESS, SSID_LEN);
	setEEPROM(settings.password, PASS_ADDRESS, PASS_LEN);
	setEEPROM(settings.busyMsg, BUSY_MSG_ADDRESS, BUSY_MSG_LEN);

	EEPROM.write(BAUD_ADDRESS, settings.serialspeed);
	EEPROM.write(ECHO_ADDRESS, byte(settings.echo));
	EEPROM.write(AUTO_ANSWER_ADDRESS, byte(settings.autoAnswer));
	EEPROM.write(SERVER_PORT_ADDRESS, highByte(settings.tcpServerPort));
	EEPROM.write(SERVER_PORT_ADDRESS + 1, lowByte(settings.tcpServerPort));
	EEPROM.write(TELNET_ADDRESS, byte(settings.telnet));
	EEPROM.write(VERBOSE_ADDRESS, byte(settings.verboseResults));
	EEPROM.write(PET_TRANSLATE_ADDRESS, byte(settings.petTranslate));
	EEPROM.write(FLOW_CONTROL_ADDRESS, byte(settings.flowControl));
	EEPROM.write(PIN_POLARITY_ADDRESS, byte(settings.pinPolarity));

	for (int i = 0; i < 10; i++)
	{
		setEEPROM(settings.speedDials[i], speedDialAddresses[i], 50);
	}
	EEPROM.commit();
}

void readSettings() {
	settings.echo = EEPROM.read(ECHO_ADDRESS);
	settings.autoAnswer = EEPROM.read(AUTO_ANSWER_ADDRESS);
	settings.serialspeed = EEPROM.read(BAUD_ADDRESS);

	settings.ssid = getEEPROM(SSID_ADDRESS, SSID_LEN);
	settings.password = getEEPROM(PASS_ADDRESS, PASS_LEN);
	settings.busyMsg = getEEPROM(BUSY_MSG_ADDRESS, BUSY_MSG_LEN);
	settings.tcpServerPort = word(EEPROM.read(SERVER_PORT_ADDRESS), EEPROM.read(SERVER_PORT_ADDRESS + 1));
	settings.telnet = EEPROM.read(TELNET_ADDRESS);
	settings.verboseResults = EEPROM.read(VERBOSE_ADDRESS);
	settings.petTranslate = EEPROM.read(PET_TRANSLATE_ADDRESS);
	settings.flowControl = EEPROM.read(FLOW_CONTROL_ADDRESS);
	settings.pinPolarity = EEPROM.read(PIN_POLARITY_ADDRESS);

	for (int i = 0; i < 10; i++)
	{
		settings.speedDials[i] = getEEPROM(speedDialAddresses[i], 50);
	}

	// Check if it's out of bounds-- we have to be able to talk (specifically serial speed)
	if (settings.serialspeed < 0 || settings.serialspeed > baud_option_count) {
		settings.serialspeed = 0;
	}	
}

void defaultEEPROM()
{
	EEPROM.write(VERSION_ADDRESS, VERSIONA);
	EEPROM.write(VERSION_ADDRESS + 1, VERSIONB);

	setEEPROM("", SSID_ADDRESS, SSID_LEN);
	setEEPROM("", PASS_ADDRESS, PASS_LEN);
	setEEPROM("d", IP_TYPE_ADDRESS, 1);
	EEPROM.write(SERVER_PORT_ADDRESS, highByte(LISTEN_PORT));
	EEPROM.write(SERVER_PORT_ADDRESS + 1, lowByte(LISTEN_PORT));

	EEPROM.write(BAUD_ADDRESS, 0x00);
	EEPROM.write(ECHO_ADDRESS, 0x01);
	EEPROM.write(AUTO_ANSWER_ADDRESS, 0x01);
	EEPROM.write(TELNET_ADDRESS, 0x00);
	EEPROM.write(VERBOSE_ADDRESS, 0x01);
	EEPROM.write(PET_TRANSLATE_ADDRESS, 0x00);
	EEPROM.write(FLOW_CONTROL_ADDRESS, 0x00);
	EEPROM.write(PIN_POLARITY_ADDRESS, 0x01);

	setEEPROM("bbs.fozztexx.com:23", speedDialAddresses[0], 50);
	setEEPROM("cottonwoodbbs.dyndns.org:6502", speedDialAddresses[1], 50);
	setEEPROM("borderlinebbs.dyndns.org:6400", speedDialAddresses[2], 50);
	setEEPROM("particlesbbs.dyndns.org:6400", speedDialAddresses[3], 50);
	setEEPROM("reflections.servebbs.com:23", speedDialAddresses[4], 50);
	setEEPROM("heatwavebbs.com:9640", speedDialAddresses[5], 50);

	for (int i = 5; i < 10; i++)
	{
		setEEPROM("", speedDialAddresses[i], 50);
	}

	setEEPROM("SORRY, SYSTEM IS CURRENTLY BUSY. PLEASE TRY AGAIN LATER.", BUSY_MSG_ADDRESS, BUSY_MSG_LEN);
	EEPROM.commit();
}

void displayCurrentSettings()
{
	Serial.println("ACTIVE PROFILE:");
	yield();
	Serial.print("BAUD: ");
	Serial.println(bauds[settings.serialspeed]);
	yield();
	Serial.print("SSID: ");
	Serial.println(settings.ssid);
	yield();
	Serial.print("PASS: ");
	Serial.println(settings.password);
	yield();
	// Serial.print("SERVER TCP PORT: "); Serial.println(tcpServerPort); yield();
	Serial.print("BUSY MSG: ");
	Serial.println(settings.busyMsg);
	yield();
	Serial.print("E");
	Serial.print(settings.echo);
	Serial.print(" ");
	yield();
	Serial.print("V");
	Serial.print(settings.verboseResults);
	Serial.print(" ");
	yield();
	Serial.print("&K");
	Serial.print(settings.flowControl);
	Serial.print(" ");
	yield();
	Serial.print("&P");
	Serial.print(settings.pinPolarity);
	Serial.print(" ");
	yield();
	Serial.print("NET");
	Serial.print(settings.telnet);
	Serial.print(" ");
	yield();
	Serial.print("PET");
	Serial.print(settings.petTranslate);
	Serial.print(" ");
	yield();
	Serial.print("S0:");
	Serial.print(settings.autoAnswer);
	Serial.print(" ");
	yield();
	Serial.println();
	yield();

	Serial.println("SPEED DIAL:");
	for (int i = 0; i < 10; i++)
	{
		Serial.print(i);
		Serial.print(": ");
		Serial.println(settings.speedDials[i]);
		yield();
	}
	Serial.println();
}

void displayStoredSettings()
{
	Serial.println("STORED PROFILE:");
	yield();
	Serial.print("BAUD: ");
	Serial.println(bauds[EEPROM.read(BAUD_ADDRESS)]);
	yield();
	Serial.print("SSID: ");
	Serial.println(getEEPROM(SSID_ADDRESS, SSID_LEN));
	yield();
	Serial.print("PASS: ");
	Serial.println(getEEPROM(PASS_ADDRESS, PASS_LEN));
	yield();
	// Serial.print("SERVER TCP PORT: "); Serial.println(word(EEPROM.read(SERVER_PORT_ADDRESS), EEPROM.read(SERVER_PORT_ADDRESS+1))); yield();
	Serial.print("BUSY MSG: ");
	Serial.println(getEEPROM(BUSY_MSG_ADDRESS, BUSY_MSG_LEN));
	yield();
	Serial.print("E");
	Serial.print(EEPROM.read(ECHO_ADDRESS));
	Serial.print(" ");
	yield();
	Serial.print("V");
	Serial.print(EEPROM.read(VERBOSE_ADDRESS));
	Serial.print(" ");
	yield();
	Serial.print("&K");
	Serial.print(EEPROM.read(FLOW_CONTROL_ADDRESS));
	Serial.print(" ");
	yield();
	Serial.print("&P");
	Serial.print(EEPROM.read(PIN_POLARITY_ADDRESS));
	Serial.print(" ");
	yield();
	Serial.print("NET");
	Serial.print(EEPROM.read(TELNET_ADDRESS));
	Serial.print(" ");
	yield();
	Serial.print("PET");
	Serial.print(EEPROM.read(PET_TRANSLATE_ADDRESS));
	Serial.print(" ");
	yield();
	Serial.print("S0:");
	Serial.print(EEPROM.read(AUTO_ANSWER_ADDRESS));
	Serial.print(" ");
	yield();
	Serial.println();
	yield();

	Serial.println("STORED SPEED DIAL:");
	for (int i = 0; i < 10; i++)
	{
		Serial.print(i);
		Serial.print(": ");
		Serial.println(getEEPROM(speedDialAddresses[i], 50));
		yield();
	}
	Serial.println();
}

void setup_eeprom()
{
	EEPROM.begin(LAST_ADDRESS + 1);
	delay(10);

	if (EEPROM.read(VERSION_ADDRESS) != VERSIONA || EEPROM.read(VERSION_ADDRESS + 1) != VERSIONB)
	{
		defaultEEPROM();
	}
	readSettings();
}

String getEEPROM(int startAddress, int len) {
	String myString;
  
	for (int i = startAddress; i < startAddress + len; i++) {
	  if (EEPROM.read(i) == 0x00) {
		break;
	  }
	  myString += char(EEPROM.read(i));
	  //Serial.print(char(EEPROM.read(i)));
	}
	//Serial.println();
	return myString;
  }
  
  
  void setEEPROM(String inString, int startAddress, int maxLen) {
	for (int i = startAddress; i < inString.length() + startAddress; i++) {
	  EEPROM.write(i, inString[i - startAddress]);
	  //Serial.print(i, DEC); Serial.print(": "); Serial.println(inString[i - startAddress]);
	  //if (EEPROM.read(i) != inString[i - startAddress]) { Serial.print(" (!)"); }
	  //Serial.println();
	}
	// null pad the remainder of the memory space
	for (int i = inString.length() + startAddress; i < maxLen + startAddress; i++) {
	  EEPROM.write(i, 0x00);
	  //Serial.print(i, DEC); Serial.println(": 0x00");
	}
  }