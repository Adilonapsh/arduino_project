#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

String sensorpir,sensorultra,kirimdata,payload;

const char* ssid1="YOUR_SSID";
const char* password1="YOUR_PASSWORD";

const char* ssid="realme 5 Pro";
const char* password="UWEW";

const char* host="192.168.43.25";
ESP8266WebServer server(80);

const int pir=5;
const int echo=4;
const int trig=0;

const int led1=14;
const int led2=12;
const int led3=13;

long durasi;
int Jarak;

int detek=false;
bool leds1=false;
bool leds2=false;
bool leds3=false;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  digitalWrite(led1,HIGH);

  Serial.begin(9600);
  delay(1000);
  WiFi.begin(ssid,password);
  while(WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi Connected !");
  Serial.print("SSID = ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address = ");
  Serial.println(WiFi.localIP());
}

void loop() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);


  durasi = pulseIn(echo, HIGH);
  Jarak= durasi*0.034/2;

  Serial.print("Jarak : ");
  Serial.println(Jarak);
  
  long state = digitalRead(pir);
    if(state == HIGH) {
      detek=true;
      Serial.println("Motion detected!");
    }
    else {
      detek=false;
      Serial.println("Motion absent!");
      }
  cekData();
  sendSensorData();
  
}

void sendSensorData(){
  HTTPClient http;
  sensorultra=Jarak;
  sensorpir=detek;

  kirimdata="sensorultra="+sensorultra+"&sensorpir="+detek+"&led1="+leds1+"&led2="+leds2+"&led3="+leds3;
  http.begin("http://192.168.43.25/esp8266/Terima_data.php");
  http.addHeader("Content-Type","application/x-www-form-urlencoded");

  int httpcode=http.POST(kirimdata);
  payload=http.getString();

  Serial.println(httpcode);
  Serial.println(payload);

  http.end();
  delay(500);
}

void cekData(){
  if(digitalRead(led1) == HIGH){
    leds1=true;
  }else if(digitalRead(led1) == LOW){
    leds1=true;
  }else if(digitalRead(led1) == HIGH){
    leds2=true;
  }else if(digitalRead(led1) == LOW){
    leds2=true;
  }else if(digitalRead(led1) == HIGH){
    leds3=true;
  }else if(digitalRead(led1) == LOW){
    leds3=true;
  }
}

