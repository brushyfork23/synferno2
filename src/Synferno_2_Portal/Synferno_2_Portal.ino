// Compile for Lolin D1 mini V3.1.0 ESP8266

// WEMOS LOLIN D1 mini (ESP8266)
// TX to Mega 19 (`RX1`)
// RX to Mega 18 (`TX1`)
// 5V to Buck Converter `+5`
// GND to GND

#define AP_SSID "synferno"
#define AP_PASS "password"
#define HOSTNAME "synferno"
#define LOCAL_IP 192,168,4,22
#define GATEWAY 192,168,4,9
#define SUBNET 255,255,255,0
#define WWW_USER "admin"
#define WWW_PASS "password"
#define MAX_OFFSET 24
#define MAX_BPM 300
#define MAX_DURATION 24

//#include <WiFi.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

ESP8266WebServer server(80);

String inString = "";    // string to hold Serial input
char inCommand;

int duration=2;
float bpm=120.0;
int offset=0;
int mode=0;


//Check if header is present and correct
boolean is_authenticated() {
  if (server.hasHeader("Cookie")) {
    String cookie = server.header("Cookie");
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      return true;
    }
  }
  return false;
}

//login page, also called for disconnect
void handleLogin() {
  String msg;
  if (server.hasArg("DISCONNECT")) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    server.send(301);
    return;
  }
  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")) {
    if (server.arg("USERNAME") == WWW_USER &&  server.arg("PASSWORD") == WWW_PASS) {
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
      return;
    }
    msg = "Wrong username/password! try again.";
  }
  String content = "<html><body><form action='/login' method='POST'>Authenticate to access controls<br>";
  content += "Username:<input type='text' name='USERNAME' placeholder='user name'><br>";
  content += "Password:<input type='password' name='PASSWORD' placeholder='password'><br>";
  content += "<input type='submit' name='SUBMIT' value='Submit'></form>";
  content += msg;
  content += "<br></body></html>";
  server.send(200, "text/html", content);
}

//root page can be accessed only if authentification is ok
void handleRoot() {
  String header;
  if (!is_authenticated()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String content = "<html><body><form action='/config' method='POST'><H2>Synferno Delay Controls</H2><br>";
  content += "Offset:<select name='OFFSET'>";
  for (int i=0; i<MAX_OFFSET; i++){
    content += "<option value='" + String(i) + "'" + (i == offset ? " selected" : "") + ">" + String(i) + "</option>";
  }
  content += "</select><br>";

  content += "Duration:<select name='DURATION'>";
  for (int i=0; i<MAX_DURATION; i++){ // TODO: get max offset from ino
    content += "<option value='" + String(i) + "'" + (i == duration ? " selected" : "") + ">" + String(i) + "</option>";
  }
  content += "</select><br>";
  
  content += "BPM:<select name='BPM'>";
  for (int i=0; i<MAX_BPM; i++){ // TODO: get max offset from ino
    content += "<option value='" + String(i) + "'" + (i == bpm ? " selected" : "") + ">" + String(i) + "</option>";
  }
  content += "</select><br>";

  content += "Mode:<select name='MODE'>";
  content += "<option value='0'";
  content += (mode == 0 ? " selected" : "");
  content += ">Midi</option>";
  content += "<option value='1'";
  content += (mode == 1 ? " selected" : "");
  content += ">Manual</option>";
  content += "</select><br>";

  content += "<input type='submit' name='SUBMIT' value='Submit'></form><br></body></html>";
  server.send(200, "text/html", content);
}

void handleConfig() {
  if (!is_authenticated()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  if (server.hasArg("OFFSET")) {
    offset = server.arg("OFFSET").toInt();
  }
  if (server.hasArg("DURATION")) {
    duration = server.arg("DURATION").toInt();
  }
  if (server.hasArg("BPM")) {
    bpm = server.arg("BPM").toInt();
  }
  if (server.hasArg("MODE")) {
    mode = server.arg("MODE").toInt();
  }
  server.sendHeader("Location", "/");
  server.send(301);

  Serial.print("O");
  Serial.println(offset);
  Serial.print("D");
  Serial.println(duration);
  Serial.print("B");
  Serial.println(bpm);
  Serial.print("M");
  Serial.println(mode);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup() {
  Serial.begin(115200);
  while(!Serial);

  // establish contact with the Mega
  if (!(connected = establishContact())) {
    // connection failed; do nothing
    while(true);
  }
  inString = "";

   // configure soft access point
  WiFi.softAPConfig(IPAddress(LOCAL_IP), IPAddress(GATEWAY), IPAddress(SUBNET));
  // initialize access point
  WiFi.softAP(AP_SSID, AP_PASS);
  // set host name for access point
  MDNS.begin(HOSTNAME);

  // configure webserver endpoints
  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/config", handleConfig);
  server.onNotFound(handleNotFound);

  //here the list of headers to be recorded
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize);
  server.begin();
}

void loop() {
  // Handle webserver requests
  server.handleClient();

  // Handle serial requests
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      inString += (char)inChar;
    }
    if (inChar != '\n') {
      inCommand = (char)inChar;
    }

    if (inChar == '\n') {
      switch (inCommand) {
        case "O":
          offset = inString.toInt();
          break;
        case "D":
          duration = inString.toInt();
          break;
        case "B":
          bpm = inString.toInt();
          break;
        case "M":
          mode = inString.toInt();
          break;
      }
      inString = "";
      inCommand = '\0';
    }
  }
}

bool establishContact() {
  while (Serial.available() <= 0) {
    Serial.print("OK?");
    delay(300);
  }
  while (Serial.available()) {
    inString += Serial.read();
  }
  return inString == "ACK";
}