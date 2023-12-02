/*
    Arduino Library "HomeSentry"
        Aiming to monitor different sensors at Home, and upload data online.
    Maxime Boulanger, 11/26/2023
*/



#ifndef HomeSentry_h
#define HomeSentry_h

#include <Arduino.h>
#include <WiFiS3.h>
#include "ArduinoGraphics.h"      // To use ArduinoGraphics APIs, please include BEFORE Arduino_LED_Matrix
#include "Arduino_LED_Matrix.h"   // Include the LED_Matrix library
#include <frames.h>               // Include a header file containing frame data
#include <string.h>
// #include "secrets.h" // fill the field of the "secret_template.h" file and rename it as "secret.h"
// #include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

#include <Adafruit_BMP085.h>     // Include the Adafruit BMP085 temperature & pressure sensor


class HomeSentry {
    public:
        // Quikly connect the Arduino UNO R4 WiFi board to WiFi.
        void connectWiFi();

        // WiFi status
        int status = WL_IDLE_STATUS;

        // Display a value with the Arduino LED matrix.
        void displayNumber(
            float numberToDisplay
        );

        // Display a danger sign with the Arduino LED matrix.
        void displayError();

        // Constructor (used to create an instance of the class)
        HomeSentry(
            const char* ssid,
            const char* pass
        ); 

        // Create an instance of the ArduinoLEDMatrix class
        ArduinoLEDMatrix matrix;

        // Create an instance of the Adafruit_BMP085 class
        Adafruit_BMP085 sensorBMP085;
        float temperature1 ;
        float pressure1 ;

        // Reads the temperature from the BMP085 sensor
        float readTemperature(void);

        // Reads the pressure from the BMP085 sensor
        float readPressure(void);



    private:
        // WiFi SSID
        char _ssid[30] ;
        // WiFi password
        char _pass[30];
        // // Text displayed on the LED matrix of the board
        // char _charArrayToDisplay[20];

};


#endif