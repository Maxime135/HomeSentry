#include <HomeSentry.h>
#include "secrets.h" // fill the field of the "secret_template.h" file and rename it as "secret.h"


#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros



// Create an instance of the HomeSentry class called sentry.
HomeSentry sentry(SECRET_SSID, SECRET_PASS);

// Create an instance of the WiFiClient called client.
WiFiClient client;


// Temperature sensor channel details
unsigned long temperatureSensorChannelNumber = SECRET_CH_ID;
const char * temperatureSensorReadAPIKey = SECRET_READ_APIKEY;
const char * temperatureSensorWriteAPIKey = SECRET_WRITE_APIKEY;
unsigned int temperatureSensorFieldNumber = 1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //HomeSentry object
  sentry.connectWiFi();
  //ThingSpeak connection
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature = ThingSpeak.readFloatField(temperatureSensorChannelNumber, temperatureSensorFieldNumber, temperatureSensorReadAPIKey);
  Serial.print("Temperature retrieved: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  // Display the retrived temperature on the LED matrix of the board.
  sentry.displayNumber(temperature);
  delay(10000);

  sentry.displayError();

  delay(5000);
}
