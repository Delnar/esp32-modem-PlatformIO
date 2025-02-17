#include <Arduino.h>
#include <config\config_defines.h>
#include <config\config.h>
#include <EEPROM.h>
#include <serial_helper\serial_helper.h>

ConfigSettings settings;
String build = "20160621182048";

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

ConfigSettings::ConfigSettings() {

}

void ConfigSettings::WriteSettings() {
	_SetEEPROM(Ssid, SSID_ADDRESS, SSID_LEN);
	_SetEEPROM(Password, PASS_ADDRESS, PASS_LEN);
	_SetEEPROM(BusyMsg, BUSY_MSG_ADDRESS, BUSY_MSG_LEN);

	EEPROM.write(BAUD_ADDRESS, settings.Serialspeed);
	EEPROM.write(ECHO_ADDRESS, byte(settings.Echo));
	EEPROM.write(AUTO_ANSWER_ADDRESS, byte(settings.AutoAnswer));
	EEPROM.write(SERVER_PORT_ADDRESS, highByte(settings.TcpServerPort));
	EEPROM.write(SERVER_PORT_ADDRESS + 1, lowByte(settings.TcpServerPort));
	EEPROM.write(TELNET_ADDRESS, byte(settings.Telnet));
	EEPROM.write(VERBOSE_ADDRESS, byte(settings.VerboseResults));
	EEPROM.write(PET_TRANSLATE_ADDRESS, byte(settings.PetTranslate));
	EEPROM.write(FLOW_CONTROL_ADDRESS, byte(settings.FlowControl));
	EEPROM.write(PIN_POLARITY_ADDRESS, byte(settings.PinPolarity));

	for (int i = 0; i < 10; i++)
	{
		_SetEEPROM(settings.SpeedDials[i], speedDialAddresses[i], 50);
	}
	EEPROM.commit();
}

void ConfigSettings::ReadSettings() {
	settings.Echo = EEPROM.read(ECHO_ADDRESS);
	settings.AutoAnswer = EEPROM.read(AUTO_ANSWER_ADDRESS);
	settings.Serialspeed = EEPROM.read(BAUD_ADDRESS);

	settings.Ssid = _GetEEPROM(SSID_ADDRESS, SSID_LEN);
	settings.Password = _GetEEPROM(PASS_ADDRESS, PASS_LEN);
	settings.BusyMsg = _GetEEPROM(BUSY_MSG_ADDRESS, BUSY_MSG_LEN);
	settings.TcpServerPort = word(EEPROM.read(SERVER_PORT_ADDRESS), EEPROM.read(SERVER_PORT_ADDRESS + 1));
	settings.Telnet = EEPROM.read(TELNET_ADDRESS);
	settings.VerboseResults = EEPROM.read(VERBOSE_ADDRESS);
	settings.PetTranslate = EEPROM.read(PET_TRANSLATE_ADDRESS);
	settings.FlowControl = EEPROM.read(FLOW_CONTROL_ADDRESS);
	settings.PinPolarity = EEPROM.read(PIN_POLARITY_ADDRESS);

	for (int i = 0; i < 10; i++)
	{
		settings.SpeedDials[i] = _GetEEPROM(speedDialAddresses[i], 50);
	}

	// Check if it's out of bounds-- we have to be able to talk (specifically serial speed)
	if (settings.Serialspeed < 0 || settings.Serialspeed > MAXBAUDS) {
		settings.Serialspeed = 0;
	}	
}

void ConfigSettings::DefaultEEPROM()
{
	EEPROM.write(VERSION_ADDRESS, VERSIONA);
	EEPROM.write(VERSION_ADDRESS + 1, VERSIONB);

	_SetEEPROM("", SSID_ADDRESS, SSID_LEN);
	_SetEEPROM("", PASS_ADDRESS, PASS_LEN);
	_SetEEPROM("d", IP_TYPE_ADDRESS, 1);
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

	_SetEEPROM("bbs.fozztexx.com:23", speedDialAddresses[0], 50);
	_SetEEPROM("cottonwoodbbs.dyndns.org:6502", speedDialAddresses[1], 50);
	_SetEEPROM("borderlinebbs.dyndns.org:6400", speedDialAddresses[2], 50);
	_SetEEPROM("particlesbbs.dyndns.org:6400", speedDialAddresses[3], 50);
	_SetEEPROM("reflections.servebbs.com:23", speedDialAddresses[4], 50);
	_SetEEPROM("heatwavebbs.com:9640", speedDialAddresses[5], 50);

	for (int i = 5; i < 10; i++) {
		_SetEEPROM("", speedDialAddresses[i], 50);
	}

	_SetEEPROM("SORRY, SYSTEM IS CURRENTLY BUSY. PLEASE TRY AGAIN LATER.", BUSY_MSG_ADDRESS, BUSY_MSG_LEN);
	EEPROM.commit();
}

