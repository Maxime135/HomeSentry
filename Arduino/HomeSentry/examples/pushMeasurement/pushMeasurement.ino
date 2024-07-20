#include <HomeSentry.h>
#include "secrets.h" // fill the fields of the "secret_template.h" file and rename it as "secret.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros



// Create an instance of the HomeSentry class called sentry.
HomeSentry sentry(SECRET_SSID, SECRET_PASS);

// Create an instance of the WiFiClient called client.
WiFiClient client;

// Temperature sensor channel details
unsigned long SensorChannelNumber = SECRET_CH_ID;
const char * SensorReadAPIKey = SECRET_READ_APIKEY;
const char * SensorWriteAPIKey = SECRET_WRITE_APIKEY;
unsigned int temperatureSensorFieldNumber = 1;
unsigned int pressureSensorFieldNumber = 2;

// Temperature sensor Firebase details


// Delay between each measurements
unsigned long startTime;
const unsigned long delayTime = 15 * 60 * 1000;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //HomeSentry object
  sentry.connectWiFi();
  // ThingSpeak connection
  ThingSpeak.begin(client);
  //Timer initialization
  startTime = millis();
}

void loop() {

  // Check if 15 minutes have elapsed
  if (millis() - startTime >= delayTime) {

    // Mesure the actual temperature with the sensor
    float temperature = sentry.readTemperature();

    // Display the measured temperature on the LED matrix of the board
    sentry.displayNumber(temperature);

    // Mesure the actual pressure with the sensor
    float pressure = sentry.readPressure();

    // Display the measured temperature on the LED matrix of the board
    sentry.displayNumber(pressure);


    // Write a value in the ThingSpeak project
    ThingSpeak.setField(temperatureSensorFieldNumber, temperature);
    ThingSpeak.setField(pressureSensorFieldNumber, pressure);

    int statusCodeWrite = ThingSpeak.writeFields(SensorChannelNumber, SensorWriteAPIKey);
      if(statusCodeWrite == 0){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(statusCodeWrite));
    }

    // Reset the start time for the next delay
    startTime = millis();
  }

}
