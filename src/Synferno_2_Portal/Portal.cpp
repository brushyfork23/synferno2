// Compile for Lolin D1 mini V3.1.0 ESP8266
#include "Portal.h"

Portal portal;

boolean Portal::begin() {
  Serial1.begin(9600);    // initialize serial for ESP module
  WiFi.init(&Serial1);    // initialize ESP module

  // configure soft access point
  if (!WiFi.softAPConfig(this->local_IP, this->gateway, this->subnet)) {
    return false;
  }
  // initialize access point
  if (!WiFi.softAP(this->ssid, this->password)) {
    return false;
  }
  // set host name for access point
  if (!MDNS.begin(this->hostname)) {
    return false;
  }
  this->server.on("/", this->handleRoot);
  this->server.on("/login", this->handleLogin);
  this->server.on("/offset", this->handleOffset);
  this->server.onNotFound(this->handleNotFound);
  //here the list of headers to be recorded
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  this->server.collectHeaders(headerkeys, headerkeyssize);
  this->server.begin();
  return true;
}

void Portal::update() {
  this->server.handleClient();
}

void Portal::setOffset(int offset) {
  this->offset = offset;
}

int Portal::getOffset() {
  return this->offset;
}

IPAddress Portal::getIp() {
  return WiFi.softAPIP();
}

String Portal::getHostname() {
  return this->hostname;
}

//Check if header is present and correct
boolean Portal::is_authenticated() {
  if (this->server.hasHeader("Cookie")) {
    String cookie = this->server.header("Cookie");
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      return true;
    }
  }
  return false;
}

void Portal::handleLogin() {
  portal.handleLoginInternal();
}

//login page, also called for disconnect
void Portal::handleLoginInternal() {
  String msg;
  if (this->server.hasArg("DISCONNECT")) {
    this->server.sendHeader("Location", "/login");
    this->server.sendHeader("Cache-Control", "no-cache");
    this->server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    this->server.send(301);
    return;
  }
  if (this->server.hasArg("USERNAME") && this->server.hasArg("PASSWORD")) {
    if (this->server.arg("USERNAME") == this->www_username &&  this->server.arg("PASSWORD") == this->www_password) {
      this->server.sendHeader("Location", "/");
      this->server.sendHeader("Cache-Control", "no-cache");
      this->server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      this->server.send(301);
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
  this->server.send(200, "text/html", content);
}

void Portal::handleRoot() {
  portal.handleRootInternal();
}

//root page can be accessed only if authentification is ok
void Portal::handleRootInternal() {
  String header;
  if (!is_authenticated()) {
    this->server.sendHeader("Location", "/login");
    this->server.sendHeader("Cache-Control", "no-cache");
    this->server.send(301);
    return;
  }
  String content = "<html><body><form action='/offset' method='POST'><H2>Synferno Delay Controls</H2><br>";
  content += "Offset:<select name='OFFSET'>";
  for (int i=0; i<24; i++){ // TODO: get max offset from ino
    content += "<option value='" + String(i) + "'" + (i == this->offset ? " selected" : "") + ">" + String(i) + "</option>";
  }
  content += "</select><br>";
  content += "<input type='submit' name='SUBMIT' value='Submit'></form><br></body></html>";
  this->server.send(200, "text/html", content);
}

void Portal::handleOffset() {
  portal.handleOffsetInternal();
}

void Portal::handleOffsetInternal() {
  if (!this->is_authenticated()) {
    this->server.sendHeader("Location", "/login");
    this->server.sendHeader("Cache-Control", "no-cache");
    this->server.send(301);
    return;
  }
  if (this->server.hasArg("OFFSET")) {
    // TODO: this needs to notify the ino that the offset has changed.  expose soemthing like offsetUpdated()?
    this->offset = this->server.arg("OFFSET").toInt();
  }
  this->server.sendHeader("Location", "/");
  this->server.send(301);
  return;
}

void Portal::handleNotFound() {
  portal.handleNotFoundInternal();
}

//no need authentification
void Portal::handleNotFoundInternal() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += this->server.uri();
  message += "\nMethod: ";
  message += (this->server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += this->server.args();
  message += "\n";
  for (uint8_t i = 0; i < this->server.args(); i++) {
    message += " " + this->server.argName(i) + ": " + this->server.arg(i) + "\n";
  }
  this->server.send(404, "text/plain", message);
}
