#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

#define LED 2

ESP8266WebServer server(80);

void setup()
{
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);

    Serial.begin(9600);

    // Connect to Wi-Fi network with SSID and password
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", []()
              { server.send(200, "text/plain", "Hello Para Warrior IoT"); });

    server.on("/status", []()
              { server.send(200, "text/plain", "Ini adalah Page Status Aktif"); });

    server.on("/flash", handleFlashing);
    server.on("/toggle", handleToggle);
    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("Webserver dijalankan");
}

void loop()
{
    server.handleClient();
}

void handleFlashing()
{
    int flash;
    int delays;
    String message = "";
    message = "Flashing " + server.arg("flash") + " times with " + server.arg("delay") + " ms delay";
    server.send(200, "text/plain", message);
    if (server.arg("flash") != "")
    {
        flash = server.arg("flash").toInt();
    }
    else
    {
        flash = 20;
    }

    if (server.arg("delay") != "")
    {
        delays = server.arg("delay").toInt();
    }
    else
    {
        delays = 100;
    }

    for (int i = 0; i < flash; i++)
    {
        delay(delays);
        digitalWrite(LED, LOW);
        delay(delays);
        digitalWrite(LED, HIGH);
    }
    digitalWrite(LED, HIGH);
}

void handleToggle()
{
    String Pins = server.arg("pin");
    String status = server.arg("status");
    digitalWrite(Pins.toInt(), status.toInt());
    server.send(200, "text/plain", "Pin " + Pins + " with status " + status);
}

void handleNotFound()
{
    server.send(404, "text/plain", "Page not found ...");
}
