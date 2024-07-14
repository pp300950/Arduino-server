#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "Pone";
const char* password = "12345678";
int ledPin = D2; // ให้แทนที่ D2 ด้วยขาที่ต่อ LED

ESP8266WebServer server(80);

void handleCommand() {
  String command = server.arg("led");
  
  if (command == "on") {
    digitalWrite(ledPin, HIGH); // กระพริบ LED
    delay(500);
    digitalWrite(ledPin, LOW);
    server.send(200, "text/plain", "LED flashed!");
  } else {
    server.send(400, "text/plain", "Invalid command");
  }
}

void setup(void) {
  Serial.begin(115200);
  delay(10);

  // ต่อ WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  server.on("/command", handleCommand);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
