/**
 * \file mqttPublishExample.ino
 * \author Ulrik Eklund
 * \date 2016
 * \brief File containing example sketch for connecting arduino as a client to IBM Bluemix MQTT broker.
 * \copyright MIT license, see LICENSE.txt
 *
 * Part of this sketch is based on MQTT example code from Nick O'Leary - @knolleary
 * other parts are from arduino.cc tutorials
 */

#include <SPI.h>	/* Installed in default arduino IDE */
//#include <Ethernet.h>  /* Installed in default arduino IDE */
#include <WiFi.h>  /* Installed in default arduino IDE */

/* Install from https://github.com/knolleary/pubsubclient/releases/latest */
#include <PubSubClient.h>

/* Install from https://github.com/bblanchon/ArduinoJson */
#include <ArduinoJson.h>

/* Set this to 'true' to use terminal output, the the sketch will halt until a terminal is connected
 * Set to 'false' to just run the sketch with no serial terminal connected */
#define TERMINAL false

/* Generic definitions for all devices connected to Bluemix */
#define MQTT_PORT 1883
#define MQTT_TOPIC "iot-2/evt/status/fmt/json"
#define MQTT_SUBSCRIBE_TOPIC "iot-2/cmd/+/fmt/json"
#define MQTT_USERNAME "use-token-auth"

/* These defintions must be changed for each device
 * See https://software.intel.com/en-us/articles/connecting-to-ibm-bluemix-internet-of-things-using-mqtt 
 * for instructions on how they need to be defined */
#define MQTT_CLIENTID "d:quickstart:iotsample-arduino:78c40e01d2fe"
#define MQTT_SERVER "quickstart.messaging.internetofthings.ibmcloud.com"
#define MQTT_PASSWORD "KOJLuhiugb#76jhAGf"
#define DEVICE_ID "78c40e01d2fe"  /* not really used seprately in the MQTT comm */

/* Functions to help the structure of the code in setup() and loop() */
void callback(char* topic, byte* payload, unsigned int length);
void reconnectToBroker(void);
double getSensorValue(void);
int connectToNetwork(void);  /* Function dealing with the connection to Wifi or ethernet */

/* Update these global variables with values suitable for your network. */
//byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x03 };  /* Not used */
char ssid[] = "iot";	/* the name of the wifi network */
//char passwd[] = "Please!"

/* Global variables and instances used in multiple functions */
int status = WL_IDLE_STATUS;	/* the wifi radio's status */

WiFiClient wclient;	/* construct a wifi client based on WiFi.h */
PubSubClient client(wclient);	/* construct the object for the MQTT client based on PubSubClient.h */

//EthernetClient ethClient;	/* construct a ethernet client */
//PubSubClient client(ethClient);


void setup() 
{
  if (TERMINAL)
  {
    Serial.begin(9600);  /* Initialize the serial port */
    while (!Serial) 
    {
      ; /* wait for the port to connect. Needed only for Leonardo according to Arduino */
    }
  }
  
	connectToNetwork();	/* connect to the wifi SSID network */
	
  client.setServer(MQTT_SERVER, MQTT_PORT); /* Setting MQTT server details */
  client.setCallback(callback); /* Set callback function for subscription from MQTT broker*/
}


void loop() 
{
  /* create the payload string (should haved made a function to do this...) */
  char buffer[256];  /* character string containing the JSON payload */
  StaticJsonBuffer<200> jsonBuffer;	/* Reserve memory space for the Json buffer */
  JsonObject& payload = jsonBuffer.createObject();  /*create the payload object */
  JsonObject& data = payload.createNestedObject("d");  /* Bluemix has all data as a singe tuple {d:data} */
  data["myName"] = "Arduino Uno";  /* 1st data item */
  data["temperature"] = double_with_n_digits(getSensorValue(), 2); /* 2nd data item */
  payload.printTo(buffer, sizeof(buffer));	/* convert to buffer, which is the string to be used as the message */

  if (!client.connected())  /* client disconnected from the MQTT broker? */
  {
    reconnectToBroker();  /* if disconnected, reconnect to the broker */
  }
  
  if (client.publish(MQTT_TOPIC, buffer) && TERMINAL)  /* publish the payload in buffer[], print if ok */
  {
      Serial.print("Message published: ");
      Serial.println(buffer);
  }
  else if(TERMINAL)
  {
    Serial.println("Failed to publish MQTT message");
  }
  
  client.loop();  /* called regularly to handle incomming */
  
  delay(5000);  /* this delay defines the frequency of published messages */
}


void callback(char* topic, byte* payload, unsigned int length) 
/* This MQTT callback function is based on code from Nick O'Leary - @knolleary
 * Rewrite according to you own needs */
{
  if (TERMINAL)
  {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i=0;i<length;i++)
    {
      Serial.print((char)payload[i]);
    }
    Serial.println();
  }
}


double getSensorValue(void)
/* Fake random temperature sensor values 20-25 C
 * Rewrite according to your own needs */
{
  double t;
  
  t = 20.0 + (random(50)/10.0);
  return (t);
}


int connectToNetwork(void)
/* Quick and dirty to connect to a wifi network, based on
 * https://www.arduino.cc/en/Tutorial/ConnectNoEncryption
 * needs to be modified if using ethernet, see e.g.
 * https://www.arduino.cc/en/Tutorial/WebClient */
{
  int success = false;
  
  if (WiFi.status() == WL_NO_SHIELD)  /* check if wifi shield is present */
  {
    if (TERMINAL)
    {
      Serial.println("WiFi shield is not connected!");
    }
    while (true);  /* wait here for eternity */
  }
  
  String fv = WiFi.firmwareVersion();
	if (fv != "1.1.0")
	{
		Serial.println("Please upgrade the firmware");
	}
 

  while (status != WL_CONNECTED)	/* attempt to connect to Wifi network */
  {
    if (TERMINAL)
    {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(ssid);
    }
    status = WiFi.begin(ssid);	/* Connect to the wifi network, no password */
    delay(3000);	/* wait 3 seconds for wifi connection */
  }
	
  if (TERMINAL)
  {
    Serial.print("You're connected to SSID: ");
    Serial.println(ssid);
  }
  success = true;
  return success;
}


void reconnectToBroker(void)
/* This function is based on code from Nick O'Leary - @knolleary
 * Probably not needed to change in your own application! */
{
  while (!client.connected())  /* Loop until reconnected */
  {
    if (TERMINAL)
    {
      Serial.println("Attempting MQTT connection to broker...");
    }

    if (client.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD))	/* Attempt to connect */
    {
      if (TERMINAL)
      {
        Serial.print("Connected to ");
      	Serial.println(MQTT_SERVER);
      }
      //client.publish(MQTT_TOPIC, "hello world");	/* Once connected, publish an announcement */
      client.subscribe(MQTT_SUBSCRIBE_TOPIC);	/* resubscribe */
    } 
    else if (TERMINAL)
    {
      Serial.print("failed, rc = ");
    	Serial.print(client.state());
    	Serial.println(", try again in 5 seconds");
    }
    delay(5000);
  }
}
