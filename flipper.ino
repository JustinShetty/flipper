#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>


#define SERVO_PIN D1
const char* ssid = "";
const char* password = "";


ESP8266WebServer server(80);
Servo s1;

void setup(){
  s1.attach(SERVO_PIN);
  s1.write(0);
  server_init();
}

void loop(){
  server.handleClient();
}

void server_init(){
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,1);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Multicast DNS is unsupported on Windows :(
  //routes http://esp8266-server.local/ to the local IP
  if (MDNS.begin("esp8266-server", WiFi.localIP())) { 
    Serial.println("MDNS responder started");
  }

  server.on("/toggle", handleToggle);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void handleToggle(){
  String req = String(millis()) + ": ";
  req += (server.method() == HTTP_GET)?"GET":"POST";
  Serial.println(req);
  String message;
  message += "New Position: ";
  
  int pos = s1.read();
  if(pos == 180){
    s1.write(0);
    message += "0.";
  }
  else{
    s1.write(180);
    message += "180.";
  }

  server.send(200,"text/plain", message);
}

void handleNotFound(){
  String req = String(millis()) + ": ";
  req += (server.method() == HTTP_GET)?"GET":"POST";
  Serial.println(req);
  
  String message = "Unhandled Request\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
