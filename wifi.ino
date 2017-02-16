// const char* ssid = "IPC-SEDOVA48";
// const char* password = "bootwifi777";

#include <ESP8266WiFi.h>

const char* ssid = "ionflux.ru";
const char* password = "9021769760";

void setup_wifi() {

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);

	Serial.printf("Connect to WiFi: %s\n", ssid);

	while (WiFi.waitForConnectResult() != WL_CONNECTED) {

		WiFi.disconnect();

		Serial.println("Connection to WiFi Failed! Creating AP");

		WiFi.mode(WIFI_AP);
		if (!WiFi.softAP(ProhectName, "12345678")) {

			Serial.println("Create Wifi Failed! Rebooting!");
			delay(5000);

			ESP.reset();
		}
		else
			break;
	}

	Serial.println("=== WiFi Settings ====================");
	WiFi.printDiag(Serial);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println("======================================");
}