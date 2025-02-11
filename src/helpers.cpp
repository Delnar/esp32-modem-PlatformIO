#include <Arduino.h>
#include <config.h>

String connectTimeString()
{
	unsigned long now = millis();
	int secs = (now - settings.connectTime) / 1000;
	int mins = secs / 60;
	int hours = mins / 60;
	String out = "";
	if (hours < 10)
		out.concat("0");
	out.concat(String(hours));
	out.concat(":");
	if (mins % 60 < 10)
		out.concat("0");
	out.concat(String(mins % 60));
	out.concat(":");
	if (secs % 60 < 10)
		out.concat("0");
	out.concat(String(secs % 60));
	return out;
}

void waitForSpace()
{
	Serial.print("PRESS SPACE");
	char c = 0;
	while (c != 0x20)
	{
		if (Serial.available() > 0)
		{
			c = Serial.read();
			if (settings.petTranslate == true)
			{
				if (c > 127)
					c -= 128;
			}
		}
	}
	Serial.print("\r");
}