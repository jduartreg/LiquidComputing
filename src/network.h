#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCBoards.h>

char ssid[] = "JC"; // your network SSID (name)
char pass[] = "sound2020";

WiFiUDP Udp;                           // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(172, 20, 10, 4); // remote IP 172.20.10.4
const unsigned int outPort = 1234;     // remote port to receive OSC
const unsigned int localPort = 4321;   // local port to listen for OSC packets (actually not used for sending)

void set_wifi()
{
  // pinMode(LED_BUILTIN, OUTPUT); ///!!TEST ONLY!!!
    // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif
    /*
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
#ifdef ESP32
    Serial.println(localPort);
#else
    Serial.println(Udp.localPort());
#endif
*/
}

uint16_t osc_touch = 0;
int wind;

void touch_ON(uint16_t t)
{
    // digitalWrite(LED_BUILTIN, HIGH);
    OSCMessage msg("/ON");
    msg.add(t);
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
    // digitalWrite(LED_BUILTIN, LOW);
    // Serial.println(t);
}

OSCErrorCode error;
unsigned int ledState = LOW;

unsigned int relay1 = 0;
unsigned int relay2 = 0;
unsigned int relay3 = 0;
unsigned int relay4 = 0;
unsigned int relay5 = 0;
unsigned int relay6 = 0;
unsigned int relay7 = 0;
unsigned int relay8 = 0;

void led(OSCMessage &msg) {
  ledState = msg.getInt(0);
  // digitalWrite(LED_BUILTIN, ledState);
  Serial.print("/led: ");
  Serial.println(ledState);
}

void rel1(OSCMessage &msg) {
  relay1 = msg.getInt(0);
  oscR1 = relay1;
  Serial.print("/relay1: ");
  Serial.println(relay1);
}
void rel2(OSCMessage &msg) {
  relay2 = msg.getInt(0);
  oscR2 = relay2;
  Serial.print("/relay2: ");
  Serial.println(relay2);
}
void rel3(OSCMessage &msg) {
  relay3 = msg.getInt(0);
  oscR3 = relay3;
  Serial.print("/relay3: ");
  Serial.println(relay3);
}
void rel4(OSCMessage &msg) {
  relay4 = msg.getInt(0);
  oscR4 = relay4;
  Serial.print("/relay4: ");
  Serial.println(relay4);
}
void rel5(OSCMessage &msg) {
  relay5 = msg.getInt(0);
  oscR5 = relay5;
  Serial.print("/relay5: ");
  Serial.println(relay5);
}
void rel6(OSCMessage &msg) {
  relay6 = msg.getInt(0);
  oscR6 = relay6;
  Serial.print("/relay6: ");
  Serial.println(relay6);
}
void rel7(OSCMessage &msg) {
  relay7 = msg.getInt(0);
  oscR7 = relay7;
  Serial.print("/relay7: ");
  Serial.println(relay7);
}
void rel8(OSCMessage &msg) {
  relay8 = msg.getInt(0);
  oscR8 = relay8;
  Serial.print("/relay8: ");
  Serial.println(relay8);
}

void osc_receiver() {
  OSCMessage msg;
  int size = Udp.parsePacket();
  if (size > 0) {
    while (size--) {
      msg.fill(Udp.read());
    }
    if (!msg.hasError()) {
      msg.dispatch("/led", led);
      msg.dispatch("/relay1", rel1);
      msg.dispatch("/relay2", rel2);
      msg.dispatch("/relay3", rel3);
      msg.dispatch("/relay4", rel4);
      msg.dispatch("/relay5", rel5);
      msg.dispatch("/relay6", rel6);
      msg.dispatch("/relay7", rel7);
      msg.dispatch("/relay8", rel8);
    } else {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}