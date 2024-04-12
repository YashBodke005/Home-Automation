# Home-Automation

This project is based on making a home automation model using ESP32 board and IoT.

## Aim

To design and implement IOT based Home automation system using ESP32 and Arduino board.

## Presentation Link

https://www.canva.com/design/DAGA5_mbyiM/Hgt7a668upUMTBH3g_gjLg/view?utm_content=DAGA5_mbyiM&utm_campaign=designshare&utm_medium=link&utm_source=editor

## Introduction

In this project we have implemented a home automation system. In this we have automated four major components of any house: Security, Water system, Light system , Fire alarm using ESP32-Wroom-32 board. Security is automated by smart lock. The water management is automated using an automatic pumping system which pumps water in the tank based on the water level. Light is automated by motion sensing. A temperature sensor monitors temperature and humidity and triggers an alarm on mobile through IOT. All the four modules have automated control using Adafruit IO.

## Implementation

Following are the details of each of the four circuits

### Smart lock

In smart lock, we lock and unlock door using Adafruit IO on smartphone. Microcontroller is connected to the virtual keypad from which the password is entered. Door is unlocked if the correct password is entered. Servo motor is used as a lock and it is connected to the ESP32 which is connected to the smartphone via adafruit server.

Following is the circuit implemented for smart lock

![Smart Lock](Image/smartlockD09.png)

### Automated water pump

The water management system uses an ultrasonic sensor HCSR-04 to track water level in the tank and turn on a dc pump if water is below a near empty level and turn off if its above near full level. Water level is indicated on the device. Double channel relay module is used to operate the dc pump.

Following is the circuit of water system

![motor](Image/motorD09.png)

### Fire alarm

A DHT11 sensor is used to monitor the temperature, based on which it also alarms the user if temperature levels are high in house. Humidity levels are also monitored and displayed.

Following is the circuit of fire alarm:

![temp](Image/tempD09.png)

### IOT

All circuits are interfaced with **Adafruit io** through which user can operate and monitor the entire system.
Feeds used to control devices:

![feeds](Image/feedsD09.png)

## Conclusion

All the circuits mentioned above have been successfully simulated and implemented. **Adafruit IO** is used to implement IOT connection. Temperature sensor can be also used to control Fan or Cooler. This system can also be upgraded for AC power supply and to control real life devices using appropriate relay modules or electronic elements.

## References

[hackster.io](https://www.hackster.io/raghavdaboss/arduino-controlled-servo-door-lock-1c2239)<br>
[circuitdigest](https://circuitdigest.com/microcontroller-projects/water-level-indicator-project-using-arduino)<br>
[Adafruit IO](https://learn.adafruit.com/category/adafruit-io)
