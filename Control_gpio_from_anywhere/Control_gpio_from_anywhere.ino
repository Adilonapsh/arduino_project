#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

//Your IP address or domain name with URL path
const char* serverName = "http://192.168.0.101/Adilonapsh/public/nodemcu/getnodegpio/1";

// Update interval time set to 5 seconds
const long interval = 5000;
unsigned long previousMillis = 0;

String outputsState;

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long currentMillis = millis();
  StaticJsonDocument <1536> doc;
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED ){ 
      outputsState = httpGETRequest(serverName);
      Serial.println(outputsState);
      DeserializationError error = deserializeJson(doc,outputsState);
      if (error){
        Serial.print(F("DeserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }
      Serial.println(doc.size());
      for (int i = 0; i < doc.size(); i++) {
        const char* nama = doc[i]["name"];
        String gpio = doc[i]["gpio"];
        String state = doc[i]["state"];
        Serial.println(nama);
        Serial.println(gpio);
        Serial.println(state);
        pinMode(gpio.toInt(), OUTPUT);
        digitalWrite(gpio.toInt(), state.toInt());
      }
      // save the last HTTP GET Request
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
