/*
    Arduino Library "HomeSentry"
        Aiming to monitor different sensors at Home, and upload data online.
    Maxime Boulanger, 11/26/2023
*/



#include <Arduino.h>
#include <HomeSentry.h>


// Constructor
HomeSentry::HomeSentry(char ssid, char pass) {
    _ssid[] = ssid;
    -pass[] = pass;
}


// Conned to WiFi function

void HomeSentry::connectWiFi() {
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
    Serial.println(_ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(_ssid, _pass);

    // wait 3 seconds for connection:
    delay(3000);
}


// Display a number on the Arduino Uno R4 WiFi board LED matrix

void HomeSentry::displayNumber(int number){
    //ToDo: design the function
    Serial.println(number);
}
