#include <WiFi.h>
#include <config.h>
#include <WiFiClient.h>
#include <wifi_helpers.h>
#include <display_helper.h>
#include <helpers.h>

WiFiClient tcpClient;
WiFiServer tcpServer(settings.tcpServerPort);

void connectWiFi()
{
	if (settings.ssid == "" || settings.password == "")
	{
		// TODO: Display error on Monocrhome display
		Serial.println("CONFIGURE SSID AND PASSWORD. TYPE AT? FOR HELP.");
		return;
	}
	WiFi.begin(settings.ssid.c_str(), settings.password.c_str());
	// TODO: Dipaly connecting on Monochrome display
	Serial.print("\nCONNECTING TO SSID ");
	Serial.print(settings.ssid);
	uint8_t i = 0;

	while (WiFi.status() != WL_CONNECTED && i++ < 20)
	{
		// TODO: Do something with the Monochrome display
		//   digitalWrite(LED_PIN, LOW);
		//   delay(250);
		//   digitalWrite(LED_PIN, HIGH);
		//   delay(250);
		Serial.print(".");
	}
	Serial.println();
	if (i == 21)
	{
		// TODO: Display error on Monochrome display
		Serial.print("COULD NOT CONNET TO ");
		Serial.println(settings.ssid);
		WiFi.disconnect();
		// TODO: This should be part of the display helper for displaying the WIFI status on the yellow bar
		// updateLed();
	}
	else
	{
		Serial.print("CONNECTED TO ");
		Serial.println(WiFi.SSID());
		Serial.print("IP ADDRESS: ");
		Serial.println(WiFi.localIP());
		// TODO: This should be part of the display helper for displaying the WIFI status on the yellow bar
		// updateLed();
	}
}

void disconnectWiFi()
{
	WiFi.disconnect();

	// updateLed();
}

String ipToString(IPAddress ip)
{
	char s[16];
	sprintf(s, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
	return s;
}

void displayNetworkStatus()
{
	Serial.print("WIFI STATUS: ");
	if (WiFi.status() == WL_CONNECTED)
	{
		Serial.println("CONNECTED");
	}
	if (WiFi.status() == WL_IDLE_STATUS)
	{
		Serial.println("OFFLINE");
	}
	if (WiFi.status() == WL_CONNECT_FAILED)
	{
		Serial.println("CONNECT FAILED");
	}
	if (WiFi.status() == WL_NO_SSID_AVAIL)
	{
		Serial.println("SSID UNAVAILABLE");
	}
	if (WiFi.status() == WL_CONNECTION_LOST)
	{
		Serial.println("CONNECTION LOST");
	}
	if (WiFi.status() == WL_DISCONNECTED)
	{
		Serial.println("DISCONNECTED");
	}
	if (WiFi.status() == WL_SCAN_COMPLETED)
	{
		Serial.println("SCAN COMPLETED");
	}
	yield();

	Serial.print("SSID.......: ");
	Serial.println(WiFi.SSID());

	//  Serial.print("ENCRYPTION: ");
	//  switch(WiFi.encryptionType()) {
	//    case 2:
	//      Serial.println("TKIP (WPA)");
	//      break;
	//    case 5:
	//      Serial.println("WEP");
	//      break;
	//    case 4:
	//      Serial.println("CCMP (WPA)");
	//      break;
	//    case 7:
	//      Serial.println("NONE");
	//      break;
	//    case 8:
	//      Serial.println("AUTO");
	//      break;
	//    default:
	//      Serial.println("UNKNOWN");
	//      break;
	//  }

	byte mac[6];
	WiFi.macAddress(mac);
	Serial.print("MAC ADDRESS: ");
	Serial.print(mac[0], HEX);
	Serial.print(":");
	Serial.print(mac[1], HEX);
	Serial.print(":");
	Serial.print(mac[2], HEX);
	Serial.print(":");
	Serial.print(mac[3], HEX);
	Serial.print(":");
	Serial.print(mac[4], HEX);
	Serial.print(":");
	Serial.println(mac[5], HEX);
	yield();

	Serial.print("IP ADDRESS.: ");
	Serial.println(WiFi.localIP());
	yield();
	Serial.print("GATEWAY....: ");
	Serial.println(WiFi.gatewayIP());
	yield();
	Serial.print("SUBNET MASK: ");
	Serial.println(WiFi.subnetMask());
	yield();
	Serial.print("SERVER PORT: ");
	Serial.println(settings.tcpServerPort);
	yield();
	Serial.print("WEB CONFIG.: HTTP://");
	Serial.println(WiFi.localIP());
	yield();
	Serial.print("CALL STATUS: ");
	yield();
	if (settings.callConnected)
	{
		Serial.print("CONNECTED TO ");
		Serial.println(ipToString(tcpClient.remoteIP()));
		yield();
		Serial.print("CALL LENGTH: ");
		Serial.println(connectTimeString());
		yield();
	}
	else
	{
		Serial.println("NOT CONNECTED");
	}
}