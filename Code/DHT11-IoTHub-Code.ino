//Azure IoT Hub + DHT11 + NodeMCU ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

// WiFi settings
const char* ssid = "Prasenjit Saha";
const char* password = "Prathama@123";

#define DHTPIN 2     // Digital pin connected to the DHT sensor

// Azure Setting Event Hub 
//const String AzureEventHubURI="https://{your-namespace}.servicebus.windows.net/{your-event-hub}/messages?timeout=60&api-version=2014-01"; //messages is fix and not the name of the access policy
//const String AzureEventHubFingerPrint="";
//const String AzureEventHubAuth="";

//Azure IoT Hub
//POST https://fully-qualified-iothubname.azure-devices.net/devices/{id}/messages/events?api-version=2020-03-13
const String AzureIoTHubURI="https://myioteventhub.azure-devices.net/devices/esp8266/messages/events?api-version=2020-03-13"; //messages is fix and not the name of the access policy
//openssl s_client -servername myioteventhub.azure-devices.net -connect myioteventhub.azure-devices.net:443 | openssl x509 -fingerprint -noout //Remove :
const String AzureIoTHubFingerPrint="9C:46:08:5D:55:5C:F7:83:79:0A:03:BD:DE:F4:54:F2:C9:E6:FF:9C"; //"9C46085D555CF783790A03BDDEF454F2C9E6FF9C";
//az iot hub generate-sas-token --device-id MyTestDevice --hub-name {YourIoTHubName} 
const String AzureIoTHubAuth="SharedAccessSignature sr=myioteventhub.azure-devices.net%2Fdevices%2Fesp8266&sig=yfFJLvULbwm1pJ0H18VyjSuAdBmrJg4PfWv8k0B8X4Y%3D&se=1612447403";

#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  // Init serial line
 // Serial.begin(115200);
  Serial.println("ESP8266 starting in normal mode");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Wait a few seconds between measurements.
  delay(5000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  String PostData="{ \"DeviceId\":\"ESP8266-0001\",\"Temperature\":"+String(t)+",\"Humidity\":"+String(h)+"}";
      Serial.println(PostData);
      // Send data to cloud
      int returnCode=RestPostData(AzureIoTHubURI,AzureIoTHubFingerPrint,AzureIoTHubAuth,PostData);
      Serial.println(returnCode);
}

// Functions
int RestPostData(String URI, String fingerPrint, String Authorization, String PostData)
{
    HTTPClient http;
    http.begin(URI,fingerPrint);
    http.addHeader("Authorization",Authorization);
    http.addHeader("Content-Type", "application/atom+xml;type=entry;charset=utf-8");
    int returnCode=http.POST(PostData);
    if(returnCode<0) 
  {
    Serial.println("RestPostData: Error sending data: "+String(http.errorToString(returnCode).c_str()));
  }
    http.end();
  return returnCode;
}
