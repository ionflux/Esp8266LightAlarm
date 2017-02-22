const char* ProhectName = "EspLightAlarm v1.1";

bool IsAPMode = false;

void setup() {

	Serial.begin(115200);
	Serial.printf("Booting %s...\n", ProhectName);

	setup_eeprom();
	setup_wifi();
	setup_ntp();
	setup_ota_update();
	setup_webserver();

	Serial.printf("%s ready\n\n", ProhectName);
}

void loop() {

	handle_ota();
	handle_webserver();
}