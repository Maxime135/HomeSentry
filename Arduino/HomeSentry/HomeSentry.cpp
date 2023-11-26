/*
    Arduino Library "HomeSentry"
        Aiming to monitor different sensors at Home, and upload data online.
    Maxime Boulanger, 11/26/2023
*/



#include <Arduino.h>
#include <HomeSentry.h>




// Create an instance of the ArduinoLEDMatrix class
// ArduinoLEDMatrix matrix;

// Constructor
HomeSentry::HomeSentry(const char* ssid, const char* pass) {
    // _ssid[30] = ssid;
    // _pass[30] = pass;
    strcpy(_ssid, ssid);
    strcpy(_pass, pass);
    
    // Serial.begin(9600);
    // Serial.println("matrix is getting ready...");
    // matrix.begin();                 // Initialize the LED matrix
    // Serial.println("matrix ready");
}


// Conned to WiFi function
void HomeSentry::connectWiFi() {
    //WiFi connection
    Serial.begin(9600);
    //Initialize serial and wait for port to open:
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

    // wait 5 seconds for connection:
    delay(5000);
    }

    // you're connected now, so print out the data:
    Serial.print("You're connected to the network: ");
    Serial.println(_ssid);
    // print your board's IP address:
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    matrix.begin();                 // Initialize the LED matrix
}


// Display a number with the Arduino Uno R4 WiFi board LED matrix
void HomeSentry::displayNumber(float numberToDisplay){

    // Animated text displayed
    matrix.beginDraw();
    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(150);

    // add the text
    char charArray[5];
    dtostrf(numberToDisplay, 2, 2, charArray); // Conversion from flaot to char
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(charArray);
    matrix.endText(SCROLL_LEFT);

    matrix.endDraw();
    
    // delay(2000);
}


// Display an error sign with the Arduino Uno R4 WiFi board LED matrix
void HomeSentry::displayError(){
    matrix.loadFrame(danger);
    delay(500);
}