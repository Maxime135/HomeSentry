/*
    Arduino Library "HomeSentry"
        Aiming to monitor different sensors at Home, and upload data online.
    Maxime Boulanger, 11/26/2023
*/



#ifndef HomeSentry_h
#define HomeSentry_h

#include <Arduino.h>
#include <WiFiS3.h>
// #include "secrets.h" // fill the field of the "secret_template.h" file and rename it as "secret.h"
// #include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros


class HomeSentry {
    public:
        // Quikly connect the Arduino UNO R4 WiFi board to WiFi.
        void connectWiFi();

        // WiFi status
        int status = WL_IDLE_STATUS;

        // Display a value in the arduino LED matrix.
        void displayNumber(
            int number
        );

        // // Constructor (used to create an instance of the class)
        HomeSentry(
            char ssid,
            char pass,
        ); 

    private:
        // WiFi SSID and password
        char _ssid;
        char _pass;

}


#endif