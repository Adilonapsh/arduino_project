#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

String sensorpir,sensorultra,kirimdata,payload;

const char* ssid="YOUR_SSID";
const char* password="YOUR_PASSWORD";

const char* ssid1="YOUR_SSID2";
const char* password1="YOUR_PASSWORD2";

const char* host="192.168.0.101";
ESP8266WebServer server(80);

const int pir=5;
const int echo=4;
const int trig=0;

const int Relay1=14;
const int Relay2=12;
const int Relay3=13;

long durasi;
int Jarak;

int detek=false;
bool Relays1=false;
bool Relays2=false;
bool Relays3=false;

void setup() {
  // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(Relay1,OUTPUT);
  pinMode(Relay2,OUTPUT);
  pinMode(Relay3,OUTPUT);

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

  server.on("/datarelay",HTTP_POST,dataRelay);
  server.begin();
  Serial.println("Server Berjalan..");
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
  server.handleClient();
  
}

void sendSensorData(){
  HTTPClient http;
  sensorultra=Jarak;
  sensorpir=detek;

  kirimdata="sensorultra="+sensorultra+"&sensorpir="+detek+"&Relay1="+Relays1+"&Relay2="+Relays2+"&Relay3="+Relays3;
  http.begin("http://192.168.0.101/ESP8266/Terima_data.php");
  http.addHeader("Content-Type","application/x-www-form-urlencoded");

  int httpcode=http.POST(kirimdata);
  payload=http.getString();

  Serial.println(httpcode);
  Serial.println(payload);

  http.end();
  delay(1000);
}
void cekData(){
  if(digitalRead(Relay1)==HIGH){
    Relays1=true;
  }else if(digitalRead(Relay1)==LOW){
    Relays1=false;
  }
  if(digitalRead(Relay2)==HIGH){
    Relays2=true;
  }else if(digitalRead(Relay2)==LOW){
    Relays2=false;
  }
  if(digitalRead(Relay3)==HIGH){
    Relays3=true;
  }else if(digitalRead(Relay3)==LOW){
    Relays3=false;
  }
}

void dataRelay(){
  if(server.hasArg("pin")&& server.hasArg("state")){
    int statusPin=server.arg("state").toInt();
    String namaPin= server.arg("pin");
    static const uint8_t pinAddress[]={14,12,13};

    digitalWrite(pinAddress[namaPin.toInt()],statusPin);
    server.send(200,"text/plain","Command Done ! ");
  }
  else
  {
    server.send(200,"text/plain","Command Not Found !");
  } 
}
