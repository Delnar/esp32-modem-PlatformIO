#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>


class WifiHelper {
	public:
		WifiHelper();
		void ConnectWiFi();
		void DisconnectWiFi();
		void DisplayNetworkStatus();


	private: 
		WiFiClient _tcpClient;
		WiFiServer _tcpServer;

		String _IPToString(IPAddress ip);
};

extern WifiHelper wifiHelper;



