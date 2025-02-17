#include <Arduino.h>
#include <config\config.h>
#include <command_helper\command_helper.h>
#include <helper\helpers.h>
#include <serial_helper\serial_helper.h>

CommandHelper::CommandHelper() {
}


void CommandHelper::Welcome() {
	serialHelper.xPrintln();
	serialHelper.Println("WIFI SIXFOUR BUILD {0} BY @PAULRICKARDS", build);
	serialHelper.xPrintln("Rewritten for ESP32 by @Delnar");
	serialHelper.xPrintln("BASED ON GITHUB.COM/JSALIN/ESP32_MODEM");
  }

void CommandHelper::DisplayHelp() {
	Welcome();
	serialHelper.xPrintln("AT COMMAND SUMMARY:"); yield();
	serialHelper.xPrintln("DIAL HOST.....: ATDTHOST:PORT"); yield();
	serialHelper.xPrintln("SPEED DIAL....: ATDSN (N=0-9)"); yield();
	serialHelper.xPrintln("SET SPEED DIAL: AT&ZN=HOST:PORT (N=0-9)"); yield();
	serialHelper.xPrintln("HANDLE TELNET.: ATNETN (N=0,1)"); yield();
	serialHelper.xPrintln("PET MCTERM TR.: ATPETN (N=0,1)"); yield();
	serialHelper.xPrintln("NETWORK INFO..: ATI"); yield();
	serialHelper.xPrintln("HTTP GET......: ATGET<URL>"); yield();
	serialHelper.xPrintln("SERVER PORT...: AT$SP=N (N=1-65535)"); yield();
	serialHelper.xPrintln("AUTO ANSWER...: ATS0=N (N=0,1)"); yield();
	serialHelper.xPrintln("SET BUSY MSG..: AT$BM=YOUR BUSY MESSAGE"); yield();
	serialHelper.xPrintln("LOAD NVRAM....: ATZ"); yield();
	serialHelper.xPrintln("SAVE TO NVRAM.: AT&W"); yield();
	serialHelper.xPrintln("SHOW SETTINGS.: AT&V"); yield();
	serialHelper.xPrintln("FACT. DEFAULTS: AT&F"); yield();
	serialHelper.xPrintln("PIN POLARITY..: AT&PN (N=0/INV,1/NORM)"); yield();
	serialHelper.xPrintln("ECHO OFF/ON...: ATE0 / ATE1"); yield();
	serialHelper.xPrintln("VERBOSE OFF/ON: ATV0 / ATV1"); yield();
	serialHelper.xPrintln("SET SSID......: AT$SSID=WIFISSID"); yield();
	serialHelper.xPrintln("SET PASSWORD..: AT$PASS=WIFIPASSWORD"); yield();
	serialHelper.xPrintln("SET BAUD RATE.: AT$SB=N (3,12,24,48,96"); yield();
	serialHelper.xPrintln("                192,384,576,1152)*100"); yield();
	helpers.WaitForSpace();
	serialHelper.xPrintln("FLOW CONTROL..: AT&KN (N=0/N,1/HW,2/SW)"); yield();
	serialHelper.xPrintln("WIFI OFF/ON...: ATC0 / ATC1"); yield();
	serialHelper.xPrintln("HANGUP........: ATH"); yield();
	serialHelper.xPrintln("ENTER CMD MODE: +++"); yield();
	serialHelper.xPrintln("EXIT CMD MODE.: ATO"); yield();
	serialHelper.xPrintln("QUERY MOST COMMANDS FOLLOWED BY '?'"); yield();
  }
  
  void storeSpeedDial(byte num, String location) {
	if (num < 0 || num > 9) { return; }		// This prevents buffer overflow/underflow
	settings.SpeedDials[num] = location;
	// Serial.print("STORED "); Serial.print(num); Serial.print(": "); Serial.println(location);
  }
  
  