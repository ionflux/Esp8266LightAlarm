#include <stdio.h>
#include <ArduinoOTA.h>
#include <WiFiUdp.h>

const char* ota_password = "1520";

void ota_handle_start() {
	Serial.println("OTA: Start read flash...");
}

void ota_handle_end() {
	Serial.println("\nOTA: End. Rebooting in 0.1 seconds...");
	delay(100);
	ESP.reset();
}

void ota_handle_progress(unsigned int progress, unsigned int total) {
	Serial.print(".");
}

void setup_ota_update() {

	Serial.println("Starting OTA server");

	// Port defaults to 8266
	ArduinoOTA.setPort(8266);
	ArduinoOTA.setHostname(ProhectName);

	// No authentication by default
	ArduinoOTA.setPassword(ota_password);

	ArduinoOTA.onStart(ota_handle_start);
	ArduinoOTA.onProgress(ota_handle_progress);

	ArduinoOTA.onError([](ota_error_t error) {
		Serial.printf("OTA: Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
		else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
		else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
		else if (error == OTA_END_ERROR) Serial.println("End Failed");

		Serial.println("\n");
	});
	ArduinoOTA.onEnd(ota_handle_end);


	ArduinoOTA.begin();
	Serial.println("OTA server started");
}

void handle_ota() {

	ArduinoOTA.handle();
}