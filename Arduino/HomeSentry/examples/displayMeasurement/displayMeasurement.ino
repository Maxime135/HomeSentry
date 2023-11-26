#include <HomeSentry.h>
#include "secrets.h" // fill the field of the "secret_template.h" file and rename it as "secret.h"

// Create an instance of the HomeSentry class called sentry.
HomeSentry sentry(SECRET_SSID, SECRET_PASS);

void setup() {
  // put your setup code here, to run once:
  sentry.connectWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:

}
