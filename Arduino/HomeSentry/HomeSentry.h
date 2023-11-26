/*
    Arduino Library "HomeSentry"
        Aiming to monitor different sensors at Home, and upload data online.
    Maxime Boulanger, 11/26/2023
*/



#ifndef HomeSentry_h
#define HomeSentry_h

#include <Arduino.h>
#include <WiFiS3.h>
#include <Arduino_LED_Matrix.h>   // Include the LED_Matrix library
#include <frames.h>               // Include a header file containing frame data
#include <string.h>
// #include "secrets.h" // fill the field of the "secret_template.h" file and rename it as "secret.h"
// #include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

class HomeSentry {
    public:
        // Quikly connect the Arduino UNO R4 WiFi board to WiFi.
        void connectWiFi();

        // WiFi status
        int status = WL_IDLE_STATUS;

        // Display a value with the Arduino LED matrix.
        void displayNumber(
            int number
        );

        // Display a danger sign with the Arduino LED matrix.
        void displayError();

        // Constructor (used to create an instance of the class)
        HomeSentry(
            const char* ssid,
            const char* pass
        ); 

    private:
        // WiFi SSID
        char _ssid[30] ;
        // WiFi password
        char _pass[30];

};


#endif