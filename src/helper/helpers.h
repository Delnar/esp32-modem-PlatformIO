#pragma once
#include <Arduino.h>

class Helpers {
	public:
		Helpers();
		String ConnectTimeString();
		void WaitForSpace();
};

extern Helpers helpers;
