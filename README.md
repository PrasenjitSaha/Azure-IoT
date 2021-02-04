# Azure-IoT-DHT11-ESP8226

<h1>Objective of this project is to send sensor data to Azure IoT Hub. </h1>
Below are the details -

**Hardware**
1.	NodeMCU 8266
![NodeMCU 8266](https://github.com/PrasenjitSaha/Azure-IoT-DHT11-ESP8226/blob/main/Introduction-to-NodeMCU-V3-2-1.png)
2.	DHT11 Temperature & Humidity sensor 
![DHT11](https://github.com/PrasenjitSaha/Azure-IoT-DHT11-ESP8226/blob/main/DHT11%E2%80%93Temperature-Sensor-Pinout.jpg)
3.	Jumper Wires
4.	Breadboard 
5.	USB Cable 

**Circuit:**
 ![Circuit Diagram](https://github.com/PrasenjitSaha/Azure-IoT-DHT11-ESP8226/blob/main/Azure%20IoT-Circuit%20Diagram.png)
 
**Prerequisite Software**
1.	Arduino IDE
•	Board Manager esp8266
•	DHT sensor library – by Adafruit 1.4.1

**Azure IoT Hub Configuration**
 1. Create IoT Hub with F1 Free Pricing
 2. Add Device from IoT Devices section

**Azure Cloud Shell SAS Generation**
az iot hub generate-sas-token --device-id {YourDeviceID} --hub-name {YourIoTHubName}
Example:  az iot hub generate-sas-token --device-id esp8266 --hub-name myioteventhub
 

**Fingerprint Generation**

* Download Open SSL binaries from https://slproweb.com/products/Win32OpenSSL.html 
* Command to generate fingerprint. 
openssl s_client -servername {IoT Hub Host Name} -connect { IoT Hub Host Name}:443 | openssl x509 -fingerprint -noout
Example:
openssl s_client -servername myioteventhub.azure-devices.net -connect myioteventhub.azure-devices.net:443 | openssl x509 -fingerprint -noout
 
Fingerprint Format: 9C:46:08:5D:55:5C:F7:83:79:0A:03:BD:DE:F4:54:F2:C9:E6:FF:9C

**IOT Hub : Send Device Event Https Post API**
POST https://fully-qualified-iothubname.azure-devices.net/devices/{id}/messages/events?api-version=2020-03-13

**Microsoft Reference Used:**
*https://docs.microsoft.com/en-us/rest/api/iothub/device/senddeviceevent
*https://docs.microsoft.com/en-us/azure/iot-hub/tutorial-connectivity#code-try-4


