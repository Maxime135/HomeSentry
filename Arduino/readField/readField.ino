#include <WiFiS3.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

WiFiClient client;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;

// Temperature sensor channel details
unsigned long temperatureSensorChannelNumber = SECRET_CH_ID;
const char * temperatureSensorReadAPIKey = SECRET_READ_APIKEY;
const char * temperatureSensorWriteAPIKey = SECRET_WRITE_APIKEY;
unsigned int temperatureSensorFieldNumber = 1;

void setup() {
  // put your setup code here, to run once:

  //WiFi connection
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(5000);
  }
  // you're connected now, so print out the data:
  Serial.print("You're connected to the network \n");
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  
  //ThingSpeak connection
  ThingSpeak.begin(client);



}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature = ThingSpeak.readFloatField(temperatureSensorChannelNumber, temperatureSensorFieldNumber, temperatureSensorReadAPIKey);
  Serial.println(temperature);
  //Serial.println(10);
  delay(15000);
}
