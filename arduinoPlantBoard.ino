/*
  Arduino Plant Board

 created 25 Jul 2015
 by Manuel Lares & Juan Ramos
 
 */

#include <SPI.h>
#include <Ethernet.h>
#include <dht.h>

#define dht_dpin A3 //no ; here. Set equal to channel sensor is on

dht DHT;

float tempF;
String tempchar; //
String Hchar;
int mostureSensor =1;
int tierra;
String tierras;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "orion.lab.fi-ware.org";    // name address for Google (using DNS)
//char server[] = "www.acme.com";    // name address for Google (using DNS)



// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

 
  // if you get a connection, report back via serial:
 if (client.connect(server, 1026)) {
  //  if (client.connect(server, 80)) {

    String data;
    data = "{\"value\":\"24.0\"}";
    Serial.println("connected");
    Serial.println(data.length());
    // Make a HTTP request:
    //client.println("GET  /ngsi10/contextEntities/plant00001 HTTP/1.1");
 
    client.println("PUT  /ngsi10/contextEntities/plant00002/attributes/temperature HTTP/1.1");
    client.println("Connection: keep-alive");
    client.println("Accept: application/json");
    client.println("Content-Type: application/json");
    //client.println("Content-Type:   text/plain; charset=UTF-8");
    client.print("X-Auth-Token: "); 
    client.println("VMfS1db5lyV3mtJ7YSqAqPFHR9cu9m");
    
    //client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println(); 
    client.print(data);
   //client.println("{"value": "24.6"}");
    client.println();
       
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
    DHT.read11(dht_dpin);
   // tempchar;
    tierra = analogRead(A0);
    tierras = String(tierra);
    Serial.print("HOla");
    Serial.print(tierras);
    tempchar = String(DHT.temperature, 10);
    Serial.print(DHT.temperature);
    Serial.print(tempchar);
    delay(1000);
    String data;
    data = "{\"value\":\"" + tempchar + "\"}";
    Serial.println("connected");
    Serial.println(data.length());
    // Make a HTTP request:
    //client.println("GET  /ngsi10/contextEntities/plant00001 HTTP/1.1");
 
    client.println("PUT  /ngsi10/contextEntities/plant00002/attributes/temperature HTTP/1.1");
    client.println("Connection: keep-alive");
    client.println("Accept: application/json");
    client.println("Content-Type: application/json");
    //client.println("Content-Type:   text/plain; charset=UTF-8");
    client.print("X-Auth-Token: "); 
    client.println("VMfS1db5lyV3mtJ7YSqAqPFHR9cu9m");
    
    //client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println(); 
    client.print(data);
   //client.println("{"value": "24.6"}");
    client.println();
    delay(10000);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
     Hchar = String(DHT.humidity, 10);
    String data1;
    data1 = "{\"value\":\"" + Hchar + "\"}";
    Serial.println("connected");
    Serial.println(data1.length());
    // Make a HTTP request:
    //client.println("GET  /ngsi10/contextEntities/plant00001 HTTP/1.1");
 
    client.println("PUT  /ngsi10/contextEntities/plant00002/attributes/humedad HTTP/1.1");
    client.println("Connection: keep-alive");
    client.println("Accept: application/json");
    client.println("Content-Type: application/json");
    //client.println("Content-Type:   text/plain; charset=UTF-8");
    client.print("X-Auth-Token: "); 
    client.println("VMfS1db5lyV3mtJ7YSqAqPFHR9cu9m");
    
    //client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(data1.length());
    client.println(); 
    client.print(data1);
   //client.println("{"value": "24.6"}");
    client.println();
    delay(1000);
  
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    tierras = String(tierra);
    String data2;
    data1 = "{\"value\":\"" + tierras + "\"}";
    Serial.println("connected");
    Serial.println(data2.length());
    // Make a HTTP request:
    //client.println("GET  /ngsi10/contextEntities/plant00001 HTTP/1.1");
 
    client.println("PUT  /ngsi10/contextEntities/plant00002/attributes/tierra HTTP/1.1");
    client.println("Connection: keep-alive");
    client.println("Accept: application/json");
    client.println("Content-Type: application/json");
    //client.println("Content-Type:   text/plain; charset=UTF-8");
    client.print("X-Auth-Token: "); 
    client.println("VMfS1db5lyV3mtJ7YSqAqPFHR9cu9m");
    
    //client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(data1.length());
    client.println(); 
    client.print(data1);
   //client.println("{"value": "24.6"}");
    client.println();
    delay(1000);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////





    

  
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
  delay(1000);
}
