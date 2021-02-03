#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

const char* ssid     = "ssid";
const char* password = "password";
#define RELAY 0 // relay connected to  GPIO0

const IPAddress remote_ip(192, 168, 0, 1); //Gateway

void setup() {
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);

  //Wait the Access Point starts
  delay(90000);
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi connected with ip ");
  Serial.println(WiFi.localIP());
  Serial.print("Pinging ip ");
  Serial.println(remote_ip);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("We're disconnected from Wifi... trying to re-connect");
    WiFi.reconnect();
    delay(5000);
  } else {
    if (Ping.ping(remote_ip)) {
      Serial.println("Success! Gateway is on");
      delay(5000);
    } else {
      Serial.println("Gateway is down :(");
      
      //Restart the router
      Serial.println("RELAY=OFF");
      digitalWrite(RELAY, HIGH);

      delay(5000);

      Serial.println("RELAY=ON");
      digitalWrite(RELAY, LOW);

      //Wait till the router starts
      delay(90000);

      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(5000);
        Serial.print(".");
      }
    }
  }
}
