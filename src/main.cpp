/*
 * Copyright (c) 2024/2025 Tobias Guggenberger - software@guggenberger.me
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <Ethernet.h>
#include <PubSubClient.h> // mqtt
#include "PCF8574.h" // Port Expander
#include <SPI.h> // Seriell
#include <Wire.h>

/************************************************************************** Relais Belegung
*/
const int Relai_K1 = 2; // Relais-Pin am Arduino


//************************************************************************** LAN Network definieren 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x09 };
IPAddress ip(10, 110, 0, 14); //comment this line if you are using DHCP

//IPAddress subnet(255, 255, 0, 0); // Subnet Mask

IPAddress mqtt_server(10, 110, 0, 3);  // IP-Adresse des MQTT Brokers im lokalen Netzwerk

EthernetClient ethClient;
PubSubClient client(ethClient);

//************************************************************************** Variablen
int topic_init = 0; // Topic Variable zum einmaligen aufrufen



//************************************************************************** Funktionsprototypen
void loop                       ();
void setup                      ();
void reconnect                  ();
void callback(char* topic, byte* payload, unsigned int length);
void topic_mqtt_init            ();
void mqtt_reconnect_intervall   ();
void(* resetFunc) (void) = 0;


//************************************************************************** Intervalle
/* Beispiel
unsigned long previousMillis_BEISPIEL = 0; // 
unsigned long interval_BEISPIEL = 800; 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ BEISPIEL
  if (millis() - previousMillis_BEISPIEL > interval_BEISPIEL) {
      previousMillis_BEISPIEL = millis(); 
      FUNKTION();
    }  
*/
unsigned long previousMillis_mqtt_reconnect = 0; // 
unsigned long interval_mqtt_reconnect = 200; 

//************************************************************************** SETUP
void setup() {
  Serial.begin(115200);

// ------------------------------------------------------------------------- Ethernet starten
  Ethernet.begin(mac, ip);
  // Pause Netzwerk Antwort
  delay(1500);  

///////////////////////////////////////////////////////////////////////////  MQTT Broker init
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

/////////////////////////////////////////////////////////////////////////// Port Relaisausgang deklaieren
pinMode(Relai_K1, OUTPUT); // Relais Pins als Ausgang deklarieren

}

//************************************************************************** Topic MQTT init
void topic_mqtt_init(){
/*
Durch das init der Topic wird einmalig dem System gezeigt welche Topic es gibt
Benötigte Variable
- int topic_init = 0;
*/
    if (topic_init==0)
  {
    topic_init = 1;
    // Topic init
    client.publish("Relais/001/K1", "online");
      }
}

//************************************************************************** mqtt - reconnect
void reconnect() {
  while (!client.connected()) {
    Serial.print("Verbindung zum MQTT-Server aufbauen...");
    if (client.connect("Relais001", "hitesh", "RO9UZ7wANCXzmy")) {
      Serial.println("verbunden");
      client.subscribe("Relais/001/K1");
    } else {
      Serial.print("Fehler, rc=");
      Serial.print(client.state());
      Serial.println(" erneut versuchen in 5 Sekunden");
      delay(5000);
    }
  }
}

