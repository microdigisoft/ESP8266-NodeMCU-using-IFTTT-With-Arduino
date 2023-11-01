#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* event_name = "YourEventName";
const char* key = "YourWebhookKey";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

void loop() {
  float bmesensor_reading = readBMESensor(); // Replace with your code to read the BMESensor
  
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    String url = "https://maker.ifttt.com/trigger/";
    url += event_name;
    url += "/with/key/";
    url += key;
    
    String payload = String("value1=") + bmesensor_reading;
    
    http.begin(client, url);  // Updated syntax here
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    int httpCode = http.POST(payload);
    
    if (httpCode == 200) {
      Serial.println("Email sent successfully!");
    } else {
      Serial.println("Failed to send email.");
    }
    
    http.end();
  }
  
  delay(5000); // Wait for 5 seconds before sending the next reading
}

float readBMESensor() {
  // Replace with your code to read the BMESensor and return the value
}
