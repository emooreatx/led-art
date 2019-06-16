/* This code implements a simple program for generating waves of color and allowing you to customize those waves in interesting ways.
 *  It is meant to work with an mqtt broker. Here I am using an mqtt hosted in AWS and accessible via VPN from my home network, but there
 *  are many ways to host the broker. You can use a raspberry pie, or a laptop, or an android phone. The code runs without the network
 *  being available with whatever the last settings were.
 *  
 */


#include <dummy.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <FastLED.h>

#define DATA_PIN    25
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    60
#define BRIGHTNESS          255


// Replace the next variables with your SSID/Password combination
const char* ssid = "LOLBUSHWICK";
const char* password = "yourmom!";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "10.1.1.227";

WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];
int value = 0;

int blueangle = 100;
int bluelow = 50;
int bluehigh = 255;
int bluetime = 0;
int blueshift = 0;

int greenangle = 78;
int greenlow = 0;
int greenhigh = 255;
int greentime = 0;
int greenshift = 0;

int redangle = 66;
int redlow = 0;
int redhigh = 150;
int redtime = 0;
int redshift = 0;

int fadespeed = 30;
int loopspeed = 10;

int jazzhands = 0;

CRGB leds[NUM_LEDS];
int LEADLED = 0;

TaskHandle_t NetTaskHandle;

void setup() {
  Serial.begin(115200);

  Serial.println("Serial Started");

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  delay(3000);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  xTaskCreatePinnedToCore(
      NetTaskCode, /* Function to implement the task */
      "NetTaskName", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &NetTaskHandle,  /* Task handle. */
      0); /* Core where the task should run */
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
//blue
  if (String(topic) == "leds/blueangle") {
    blueangle = messageTemp.toInt();
  }
  if (String(topic) == "leds/bluelow") {
    bluelow = messageTemp.toInt();
  }
  if (String(topic) == "leds/bluehigh") {
    bluehigh = messageTemp.toInt();
  }
  if (String(topic) == "leds/bluetime") {
    bluetime = messageTemp.toInt();
  }
  if (String(topic) == "leds/blueshift") {
    blueshift = messageTemp.toInt();
  }

//red
  if (String(topic) == "leds/redangle") {
    redangle = messageTemp.toInt();
  }
  if (String(topic) == "leds/redlow") {
    redlow = messageTemp.toInt();
  }
  if (String(topic) == "leds/redhigh") {
    redhigh = messageTemp.toInt();
  }
  if (String(topic) == "leds/redtime") {
    redtime = messageTemp.toInt();
  }
  if (String(topic) == "leds/redshift") {
    redshift = messageTemp.toInt();
  }

//green  
  if (String(topic) == "leds/greenangle") {
    greenangle = messageTemp.toInt();
  }
  if (String(topic) == "leds/greenlow") {
    greenlow = messageTemp.toInt();
  }
  if (String(topic) == "leds/greenhigh") {
    greenhigh = messageTemp.toInt();
  }
  if (String(topic) == "leds/greentime") {
    greentime = messageTemp.toInt();
  }
  if (String(topic) == "leds/greenshift") {
    greenshift = messageTemp.toInt();
  }

//speeds and pattern
  if (String(topic) == "leds/fadespeed") {
    fadespeed = messageTemp.toInt();
  }
  if (String(topic) == "leds/loopspeed") {
    loopspeed = messageTemp.toInt();
  }
  if (String(topic) == "leds/jazzhands") {
    jazzhands = messageTemp.toInt();
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("leds/blueangle");
      client.subscribe("leds/bluelow");
      client.subscribe("leds/bluehigh");
      client.subscribe("leds/bluetime");
      client.subscribe("leds/blueshift");
      
      client.subscribe("leds/greenangle");
      client.subscribe("leds/greenlow");
      client.subscribe("leds/greenhigh");
      client.subscribe("leds/greentime");
      client.subscribe("leds/greenshift");
      
      client.subscribe("leds/redangle");
      client.subscribe("leds/redlow");
      client.subscribe("leds/redhigh");
      client.subscribe("leds/redtime");
      client.subscribe("leds/redshift");
      
      client.subscribe("leds/fadespeed");
      client.subscribe("leds/loopspeed");
      client.subscribe("leds/jazzhands");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
    }
  }
}
void loop() {
  delay(loopspeed);
//    if (jazzhands == 1)
//    {
      movingdot();
//    }
//    else 
//    {
//      justthewave();
//    }
}
  


void NetTaskCode( void * pvParameters ) {
  while(1) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
  }
}



void justthewave() {
  leds[0].b = beatsin8(blueangle);
  leds[0].g = beatsin8(greenangle);
  leds[0].r = beatsin8(redangle);
  memmove(leds+1, leds, (NUM_LEDS-1)*3);
  FastLED.show();
}

void movingdot() {
  leds[LEADLED].b = beatsin8(blueangle, bluelow, bluehigh, bluetime, blueshift);
  leds[LEADLED].g = beatsin8(greenangle, greenlow, greenhigh, greentime, greenshift);
  leds[LEADLED].r = beatsin8(redangle, redlow, redhigh, redtime, redshift);
  fadeToBlackBy(leds, NUM_LEDS, fadespeed);
  if (LEADLED++ >= NUM_LEDS) {
    LEADLED = 0; 
  }
  FastLED.show();
}

  
