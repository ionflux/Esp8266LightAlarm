#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>

ESP8266WebServer server(80);

String getContentType(String filename) {
	if (server.hasArg("download")) return "application/octet-stream";
	else if (filename.endsWith(".htm")) return "text/html";
	else if (filename.endsWith(".html")) return "text/html";
	else if (filename.endsWith(".css")) return "text/css";
	else if (filename.endsWith(".js")) return "application/javascript";
	else if (filename.endsWith(".png")) return "image/png";
	else if (filename.endsWith(".gif")) return "image/gif";
	else if (filename.endsWith(".jpg")) return "image/jpeg";
	else if (filename.endsWith(".ico")) return "image/x-icon";
	else if (filename.endsWith(".xml")) return "text/xml";
	else if (filename.endsWith(".pdf")) return "application/x-pdf";
	else if (filename.endsWith(".zip")) return "application/x-zip";
	else if (filename.endsWith(".gz")) return "application/x-gzip";
	return "text/plain";
}

bool handleFileRead(String path) {
	
	if (path.endsWith("/")) path += "index.html";
	String contentType = getContentType(path);
	String pathWithGz = path + ".gz";
	if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
		if (SPIFFS.exists(pathWithGz))
			path += ".gz";
		File file = SPIFFS.open(path, "r");
		size_t sent = server.streamFile(file, contentType);
		file.close();
		return true;
	}

	Serial.println("404: " + path);
	return false;
}

void web_handle404() {

	if (!handleFileRead(server.uri()))
		server.send(404, "text/plain", "File not found");
}

void setup_webserver() {

	Serial.println("Starting HTTP server");

	SPIFFS.begin();

	Serial.println("HTTP server files:");

	Dir dir = SPIFFS.openDir("/");
	while (dir.next()) {
		String fileName = dir.fileName();
		size_t fileSize = dir.fileSize();
		Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), String(fileSize).c_str());
	}
	Serial.printf("\n");

	server.onNotFound(web_handle404);

	server.begin();

	Serial.println("HTTP server started");
}

void handle_webserver() {
	
	server.handleClient();
}