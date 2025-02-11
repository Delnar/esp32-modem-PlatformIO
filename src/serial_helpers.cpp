#include <Arduino.h>
#include <serial_helpers.h>
#include <config.h>
#include <helpers.h>

const int bauds[] = { 300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200 };
const int baud_option_count = sizeof(bauds);

String resultCodes[] = { "OK", "CONNECT", "RING", "NO CARRIER", "ERROR", "", "NO DIALTONE", "BUSY", "NO ANSWER" };

void sendResult(int resultCode)
{
	Serial.print("\r\n");
	if (settings.verboseResults == 0)
	{
		Serial.println(resultCode);
		return;
	}
	if (resultCode == R_CONNECT)
	{
		Serial.print(String(resultCodes[R_CONNECT]) + " " + String(bauds[settings.serialspeed]));
	}
	else if (resultCode == R_NOCARRIER)
	{
		Serial.print(String(resultCodes[R_NOCARRIER]) + " (" + connectTimeString() + ")");
	}
	else
	{
		Serial.print(String(resultCodes[resultCode]));
	}
	Serial.print("\r\n");
}

void sendString(String msg)
{
	Serial.print("\r\n");
	Serial.print(msg);
	Serial.print("\r\n");
}

void setBaudRate(int inSpeed)
{
	if (inSpeed == 0)
	{
		sendResult(R_ERROR);
		return;
	}
	int foundBaud = -1;
	for (int i = 0; i < sizeof(bauds); i++)
	{
		if (inSpeed == bauds[i])
		{
			foundBaud = i;
			break;
		}
	}
	// requested baud rate not found, return error
	if (foundBaud == -1)
	{
		sendResult(R_ERROR);
		return;
	}
	if (foundBaud == settings.serialspeed)
	{
		sendResult(R_OK);
		return;
	}
	Serial.print("SWITCHING SERIAL PORT TO ");
	Serial.print(inSpeed);
	Serial.println(" IN 5 SECONDS");
	delay(5000);
	Serial.end();
	delay(200);
	Serial.begin(bauds[foundBaud]);
	settings.serialspeed = foundBaud;
	delay(200);
	sendResult(R_OK);
}

void setCarrier(byte carrier)
{
	if (settings.pinPolarity == P_NORMAL)
		carrier = !carrier;
	// TODO: Replace on the monochrome display
	// digitalWrite(DCD_PIN, carrier);
}
