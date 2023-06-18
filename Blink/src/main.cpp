#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid="YOUR_SSID";
const char* password="YOUR_PASSWORD";
ESP8266WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  Serial.begin(9600);

  WiFi.begin(ssid,password);
  while (WiFi.status()!= WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wifi Connected !");
  Serial.print("SSID : ");
  Serial.println(WiFi.SSID());
  Serial.print("IP ADDRESS : ");
  Serial.println(WiFi.localIP());

  server.on("/setpin",HTTP_POST,setPin);
  server.begin();
  Serial.println("Server Berjalan..");

}

void loop() {
  server.handleClient();
  // put your main code here, to run repeatedly:
}

void setPin() {
  if(server.hasArg("pin")&& server.hasArg("state")){
    int statusPin=server.arg("state").toInt();
    String namaPin= server.arg("pin");
    static const uint8_t pinAddress[]={16,5,4,0,2,14,12,13,15,3,1};

    digitalWrite(pinAddress[namaPin.substring(1).toInt()],statusPin);
    server.send(200,"text/plain","Command Done ! ");
  }
  else
  {
    server.send(200,"text/plain","Command Not Found !");
  } 
}
