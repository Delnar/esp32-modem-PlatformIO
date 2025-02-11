#include <Arduino.h>
#include <config_defines.h>
#include <button_helper.h>
#include <config.h>
#include <serial_helpers.h>

// Hold for 5 seconds to switch to 300 baud
// Slow flash: keep holding
// Fast flash: let go
int checkButton() {
	long time = millis();
	while (digitalRead(SWITCH_PIN) == LOW && millis() - time < 5000) {
	  delay(250);
	  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
	  yield();
	}
	if (millis() - time > 5000) {
	  Serial.flush();
	  Serial.end();
	  settings.serialspeed = 0;
	  delay(100);
	  Serial.begin(bauds[settings.serialspeed]);
	  sendResult(R_OK);
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