#pragma once

#include <Arduino.h>

class CommandHelper {
	public:
		CommandHelper();
		void Welcome();
		void DisplayHelp();
		void StoreSpeedDial(byte num, String location);		
};

extern CommandHelper commandHelper;


