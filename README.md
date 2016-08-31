Publishing data from an arduino device to IBM Bluemix
======
This is a template sketch for setting up an arduino card as an [MQTT](http://mqtt.org) client to communicate with an MQTT broker.

The settings are configured for [IBM Bluemix IoT](http://www.ibm.com/cloud-computing/bluemix/internet-of-things/), but the sketch should be general enough to use with other MQTT brokers (but may require some modifications).  
This is an alternative to the [sample sketches from IBM](https://github.com/ibm-messaging/iot-arduino), providing similar functionality. This sketch uses a different MQTT library, has a smaller footprint, and can also run on Arduino Due.

Look at [HiveMQ's MQTT Essentials](http://www.hivemq.com/mqtt-essentials/) for a thorough introduction.

Features
------
- Connects an Arduino card as a registered device to an MQTT broker, in particular the IBM Bluemix IoT platform
- Uses the [pubsubclient MQTT library](http://pubsubclient.knolleary.net) by [Nick O'Leary](http://knolleary.net/about/).
- Uses the [arduinoJson library](https://github.com/bblanchon/ArduinoJson) to format the MQTT payload correctly for IBM Bluemix. You need to install these two libraries in your arduino IDE ([see instructions here](https://www.arduino.cc/en/Guide/Libraries)).
- Sketch developed for wifi (easy to convert to ethernet since network connection is separated from broker connection)
- Works on several cards, from Uno (AVR) to Due (ARM Cortex-M3)
- Fairly memory efficient (uses about 50% of the memory on Arduino Uno, 5% on Arduino Due, including all libraries)
- MIT License

Preconditions
------
It assumes that you have already registered your device, see e.g. [Connecting to IBM Bluemix* Internet of Things using MQTT](https://software.intel.com/en-us/articles/connecting-to-ibm-bluemix-internet-of-things-using-mqtt)

Principal program flow
------
1. Declare the two constructors to 1) connect to wifi and 2) setting upp an MQTT client
2. Connect to the local wifi network
3. Enter broker details, such as ip-address
4. Create the message data string (this sketch uses JSON)
5. Connect client to the broker if no connection in place (with proper authentication)
6. Publish data
7. Loop() client to handle incoming messages
8. Wait
9. Repeat steps 4. to 8. ad infinitum

Setting up the parameters for the IBM Bluemix broker
------

The following information is from [Intel](https://software.intel.com/en-us/articles/connecting-to-ibm-bluemix-internet-of-things-using-mqtt), on how to communicate with IBM Bluemix as an MQTT broker, but seems to work perfectly nonetheless:

- `MQTT_SERVER` - use `\<Your organization ID\>.messaging.internetofthings.ibmcloud.com`, along with the `ssl://` (for C++) or `mqtts://` (for JavaScript*) protocol

- `MQTT_CLIENTID` - use `d:\<Your organization ID\>:\<Your device type\>:\<Your device ID\>`

- `MQTT_TOPIC` - use `iot-2/evt/status/fmt/json`. Note that in general the MQTT topic is not fixed, but Bluemix limits how the topic can be formulated.

- `MQTT_USERNAME` - use `use-token-auth` since Bluemix only relies on the token

- `MQTT_PASSWORD` - use the string with the authorization token of your device


Compatible cards
------
The sketch have been tried on

- **Uno:** Sketch uses 16 498 bytes (51%) of program storage space. Maximum is 32 256 bytes.  
Global variables use 1 056 bytes (51%) of dynamic memory, leaving 992 bytes for local variables. Maximum is 2 048 bytes.
- **Mega ADK**
- **Due:** Sketch uses 26 744 bytes (5%) of program storage space. Maximum is 524 288 bytes

Acknowledegements
------
This code is heavily inspired by

- Nick O'Learys [MQTT examples](http://pubsubclient.knolleary.net)
- [Tutorial](https://www.arduino.cc/en/Tutorial/ConnectNoEncryption) from Arduino.cc
- [Tutorial](https://developer.ibm.com/recipes/tutorials/connect-an-arduino-uno-device-to-the-ibm-internet-of-things-foundation/) from IBM


Found this sketch useful? Please star this project or drop me a note!
