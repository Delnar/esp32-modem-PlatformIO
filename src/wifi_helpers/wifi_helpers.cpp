#include <WiFi.h>
#include <config\config.h>
#include <WiFiClient.h>
#include <wifi_helpers\wifi_helpers.h>
#include <display_helper\display_helper.h>
#include <helper\helpers.h>
#include <serial_helper\serial_helper.h>

WifiHelper::WifiHelper()
{
	_tcpClient = WiFiClient();
	_tcpServer = WiFiServer(settings.TcpServerPort);
}


void WifiHelper::ConnectWiFi()
{
	if (settings.Ssid == "" || settings.Password == "")
	{
		// TODO: Display error on Monocrhome display
		displayHelper.ShowErrorSymbol = true;
		displayHelper.Draw(); 
		yield();
		serialHelper.xPrintln("CONFIGURE SSID AND PASSWORD. TYPE AT? FOR HELP.");		
		return;
	}

	displayHelper.ShowErrorSymbol = false;
	displayHelper.Draw(); 
	yield();
	
	WiFi.begin(settings.Ssid.c_str(), settings.Password.c_str());
	displayHelper.ShowWifiSymbol = true;
	serialHelper.Print("CONNECTING TO SSID {0}", settings.Ssid);

	uint8_t i = 0;

	displayHelper.ClearTextElements();
	displayHelper.AddTextElement(0, 32, DisplayHelper::FONT_6x10, "Connecting to:");
	displayHelper.AddTextElement(0, 48, DisplayHelper::FONT_6x10, "SSID: %s", settings.Ssid.c_str());

	// Should connect within 5 seconds
	while (WiFi.status() != WL_CONNECTED && i <= 20) {
		displayHelper.ShowWifiSymbol != displayHelper.ShowWifiSymbol;
		displayHelper.Draw();
		yield();
		delay(250);
		serialHelper.xPrint(".");
		i++;
	}
	serialHelper.xPrintln();	
	if (i >= 21){
		displayHelper.ShowWifiSymbol = false;
		displayHelper.ShowErrorSymbol = true;

		displayHelper.ClearTextElements();		
		displayHelper.AddTextElement(0, 32, DisplayHelper::FONT_6x10, "Failed connect to:");
		displayHelper.AddTextElement(0, 48, DisplayHelper::FONT_6x10, "SSID: %s", settings.Ssid.c_str());
		displayHelper.Draw();

		serialHelper.Println("COULD NOT CONNECT TO {0}", settings.Ssid);
		WiFi.disconnect();
	}
	else
	{
		displayHelper.ShowErrorSymbol = false;
		displayHelper.ShowWifiSymbol = true;
		displayHelper.ClearTextElements();		
		displayHelper.AddTextElement(0, 32, DisplayHelper::FONT_6x10, "Connecting to:");
		displayHelper.AddTextElement(0, 48, DisplayHelper::FONT_6x10, "SSID: %s", settings.Ssid.c_str());
		displayHelper.AddTextElement(0, 64, DisplayHelper::FONT_6x10, "IP: %s", _IPToString(WiFi.localIP()).c_str());
		displayHelper.Draw();

		serialHelper.Print("CONNECTED TO {0}", settings.Ssid);
	}
}

void disconnectWiFi()
{
	WiFi.disconnect();
	displayHelper.ShowWifiSymbol = true;
	displayHelper.Draw();
	// updateLed();
}

String WifiHelper::_IPToString(IPAddress ip)
{
	char s[16];
	sprintf(s, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
	return s;
}

void WifiHelper::DisplayNetworkStatus()
{
	serialHelper.xPrintln("WIFI STATUS: ");
	switch(WiFi.status()) {
		case WL_CONNECTED:
			serialHelper.xPrintln("CONNECTED");
			break;
		case WL_IDLE_STATUS:
			serialHelper.xPrintln("OFFLINE");
			break;
		case WL_CONNECT_FAILED:
			serialHelper.xPrintln("CONNECT FAILED");
			break;
		case WL_NO_SSID_AVAIL:
			serialHelper.xPrintln("SSID UNAVAILABLE");
			break;
		case WL_CONNECTION_LOST:
			serialHelper.xPrintln("CONNECTION LOST");
			break;
		case WL_DISCONNECTED:
			serialHelper.xPrintln("DISCONNECTED");
			break;
		case WL_SCAN_COMPLETED:
			serialHelper.xPrintln("SCAN COMPLETED");
			break;
		default:
			serialHelper.xPrintln("UNKNOWN");
			break;
	}
	yield();

	serialHelper.Println("SSID: {}", WiFi.SSID());

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
	serialHelper.Println("MAC ADDRESS: %02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	yield();

	serialHelper.Println("IP ADDRESS: {0}", _IPToString(WiFi.localIP()));
	yield();
	serialHelper.Println("GATEWAY: {0}", _IPToString(WiFi.gatewayIP()));
	yield();
	serialHelper.Println("SUBNET MASK: {0}", _IPToString(WiFi.subnetMask()));
	yield();
	serialHelper.Println("DNS: {0}", _IPToString(WiFi.dnsIP()));
	yield();
	serialHelper.Println("SERVER PORT: {0}", settings.TcpServerPort);
	yield();
	serialHelper.Println("WEB CONFIG.: HTTP://{0}", WiFi.localIP());
	yield();
	serialHelper.Print("CALL STATUS: ");
	yield();
	if (settings.CallConnected)
	{
		serialHelper.Println("CONNECTED TO {0}", _IPToString(_tcpClient.remoteIP()));
		yield();
		serialHelper.Println("CALL LENGTH: {0}", helpers.ConnectTimeString());
		yield();
	}
	else
	{
		serialHelper.xPrintln("NOT CONNECTED");
	}
}

WifiHelper wifiHelper;