#include <Arduino.h>
#include <config.h>
#include <helpers.h>

void welcome() {
	Serial.println();
	Serial.println("WIFI SIXFOUR BUILD " + build + " BY @PAULRICKARDS");
	Serial.println("Rewritten for ESP32 by @Delnar");
	Serial.println("BASED ON GITHUB.COM/JSALIN/ESP32_MODEM");
  }

void displayHelp() {
	welcome();
	Serial.println("AT COMMAND SUMMARY:"); yield();
	Serial.println("DIAL HOST.....: ATDTHOST:PORT"); yield();
	Serial.println("SPEED DIAL....: ATDSN (N=0-9)"); yield();
	Serial.println("SET SPEED DIAL: AT&ZN=HOST:PORT (N=0-9)"); yield();
	Serial.println("HANDLE TELNET.: ATNETN (N=0,1)"); yield();
	Serial.println("PET MCTERM TR.: ATPETN (N=0,1)"); yield();
	Serial.println("NETWORK INFO..: ATI"); yield();
	Serial.println("HTTP GET......: ATGET<URL>"); yield();
	//Serial.println("SERVER PORT...: AT$SP=N (N=1-65535)"); yield();
	Serial.println("AUTO ANSWER...: ATS0=N (N=0,1)"); yield();
	Serial.println("SET BUSY MSG..: AT$BM=YOUR BUSY MESSAGE"); yield();
	Serial.println("LOAD NVRAM....: ATZ"); yield();
	Serial.println("SAVE TO NVRAM.: AT&W"); yield();
	Serial.println("SHOW SETTINGS.: AT&V"); yield();
	Serial.println("FACT. DEFAULTS: AT&F"); yield();
	Serial.println("PIN POLARITY..: AT&PN (N=0/INV,1/NORM)"); yield();
	Serial.println("ECHO OFF/ON...: ATE0 / ATE1"); yield();
	Serial.println("VERBOSE OFF/ON: ATV0 / ATV1"); yield();
	Serial.println("SET SSID......: AT$SSID=WIFISSID"); yield();
	Serial.println("SET PASSWORD..: AT$PASS=WIFIPASSWORD"); yield();
	Serial.println("SET BAUD RATE.: AT$SB=N (3,12,24,48,96"); yield();
	Serial.println("                192,384,576,1152)*100"); yield();
	waitForSpace();
	Serial.println("FLOW CONTROL..: AT&KN (N=0/N,1/HW,2/SW)"); yield();
	Serial.println("WIFI OFF/ON...: ATC0 / ATC1"); yield();
	Serial.println("HANGUP........: ATH"); yield();
	Serial.println("ENTER CMD MODE: +++"); yield();
	Serial.println("EXIT CMD MODE.: ATO"); yield();
	Serial.println("QUERY MOST COMMANDS FOLLOWED BY '?'"); yield();
  }
  
  void storeSpeedDial(byte num, String location) {
	if (num < 0 || num > 9) { return; }		// This prevents buffer overflow/underflow
	settings.speedDials[num] = location;
	// Serial.print("STORED "); Serial.print(num); Serial.print(": "); Serial.println(location);
  }
  
  