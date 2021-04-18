# Azure IoT Experiment with DHT11 & NodeMCU ESP8226

Objective of this project is to send sensor data to Azure IoT Hub. <br/>

You can watch my video on YouTube : https://www.youtube.com/watch?v=A0xrhWByCtc

**Architecture**
![Arch](https://github.com/PrasenjitSaha/Azure-IoT-DHT11-ESP8226/blob/main/Images/Azure%20IoT-Copy%20of%20Architecture.png)<br/>

Below are the details -<br/>

**Hardware**
1.	NodeMCU 8266 <br/>
<img src="https://github.com/PrasenjitSaha/Azure-IoT-DHT11-ESP8226/blob/main/Images/Introduction-to-NodeMCU-V3-2-1.png" width="400" height="300" />
2.	DHT11 Temperature & Humidity sensor <br/>
<img src="https://github.com/PrasenjitSaha/Azure-IoT-DHT11-ESP8226/blob/main/Images/DHT11%E2%80%93Temperature-Sensor-Pinout.jpg" width="300" height="200" /><br/>
3.	Jumper Wires<br/>
4.	Breadboard <br/>
5.	USB Cable <br/>

**Circuit:** <br/>
 ![Circuit Diagram](https://github.com/PrasenjitSaha/Azure-IoT-DHT11-ESP8226/blob/main/Images/Azure%20IoT-Circuit%20Diagram.png) <br/>
 
**Prerequisite Software**  <br/>
•	Arduino IDE <br/>
•	Board Manager congigured with esp8266  <br/>
•	DHT sensor library(by Adafruit 1.4.1) installation  <br/>

**Azure IoT Hub Configuration**
 1. Create IoT Hub with F1 Free Pricing
 2. Add Device from IoT Devices section

**Azure Cloud Shell SAS Generation**
- az iot hub generate-sas-token --device-id {YourDeviceID} --hub-name {YourIoTHubName}
- Example:  az iot hub generate-sas-token --device-id esp8266 --hub-name myioteventhub
 

**Fingerprint Generation**
Youtube Video Link: https://www.youtube.com/watch?v=FbOlSMrM-BE

* Download Open SSL binaries from https://slproweb.com/products/Win32OpenSSL.html <br />
* Command to generate fingerprint. <br />
openssl s_client -servername {IoT Hub Host Name} -connect { IoT Hub Host Name}:443 | openssl x509 -fingerprint -noout <br /><br />

Example:<br />
openssl s_client -servername myioteventhub.azure-devices.net -connect myioteventhub.azure-devices.net:443 | openssl x509 -fingerprint -noout <br />
<br /> 
Fingerprint Format: 9S:89:07:5D:55:5C:F7:56:79:0A:03:BD:DE:F4:54:F2:C9:E3:FF:9C

**IOT Hub : Send Device Event Https Post API**
* POST https://fully-qualified-iothubname.azure-devices.net/devices/{id}/messages/events?api-version=2020-03-13

**Microsoft Reference Used:**
* https://docs.microsoft.com/en-us/rest/api/iothub/device/senddeviceevent
* https://docs.microsoft.com/en-us/azure/iot-hub/tutorial-connectivity#code-try-4


