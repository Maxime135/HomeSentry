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

// HomeSentry Firebase Realtime Database configuration
// Database URL: https://homesentry-default-rtdb.europe-west1.firebasedatabase.app/
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

  // HomeSentry object
  sentry.connectWiFi();

  // Keep the ThingSpeak code available if you still need it for comparison/testing.
  // ThingSpeak.begin(client);

  // Firebase connection configuration for the HomeSentry RTDB
  config.api_key = FIREBASE_API_KEY;
  config.database_url = FIREBASE_DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;

  auth.user.email = FIREBASE_USER_EMAIL;
  auth.user.password = FIREBASE_USER_PASSWORD;

  // If the Firebase Auth user already exists, signUp may fail, but the session can still
  // be initialized with Firebase.begin(). The code below keeps the legacy ThingSpeak block
  // and adds a safe Firebase setup path.
  if (strlen(FIREBASE_USER_EMAIL) > 0 && strlen(FIREBASE_USER_PASSWORD) > 0) {
    if (Firebase.signUp(&config, &auth, FIREBASE_USER_EMAIL, FIREBASE_USER_PASSWORD)) {
      Serial.println("Firebase sign-up successful.");
      signupOK = true;
    } else {
      Serial.print("Firebase sign-up warning: ");
      Serial.println(config.signer.signupError.message.c_str());
    }
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Timer initialization
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

    // Write a value in Firebase.
    // Use Firebase.ready() instead of signupOK so a valid existing user can still upload
    // even when the legacy sign-up step returns false.
    if (Firebase.ready()) {

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
