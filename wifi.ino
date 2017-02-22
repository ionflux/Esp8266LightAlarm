// const char* ssid = "IPC-SEDOVA48";
// const char* password = "bootwifi777";

#include <ESP8266WiFi.h>

const char* ssid = "ionflux.ru";
const char* password = "9021769760";

const byte DNS_PORT = 53;
IPAddress apIP(10, 10, 10, 1);

void setup_wifi() {

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);

	Serial.printf("Connect to WiFi: %s\n", ssid);

	while (WiFi.waitForConnectResult() != WL_CONNECTED)
	{
		WiFi.disconnect();

		Serial.println("Connection to WiFi Failed! Creating AP");

		if (WiFi.mode(WIFI_AP) && WiFi.softAP(ProhectName, "12345678") && WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0))) {

			WiFi.begin();

			Serial.println("WiFi AP Created");

			IsAPMode = true;

			break;

		} else {

			Serial.println("Create Wifi Failed! Rebooting!");
			delay(5000);

			ESP.reset();
		}
	}

	Serial.println("=== WiFi Settings ====================");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println("======================================");
}