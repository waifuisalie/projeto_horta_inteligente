#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

// Pins
const int ledPin = 2;  // Change to the pin where your LED is connected
const int sensorPin = 34;  // Change to the pin where your sensor is connected

void handleRoot() {
  // Read sensor value
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (3.3 / 4095.0);

  // HTML content
  String html = "<html><body>";
  html += "<h1>ESP32 Web Server</h1>";
  html += "<p>Voltage: " + String(voltage, 2) + "V</p>";
  html += "<button onclick=\"location.href='/led/on'\">Turn LED ON</button>";
  html += "<button onclick=\"location.href='/led/off'\">Turn LED OFF</button>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleLEDOn() {
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleLEDOff() {
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start the server
  server.on("/", handleRoot);
  server.on("/led/on", handleLEDOn);
  server.on("/led/off", handleLEDOff);
  server.begin();

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}
