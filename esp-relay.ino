#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "wifi_credentials.h"

ESP8266WebServer server(80);

const unsigned char CLOSE_COMMAND[] = { 0xA0, 0x01, 0x00, 0xA1 };
const unsigned char OPEN_COMMAND[] = { 0xA0, 0x01, 0x01, 0xA2 };

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting to connect…");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRootPath);
  server.on("/reset", HTTP_POST, handleResetPath);
  server.begin();
  Serial.println("Server listening");
}

void loop() {
  server.handleClient();
}

void send_html(char *html) {
  server.send(200, "text/html", String("<html><head><title>ESP8266 Relay</title></head><body>") + html + String("</body></html"));
}

void handleRootPath() {
  send_html("Welcome to ESP8266 Relay<form action=\"/reset\" method=\"post\"><input type=\"submit\" value=\"Reset\"></form>");
}

void handleResetPath() {
  Serial.write(OPEN_COMMAND, 4);
  delay(1000);
  Serial.write(CLOSE_COMMAND, 4);

  send_html("Relay reseted.<br /><a href=\"/\">Back to main page</a>");
}