void ConfigSettings::DisplayCurrentSettings()
{
	serialHelper.xPrintln("ACTIVE PROFILE:");
	yield();
	serialHelper.Println("BAUD: {0}", serialHelper.GetBaudRate(Serialspeed));
	yield();
	serialHelper.Println("SSID: {0}", Ssid);
	yield();
	serialHelper.Println("PASS: {0}", Password);
	yield();
	serialHelper.Println("SERVER TCP PORT: {0}", TcpServerPort);
	yield();
	serialHelper.Println("BUSY MSG: {0}", BusyMsg);
	yield();
	serialHelper.Print("E{0} ", Echo);
	yield();
	serialHelper.Print("V{0} ", VerboseResults);
	yield();
	serialHelper.Print("&K{0} ", FlowControl);
	yield();
	serialHelper.Print("&P{0} ", PinPolarity);
	yield();
	serialHelper.Print("NET{0} ", Telnet);
	yield();
	serialHelper.Print("PET{0} ", PetTranslate);
	yield();
	serialHelper.Print("S0:{0} ", AutoAnswer);
	yield();
	serialHelper.xPrintln();
	yield();

	Serial.println("SPEED DIAL:");
	for (int i = 0; i < 10; i++) {
		serialHelper.Println("{0}: {1}", i, SpeedDials[i]);
		yield();
	}
	Serial.println();
}

void ConfigSettings::DisplayStoredSettings()
{

	serialHelper.xPrintln("STORED PROFILE:");
	yield();
	serialHelper.Println("BAUD: {0}", serialHelper.GetBaudRate(EEPROM.read(BAUD_ADDRESS)));
	yield();
	serialHelper.Println("SSID: {0}", _GetEEPROM(SSID_ADDRESS, SSID_LEN));
	yield();
	serialHelper.Println("PASS: {0}", _GetEEPROM(PASS_ADDRESS, PASS_LEN));
	yield();
	serialHelper.Println("SERVER TCP PORT: {0}", word(EEPROM.read(SERVER_PORT_ADDRESS), EEPROM.read(SERVER_PORT_ADDRESS+1)));
	yield();
	serialHelper.Println("BUSY MSG: {0}", _GetEEPROM(BUSY_MSG_ADDRESS, BUSY_MSG_LEN));
	yield();
	serialHelper.Print("E{0} ", EEPROM.read(ECHO_ADDRESS));
	yield();
	serialHelper.Print("V{0} ", EEPROM.read(VERBOSE_ADDRESS));
	yield();
	serialHelper.Print("&K{0} ", EEPROM.read(FLOW_CONTROL_ADDRESS));
	yield();
	serialHelper.Print("&P{0} ", EEPROM.read(PIN_POLARITY_ADDRESS));
	yield();
	serialHelper.Print("NET{0} ", EEPROM.read(TELNET_ADDRESS));
	yield();
	serialHelper.Print("PET{0} ", EEPROM.read(PET_TRANSLATE_ADDRESS));
	yield();
	serialHelper.Print("S0:{0} ", EEPROM.read(AUTO_ANSWER_ADDRESS));
	yield();
	serialHelper.xPrintln();
	yield();

	Serial.println("SPEED DIAL:");
	for (int i = 0; i < 10; i++) {
		serialHelper.Println("{0}: {1}", i, _GetEEPROM(speedDialAddresses[i], 50));
		yield();
	}
	Serial.println();
}

void ConfigSettings::SetupEEPROM() {
	EEPROM.begin(LAST_ADDRESS + 1);
	delay(10);
	if (EEPROM.read(VERSION_ADDRESS) != VERSIONA || EEPROM.read(VERSION_ADDRESS + 1) != VERSIONB) {
		DefaultEEPROM();
	}
	ReadSettings();

}

String ConfigSettings::_GetEEPROM(int startAddress, int len) {
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
  
  
void ConfigSettings::_SetEEPROM(String inString, int startAddress, int maxLen) {
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