//************************************************************************** mqtt - callback
void callback(char* topic, byte* payload, unsigned int length) {

 Serial.print("Nachricht empfangen [");
  Serial.print(topic);
  Serial.print("]: ");
  
  // Payload in einen String umwandeln
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.println(message);

// -------------------------------------------------------- Topic Auswerten K0 gruen
    if (String(topic) == "Meldungen/Warnleuchte001/gruen") {
      if (message == "on") {
          Serial.println("Relais K0 gruen -> AN");
          pcf8574.digitalWrite(P0, !HIGH);
      } 
      else if (message == "off") {
          Serial.println("Relais K0 gruen -> AUS");
          pcf8574.digitalWrite(P0, !LOW);
      } 
      else { }} else { }

// -------------------------------------------------------- Topic Auswerten K1 gelb
    if (String(topic) == "Meldungen/Warnleuchte001/gelb") {
      if (message == "on") {
          Serial.println("Relais K1 gelb -> AN");
          pcf8574.digitalWrite(P1, !HIGH);
      } 
      else if (message == "off") {
          Serial.println("Relais K1 gelb -> AUS");
          pcf8574.digitalWrite(P1, !LOW);
      } 
      else { }} else { }

// -------------------------------------------------------- Topic Auswerten K2 rot
    if (String(topic) == "Meldungen/Warnleuchte001/rot") {
      if (message == "on") {
          Serial.println("Relais K2 rot -> AN");
          pcf8574.digitalWrite(P2, !HIGH);
      } 
      else if (message == "off") {
          Serial.println("Relais K2 rot-> AUS");
          pcf8574.digitalWrite(P2, !LOW);
      } 
      else { }} else { }


// -------------------------------------------------------- Topic Auswerten K3 blau
    if (String(topic) == "Meldungen/Warnleuchte001/blau") {
      if (message == "on") {
          Serial.println("Relais K3 blau -> AN");
          pcf8574.digitalWrite(P3, !HIGH);
      } 
      else if (message == "off") {
          Serial.println("Relais K3 blau -> AUS");
          pcf8574.digitalWrite(P3, !LOW);
      } 
      else { }} else { }

// -------------------------------------------------------- Topic Auswerten K4 x1
    if (String(topic) == "Meldungen/Warnleuchte001/x1") {
      if (message == "on") {
          Serial.println("Relais K4 x1 -> AN");
          pcf8574.digitalWrite(P4, !HIGH);
      } 
      else if (message == "off") {
          Serial.println("Relais K4 x1 -> AUS");
          pcf8574.digitalWrite(P4, !LOW);
      } 
      else { }} else { }

// -------------------------------------------------------- Topic Auswerten K5 x2
    if (String(topic) == "Meldungen/Warnleuchte001/x2") {
      if (message == "on") {
          Serial.println("Relais K5 x2 -> AN");
          pcf8574.digitalWrite(P5, !HIGH);
      } 
      else if (message == "off") {
          Serial.println("Relais K5 x2 -> AUS");
          pcf8574.digitalWrite(P5, !LOW);
      } 
      else { }} else { }

// -------------------------------------------------------- Topic Auswerten K6 x3
    if (String(topic) == "Meldungen/Warnleuchte001/x3") {
      if (message == "on") {
          Serial.println("Relais K6 x3 -> AN");
          pcf8574.digitalWrite(P6, !HIGH);
      } 
      else if (message == "off") {
          Serial.println("Relais K6 x3 -> AUS");
          pcf8574.digitalWrite(P6, !LOW);
      } 
      else { }} else { }

// -------------------------------------------------------- Topic Auswerten K7 hupe
    if (String(topic) == "Meldungen/Warnleuchte001/hupe") {
      if (message == "on") {
          Serial.println("Relais K7 hupe -> AN");
          pcf8574.digitalWrite(P7, !HIGH);
      } 
      else if (message == "off") {
          Serial.println("Relais K7 hupe -> AUS");
          pcf8574.digitalWrite(P7, !LOW);
      } 
      else { }} else { }      

}



//************************************************************************** mqtt_reconnect_intervall 
void mqtt_reconnect_intervall() {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
}

//************************************************************************** LOOP
void loop() {

// MQTT Abfrage
    if (millis() - previousMillis_mqtt_reconnect > interval_mqtt_reconnect) {
      previousMillis_mqtt_reconnect = millis(); 
      mqtt_reconnect_intervall();
    }  

    
// Mqtt Topic einmalig beim Start INIT
topic_mqtt_init();

 //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Arduino Reset
if ( millis()  >= 86400000) resetFunc(); // Reset alle zwei Tage
if ( millis()  >= 30000) resetFunc(); // Reset alle zwei Tage



}