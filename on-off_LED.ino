#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>  

const char* ssid = "PP";
const char* password = "12345678";

ESP8266WebServer server(80);

const int ledPin = 2;
bool ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/ledstate", HTTP_GET, handleLedState);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String ledStatus = (ledState == HIGH) ? "ON" : "OFF";

  String htmlContent = "<!DOCTYPE html>\
  <html lang=\"en\">\
  <head>\
    <title>ESP8266 Web Server</title>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
  </head>\
  <body>\
    <p> LED Status: <span id=\"led-state\">"
                       + ledStatus + "</span> </p>\
    <button onclick=\"toggleLed()\"> TOGGLE </button>\
    <script>\
      function toggleLed() {\
        var xhr = new XMLHttpRequest();\
        xhr.onreadystatechange = function() {\
          if (this.readyState == 4 && this.status == 200) {\
            document.getElementById(\"led-state\").innerHTML = this.responseText;\
          }\
        };\
        xhr.open(\"GET\", \"/ledstate\", true);\
        xhr.send();\
      }\
    </script>\
  </body>\
  </html>";

  server.send(200, "text/html", htmlContent);
}

void handleLedState() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
 
  WiFiClient client;

  String ledStateStr = (ledState == HIGH) ? "ON" : "OFF";
  String postData = "{\"led_status\": \"" + ledStateStr + "\"}";
  HTTPClient http;
  http.begin(client, "http://192.168.60.155/ledstatus"); 
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(postData);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  http.end();

  server.send(200, "text/plain", ledStateStr);
}
