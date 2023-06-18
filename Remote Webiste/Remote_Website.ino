

#include <SocketIoClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRutils.h>
#include <IRsend.h>
#include <IRrecv.h>

IRsend irsend(4); // Send using GPIO 4.
const uint16_t kRecvPin = 5;

IRrecv irrecv(kRecvPin);
decode_results results;

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

const char *ssid1 = "Study hard";
const char *password1 = "creads418";

IPAddress ip(192, 168, 0, 101);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

void setup()
{

    irsend.begin();
    irrecv.enableIRIn();
    Serial.begin(9600);
    delay(10);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid1, password1);
    WiFi.begin(ssid, password);
    WiFi.config(ip, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Wifi Connected !");
    Serial.println(WiFi.SSID());
    Serial.print("IP Address Route = ");
    Serial.println(WiFi.localIP());
    Serial.print("IP Address Local = ");
    Serial.println(WiFi.softAPIP());
    Serial.println("Connecting to ..");
    Serial.print("SSID = ");
}

void loop()
{
    if (irrecv.decode(&results))
    {
        // print() & println() can't handle printing long longs. (uint64_t)
        serialPrintUint64(results.value, HEX);
        Serial.println("");
        irrecv.resume(); // Receive the next value
    }
    delay(100);
}