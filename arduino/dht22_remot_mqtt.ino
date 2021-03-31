/*
  Simple wemos D1 mini  MQTT example
  This sketch demonstrates the capabilities of the pubsub library in combination
  with the ESP8266 board/library.
  It connects to the provided access point using dhcp, using ssid and pswd
  It connects to an MQTT server ( using mqtt_server ) then:
  - publishes "connected"+uniqueID to the [root topic] ( using topic ) 
  - subscribes to the topic "[root topic]/composeClientID()/in"  with a callback to handle
  - If the first character of the topic "[root topic]/composeClientID()/in" is an 1, 
    switch ON the ESP Led, else switch it off
  - after a delay of "[root topic]/composeClientID()/in" minimum, it will publish 
    a composed payload to 
  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. 
  
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>

// Update these with values suitable for your network.

const char* ssid = "shiddiq_ms";
const char* pswd = "kerjainTA";
const char* mqtt_server = "192.168.0.100";
const char* topic = "Shiddiq42";    // rhis is the [root topic]

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const uint16_t kIrLed=14;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino
uint16_t rawData30[115] = {3060, 9006,  544, 1544,  554, 498,  552, 498,  554, 546,  552, 514,  536, 496,  498, 576,  504, 562,  508, 550,  562, 1486,  498, 576,  558, 492,  504, 544,  498, 1588,  492, 1540,  498, 1574,  500, 550,  498, 1574,  506, 1542,  552, 1520,  498, 1574,  506, 1542,  498, 1572,  498, 1550,  582, 1488,  500, 1574,  504, 544,  498, 550,  498, 552,  496, 576,  558, 494,  580, 494,  504, 544,  500, 550,  498, 552,  496, 604,  498, 550,  498, 1574,  498, 1548,  498, 1572,  500, 1572,  504, 546,  506, 542,  500, 552,  550, 1572,  506, 544,  498, 550,  500, 550,  498, 574,  504, 546,  500, 550,  500, 550,  524, 1546,  500, 1572,  506, 1542,  526, 1572,  448};
uint16_t rawDataoff[231] = {3020, 9082,  522, 1544,  502, 550,  500, 572,  500, 576,  558, 542,  500, 548,  500, 574,  476, 574,  504, 544,  502, 1570,  504, 546,  506, 542,  502, 546,  500, 1572,  502, 548,  502, 1570,  502, 1572,  550, 1548,  502, 1546,  528, 1544,  500, 550,  500, 574,  500, 548,  506, 542,  502, 548,  500, 600,  528, 546,  502, 548,  498, 588,  490, 546,  504, 542,  502, 548,  500, 574,  474, 576,  558, 542,  508, 542,  502, 548,  500, 548,  528, 1544,  502, 548,  498, 576,  502, 546,  506, 542,  502, 548,  500, 600,  526, 548,  500, 1598,  556, 520,  524, 550,  500, 1546,  554, 546,  506, 544,  500, 550,  498, 552,  494, 580,  504, 546,  448, 1668,  2968, 9080,  522, 1548,  526, 548,  504, 544,  500, 602,  526, 550,  494, 580,  506, 544,  498, 550,  498, 552,  524, 1544,  500, 552,  498, 552,  526, 1544,  500, 552,  496, 578,  500, 548,  500, 1548,  526, 1546,  526, 1546,  506, 1542,  498, 1572,  498, 1600,  526, 1572,  508, 1540,  498, 1572,  500, 550,  498, 552,  498, 576,  502, 546,  506, 542,  498, 602,  526, 550,  498, 548,  500, 552,  496, 578,  504, 546,  498, 550,  498, 1572,  508, 1540,  528, 1596,  526, 1572,  504, 570,  526, 576,  496, 552,  498, 1548,  524, 552,  498, 552,  528, 546,  504, 544,  500, 548,  500, 552,  496, 576,  504, 548,  556, 542,  500, 1600,  526, 1572,  448};
uint16_t rawDataturbo[115] = {2994, 9080,  526, 1546,  498, 552,  496, 576,  472, 580,  496, 576,  500, 548,  474, 574,  498, 552,  498, 576,  500, 1546,  498, 554,  496, 576,  500, 1546,  498, 1574,  554, 1546,  498, 1572,  500, 550,  498, 1572,  476, 1574,  496, 1574,  498, 1572,  502, 1548,  496, 1572,  500, 1552,  524, 1544,  500, 1572,  498, 1552,  494, 576,  502, 548,  498, 550,  498, 554,  496, 576,  502, 548,  500, 550,  498, 550,  498, 556,  494, 574,  502, 1548,  524, 546,  502, 548,  498, 1550,  496, 576,  502, 546,  498, 550,  498, 1574,  502, 548,  498, 552,  498, 554,  494, 576,  502, 548,  498, 550,  498, 552,  496, 1574,  552, 1520,  526, 1546,  500, 1550,  526};

long timeBetweenMessages = 1000 * 3 * 1;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
int value = 0;

int status = WL_IDLE_STATUS;     // the starting Wifi radio's status

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pswd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '0') {
    irsend.sendRaw(rawDataoff, 231, 38); //kondisi off Send a raw data capture at 38kHz.
    digitalWrite(BUILTIN_LED, HIGH);
  } else if ((char)payload[0] == '1'){
    irsend.sendRaw(rawDataturbo, 115, 38);  //kondisi turbo Send a raw data capture at 38kHz.
    digitalWrite(BUILTIN_LED, LOW);
  } else if ((char)payload[0] == '2'){
    irsend.sendRaw(rawData30, 115, 38);  //kondisi low Send a raw data capture at 38kHz.
    delay(50); digitalWrite(BUILTIN_LED, HIGH);
    delay(50); digitalWrite(BUILTIN_LED, LOW);
    delay(50); digitalWrite(BUILTIN_LED, HIGH);
    delay(50); digitalWrite(BUILTIN_LED, LOW);
  }
}


String macToStr(const uint8_t* mac)
{
  String result;
  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);
    if (i < 5)
      result += ':';
  }
  return result;
}

String composeClientID() {
  uint8_t mac[6];
  WiFi.macAddress(mac);
  String clientId;
  clientId += "esp-";
  clientId += macToStr(mac);
  return clientId;
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    String clientId = composeClientID() ;
    clientId += "-";
    clientId += String(micros() & 0xff, 16); // to randomise. sort of

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(topic, ("connected " + composeClientID()).c_str() , true );
      // ... and resubscribe
      // topic + clientID + in
      String subscription;
      subscription += topic;
      subscription += "/pwrac";
      //subscription += composeClientID() ;
      subscription += "/#";
      client.subscribe(subscription.c_str() );
      Serial.print("subscribed to : ");
      Serial.println(subscription);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.print(" wifi=");
      Serial.print(WiFi.status());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  dht.begin();
  digitalWrite(BUILTIN_LED, LOW);
  
  irsend.begin(); 
  #if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  #else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
  #endif  // ESP8266
}

void loop() {
  // confirm still connected to mqtt server
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > timeBetweenMessages ) {
    lastMsg = now;
    /*
    ++value;
    String payload = "{\"micros\":";
    payload += micros();
    payload += ",\"counter\":";
    payload += value;
    payload += ",\"client\":";
    payload += composeClientID();
    payload += "}";
    Serial.println(payload);
    */

    // Read DHT22
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
    }
    /*
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.println(F("°C "));
    */
    String buff = "{\"T\":"+String(t)+",\"H\":"+String(h)+"}";
    
    String pubTopic;
     pubTopic += topic ;
     pubTopic += "/env/dalam1/";
     pubTopic += composeClientID();
     pubTopic += "/out";
     
    Serial.print("Publish topic: ");
    Serial.println(pubTopic);
    Serial.print("Publish message: ");
    Serial.println(buff);
    client.publish( (char*) pubTopic.c_str() , buff.c_str(), true );
  }
}
