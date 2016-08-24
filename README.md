Publishing data from an arduino device to IBM Bluemix
======
This is a template for setting up an arduino sketch to communicate with [IBM Bluemix IoT](http://www.ibm.com/cloud-computing/bluemix/internet-of-things/) using [MQTT](http://mqtt.org).

It is an alternative to the [samples from IBM](https://github.com/ibm-messaging/iot-arduino), still providing similar functionality. This sketch uses a different MQTT library, has a smaller footprint, and can also run on Arduino Due.

Features
------
- Connects an arduino card as a registered device to the IBM Bluemix IoT platform
- Uses the [pubsubclient MQTT library](http://pubsubclient.knolleary.net) by [Nick O'Leary](http://knolleary.net/about/).
- Uses the [arduinoJson library](https://github.com/bblanchon/ArduinoJson) to format the MQTT payload correctly for IBM Bluemix. You need to install these two libraries in your arduino IDE ([see instructions here](https://www.arduino.cc/en/Guide/Libraries)).
- Sketch developed for wifi (easy to convert to ethernet)
- Works on several cards, from Uno (AVR) to Due (ARM Cortex-M3)
- Fairly memory efficient (uses about 50% of the memory on Arduino Uno, 5% on Arduino Due, including all libraries)
- MIT License

Preconditions
------
It assumes that you have already registered your device, see e.g. [Connecting to IBM Bluemix* Internet of Things using MQTT](https://software.intel.com/en-us/articles/connecting-to-ibm-bluemix-internet-of-things-using-mqtt)

Setting up the parameters for the broker
------

The following information is from [Intel](https://software.intel.com/en-us/articles/connecting-to-ibm-bluemix-internet-of-things-using-mqtt), on how to communicate with IBM Bluemix as an MQTT broker, but seems to work perfectly nonetheless:

- `MQTT_SERVER` - use `\<Your organization ID\>.messaging.internetofthings.ibmcloud.com`, along with the `ssl://` (for C++) or `mqtts://` (for JavaScript*) protocol

- `MQTT_CLIENTID` - use `d:\<Your organization ID\>:\<Your device type\>:\<Your device ID\>`

- `MQTT_TOPIC` - use `iot-2/evt/status/fmt/json`

- `MQTT_USERNAME` - use `use-token-auth`

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


Found this sketch useful? Please star this project!
