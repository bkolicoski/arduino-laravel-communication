/*
 * Arduino communication with  a web server example
 */
 
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
 
const char *ssid = "YourWIFINetwork";  
const char *password = "your_password";
 
//Web/Server address to read/write from 
const char *host = "http://192.168.2.114/api";   //your IP/web server address

void setup() {
  delay(1000);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}
 
void loop() {
  //Declare object of class HTTPClient
  HTTPClient http;

  //Prepare data
  String temperature, humidity, postData;
  int tmp_value=random(10, 25);
  int h_value=random(40, 80);
  temperature = String(tmp_value);
  humidity = String(h_value);
 
  //prepare request
  postData = "temperature=" + temperature + "&humidity=" + humidity ;
  http.begin(host);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(postData);
  String payload = http.getString();
 
  Serial.println(httpCode);
  Serial.println(payload);
  http.end();
  delay(5000);
}
