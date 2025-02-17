#include <Arduino.h>
#include <serial_helper\serial_helper.h>
#include <config\config.h>
#include <helper\helpers.h>

SerialHelper::SerialHelper()
{
	
}

void SerialHelper::BeginSerial()
{
	Serial.begin(_Bauds[_Baud_Speed]);
}

void SerialHelper::EndSerial()
{
	Serial.flush();
	Serial.end();
}

String SerialHelper::GetResultCode(int resultCode)
{
	return _ResultCodes[resultCode];
}

int SerialHelper::GetBaudRate(int index)
{
	if (index < 0 || index >= MAXBAUDS) {
		return -1;
	}
	return _Bauds[index];
}

int SerialHelper::GetBaudRate() {
	return _Bauds[_Baud_Speed];
}

void SerialHelper::SendResult(int resultCode)
{
	Serial.print("\r\n");
	if (settings.VerboseResults == 0) {
		Serial.println(resultCode);
		return;
	}
	if (resultCode == R_CONNECT) {
		Serial.print(String(_ResultCodes[R_CONNECT]) + " " + String(_Bauds[settings.Serialspeed]));
	}
	else if (resultCode == R_NOCARRIER)	{
		Serial.print(String(_ResultCodes[R_NOCARRIER]) + " (" + helpers.ConnectTimeString() + ")");
	}
	else{
		Serial.print(String(_ResultCodes[resultCode]));
	}
	Serial.print("\r\n");
}

void SerialHelper::SendString(String msg)
{
	Serial.print("\r\n");
	Serial.print(msg);
	Serial.print("\r\n");
}

void SerialHelper::SetBaudRate(int index)
{
	if (index < 0 || index >= MAXBAUDS)	{
		SendResult(R_ERROR);
		return;
	}
	if (index == _Baud_Speed)	{
		SendResult(R_OK);
		return;
	}

	_Baud_Speed = index;	
	Serial.print("SWITCHING SERIAL PORT TO ");
	Serial.print(_Bauds[_Baud_Speed]);
	Serial.println(" IN 5 SECONDS");
	delay(5000);
	EndSerial();
	delay(200);
	BeginSerial();
	Serial.begin(_Bauds[_Baud_Speed]);
	delay(200);
	SendResult(R_OK);

	settings.Serialspeed = _Baud_Speed;	
}

void SerialHelper::Print(const char * msg, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, msg);
	vsnprintf(buffer, sizeof(buffer), msg, args);
	va_end(args);
	Serial.print(buffer);
}

void SerialHelper::Println(const char * msg, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, msg);
	vsnprintf(buffer, sizeof(buffer), msg, args);
	va_end(args);
	Serial.print(buffer);
	Serial.println();
}

void SerialHelper::xPrint(const char * msg)
{
	Serial.print(msg);
}

void SerialHelper::xPrintln(const char * msg)
{
	Serial.println(msg);
}

void SerialHelper::xPrintln()
{
	Serial.println();
}


SerialHelper serialHelper;

// void setCarrier(byte carrier)
// {
// 	if (settings.pinPolarity == P_NORMAL)
// 		carrier = !carrier;
// 	// TODO: Replace on the monochrome display
// 	// digitalWrite(DCD_PIN, carrier);
// }
