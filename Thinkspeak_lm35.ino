#include <ESP8266WiFi.h> 

int outputPin = A0; 
int analogValue;
float millivolts, celsius;

String apiKey = "OQ26CQKN195R812T"; 
const char* ssid = "ASUS";
const char* password = "12345678";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(10);
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
}

void loop() {
  analogValue = analogRead(outputPin);
  millivolts = (analogValue / 1024.0) * 3300;
  celsius = millivolts / 10;

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "field1=";
    postStr += String(celsius);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n"); 
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: "); // Use 'Content-Length' with correct spelling
    client.print(postStr.length()); // Use .length() to get string length
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();
  Serial.println("\nWaiting...");
  delay(5000);
}