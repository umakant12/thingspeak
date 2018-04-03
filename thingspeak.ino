#include <ESP8266WiFi.h>

const char* ssid = "IoT DL5";                     //"YourNetworkSSID"
const char* password = "password";                //"YourPassword"
const char* host = "api.thingspeak.com";    
const char* writeAPIKey = "1TD5876D93IST4HI";     //"YourWriteAPI"

int value=0;

void setup() {
  pinMode(A0,INPUT);
  Serial.begin(9600);
  delay(1000);
  //  Connect to WiFi network
  Serial.print("Connecting to ssid=");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {  
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected");
}

void loop()
{
  value=analogRead(A0);
  Serial.print("Value = ");
  Serial.println(value,DEC);
 
  // make TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }
  String url = "/update?key=";
  url+=writeAPIKey;
  url+="&field1=";
  url+=String(value);
  url+="\r\n";
  
  // Request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
    delay(2000);
}
