#include <HomeSentry.h>
#include "secrets.h" // fill the field of the "secret_template.h" file and rename it as "secret.h"

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
  float temperatureRead = ThingSpeak.readFloatField(SensorChannelNumber, temperatureSensorFieldNumber, SensorReadAPIKey);
  Serial.print("Temperature retrieved: ");
  Serial.print(temperatureRead);
  Serial.println(" °C");
  
  // Display the retrived temperature on the LED matrix of the board.
  sentry.displayNumber(temperatureRead);
  delay(3000);

  sentry.displayError();

  // Mesure the actual temperature with the sensor
  float temperature = sentry.readTemperature();

  // Display the measured temperature on the LED matrix of the board
  sentry.displayNumber(temperature);
  delay(3000);

  // Mesure the actual pressure with the sensor
  float pressure = sentry.readPressure();

  // Display the measured temperature on the LED matrix of the board
  sentry.displayNumber(pressure);
  delay(3000);

  sentry.displayError();
  delay(9000);

  // Write a value in the ThingSpeak project
  ThingSpeak.writeField(SensorChannelNumber, temperatureSensorFieldNumber, temperature, SensorWriteAPIKey);
  Serial.println("Temperature: pushed!");

  ThingSpeak.writeField(SensorChannelNumber, pressureSensorFieldNumber, pressure, SensorWriteAPIKey);
  Serial.println("Pressure: pushed!");

  delay(3000);

}
