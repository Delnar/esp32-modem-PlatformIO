#include <Arduino.h>
#include <config\config_defines.h>
#include <button_helper\button_helper.h>
#include <config\config.h>
#include <serial_helper\serial_helper.h>


ButtonHelper::ButtonHelper() {
}


// Hold for 5 seconds to switch to 300 baud
// Slow flash: keep holding
// Fast flash: let go
int ButtonHelper::checkButton() {
	long time = millis();
	while (digitalRead(SWITCH_PIN) == LOW && millis() - time < 5000) {
	  delay(250);
	  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
	  yield();
	}
	if (millis() - time > 5000) {
	  // Switch to 300 baud
	  serialHelper.SetBaudRate(0);
	  delay(100);
	  while (digitalRead(SWITCH_PIN) == LOW) {
		delay(50);
		digitalWrite(LED_PIN, !digitalRead(LED_PIN));
		yield();
	  }
	  return 1;
	} else {
	  return 0;
	}
  }

ButtonHelper buttonHelper;