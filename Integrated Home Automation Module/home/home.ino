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
String key;
String password = "1234";
String in = "";
int l=0;
int angle = 0; // the current angle of servo motor

unsigned long lastTime;
//Temp sensor
int tempPin=13;
float tempmin=55.0;

//ultrasonic-motor
int control = 5;
int trigPin =2;
int echoPin = 4;
long duration;
int distance;
int x;

Servo servo;
// set up the 'analog' feed
AdafruitIO_Feed *k = io.feed("k");
AdafruitIO_Feed *level = io.feed("level");
AdafruitIO_Feed *led = io.feed("led");
AdafruitIO_Feed *temperature = io.feed("temperature");


void setup() {

  servo.attach(servopin);
  servo.write(0); // rotate servo motor to 0°
  lastTime = millis();

  pinMode(control, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(tempPin, INPUT);


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
  k->onMessage(handlekey);
  led->onMessage(handleled);

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

  //motor control
   digitalWrite(control,HIGH);
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
 
  if (distance>=25)
  {
    digitalWrite(control,LOW);
     x = 1;
  }
  if (distance<25 && distance>5)
  {
     if (x==1)
    {
      digitalWrite(control,LOW);
    }
    else
    {
      digitalWrite(control,HIGH);
    }
  }
  if (distance<=10)
  {
    digitalWrite(control,HIGH);
    x=0;
  }
  
  Serial.print("sending -> ");
  Serial.println(distance);
  level->save(30-distance);
  

  int read = analogRead(tempPin);
  float voltage = read*(5./1023.);
  float temp = (voltage-0.5)*100;
  Serial.print(temp);
  Serial.println("Degree celsius");
  temperature->save(temp);
  delay(2000);

}

void handlekey(AdafruitIO_Data *data) {

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


