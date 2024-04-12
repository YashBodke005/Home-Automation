// Adafruit IO Analog Out Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-analog-output
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"
#if defined(ARDUINO_ARCH_ESP32)
  // ESP32Servo Library (https://github.com/madhephaestus/ESP32Servo)
  // installation: library manager -> search -> "ESP32Servo"
  #include <ESP32Servo.h>
#else
  #include <Servo.h>
#endif
/************************ Example Starts Here *******************************/

// this should correspond to a pin with PWM capability
#define servopin 12
Servo servo;
// set up the 'analog' feed
AdafruitIO_Feed *k = io.feed("k");

String key;
String password = "1234";
String in = "";
int l=0;
int angle = 0; // the current angle of servo motor
unsigned long lastTime;

void setup() {

 
   servo.attach(servopin);
  servo.write(0); // rotate servo motor to 0°
  lastTime = millis();

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'analog' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  k->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  k->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  if (angle == 90 && (millis() - lastTime) > 5000) { // 5 seconds
    angle = 0;
    servo.write(angle);
    Serial.println("Rotating Servo Motor to 0°");
  }

}

// this function is called whenever an 'analog' message
// is received from Adafruit IO. it was attached to
// the analog feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

   key = data->value();
  Serial.print("Received data: ");
  Serial.println(key);
  Serial.println(in);
  
  // convert the data to integer
   if(l<4)
    {in += key;
      l = l+1;
     }
      else if (in == password)
      {
        Serial.println("lock opened");
        Serial.println("The password is correct, rotating Servo Motor to 90°");
        angle = 90;
        servo.write(angle);
        lastTime = millis();
        l=0;
        in = "";
        
      }
     
      else
      { 
        l=0;
        in = "";
        Serial.println("Enter password again");
       }
       
     

  
}
