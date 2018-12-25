#ifndef Portal_h
#define Portal_h


#define AP_SSID "synferno"
#define AP_PASS "password"
#define HOSTNAME "synferno"
#define LOCAL_IP 192,168,4,22
#define GATEWAY 192,168,4,9
#define SUBNET 255,255,255,0
#define WWW_USER "admin";
#define WWW_PASS "password";

#include <Arduino.h>

//#include <WiFi.h>
#include "WiFiEsp.h"
#include <WebServer.h>
#include <ESPmDNS.h>

class Portal{
  public:
    Portal() : server(80), local_IP(LOCAL_IP), gateway(GATEWAY), subnet(SUBNET) {}
    boolean begin();
    void update();
    IPAddress getIp();
    String getHostname();
    void setOffset(int offset);
    int getOffset();

  private:
    const char* ssid = AP_SSID;
    const char* password = AP_PASS;
    const char* hostname = HOSTNAME;
    const char* www_username = WWW_USER;
    const char* www_password = WWW_PASS;
    
    WebServer server;
    IPAddress local_IP;
    IPAddress gateway;
    IPAddress subnet;
    int offset;

    static void handleRoot();
    static void handleLogin();
    static void handleOffset();
    static void handleNotFound();
    void handleRootInternal();
    void handleLoginInternal();
    void handleOffsetInternal();
    void handleNotFoundInternal();
    boolean is_authenticated();
};

extern Portal portal;

#endif
