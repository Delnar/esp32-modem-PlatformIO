#pragma once

#include <Arduino.h>

#undef  R_OK
#define R_OK 0
#define R_CONNECT 1
#define R_RING 2
#define R_NOCARRIER 3
#define R_ERROR 4
#define R_NONE 5
#define R_NODIALTONE 6
#define R_BUSY 7
#define R_NOANSWER 8

#define MAXBAUDS 9
#define MAXRESULTCODES 9

class SerialHelper {
	public:
		SerialHelper();
		
		void SetBaudRate(int index);
		int GetBaudRate(int index);
		int GetBaudRate();

		String GetResultCode(int resultCode);

		void SendResult(int resultCode);
		void SendString(String msg);

		void BeginSerial();
		void EndSerial();

		void Print(const char * msg, ...);
		void Println(const char * msg, ...);

		void xPrint(const char * msg);
		void xPrintln(const char * msg);
		void xPrintln();

	private:
		int _Bauds[MAXBAUDS] = { 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 };
		String _ResultCodes[MAXRESULTCODES] = { "OK", "CONNECT", "RING", "NO CARRIER", "ERROR", "", "NO DIALTONE", "BUSY", "NO ANSWER" };
		int _Baud_Speed = 0;
};

extern SerialHelper serialHelper;

