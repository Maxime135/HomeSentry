#include <HomeSentry.h>
#include "secrets.h" // fill the fields of the "secret_template.h" file and rename it as "secret.h"
// #include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"


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

// const char * firebase_api_key = FIREBASE_API_KEY;
// const char * firebase_database_url = FIREBASE_DATABASE_URL;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

// Delay between each measurements
unsigned long startTime;
const unsigned long delayTime = 15 * 60 * 1000;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //HomeSentry object
  sentry.connectWiFi();
  // // ThingSpeak connection
  // ThingSpeak.begin(client);

  // Firebase connection
  config.api_key = FIREBASE_API_KEY;
  config.database_url = FIREBASE_DATABASE_URL;
  auth.user.email = FIREBASE_USER_EMAIL;
  auth.user.password = FIREBASE_USER_PASSWORD;
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("successfully connected to Firebase");
    signupOK = true;
  } else {
    // Serial.printf("%s\n", config.signer.signupError.message.c_str());
    Serial.print(config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

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

    // // Write a value in the ThingSpeak project
    // ThingSpeak.setField(temperatureSensorFieldNumber, temperature);
    // ThingSpeak.setField(pressureSensorFieldNumber, pressure);

    // int statusCodeWrite = ThingSpeak.writeFields(SensorChannelNumber, SensorWriteAPIKey);
    //   if(statusCodeWrite == 0){
    //   Serial.println("Channel update successful.");
    // }
    // else{
    //   Serial.println("Problem updating channel. HTTP error code " + String(statusCodeWrite));
    // }

    // Write a value in Firebase
    if (Firebase.ready() && signupOK) {

      // storing temperature
      if(Firebase.RTDB.setFloat(&fbdo, "HomeSentry_Sensor/temperature", temperature)){
        Serial.println(); Serial.print(temperature);
        Serial.print(" - successfully saved to: " + fbdo.dataPath());
        Serial.println(" (" + fbdo.dataType() + ")");
      }else{
        Serial.println("FAILED: " + fbdo.errorReason());
      }

      // storing pressure
      if(Firebase.RTDB.setFloat(&fbdo, "HomeSentry_Sensor/pressure", pressure)){
        Serial.println(); Serial.print(pressure);
        Serial.print(" - successfully saved to: " + fbdo.dataPath());
        Serial.println(" (" + fbdo.dataType() + ")");
      }else{
        Serial.println("FAILED: " + fbdo.errorReason());
      }
    }

    // Reset the start time for the next delay
    startTime = millis();
  }

}
