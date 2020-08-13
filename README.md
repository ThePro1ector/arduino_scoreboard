# Arduino Scoreboard

<b style="color:red">***WORK IN PROGRESS***</b>



## Background
This project is geared to Volleyball, but should be useable for other scoring.  The basic idea is drive a string of LEDs wrapped around a board to form a grid, and drive that with and Arduino and a few buttons to create a scoreboard.

Unlike some of the other Arduino based scoreboards, there should be very little physical construction, soldering etc.

The first design will be using a full Arduino UNO and breadboard as a proof of concept.  Other designs will refine the system, like using a simple Arduino adaptor board to solder buttons, and then move to a less expensive ESP32 (vs UNO) that has more memory, wireless, and bluetooth.  Wireless and bluetooth will be used for experimenting with user configurations.

All designs will user the WS2812B LED string, that has individually addressable LEDs and is well supported with the Arduino FastLED library.

Prior to any of the hardware designs, we will create a simple C code simulator that should allow faster prototyping of firmware.


## Note about Arduino Development Environment
This project relies on build and running a helper applications to generate tables of LED position.  We are assuming that the users development system
has gcc.  If not, then the user will need to figure out how to comple the helper applications.

We have been using a simple Raspberry Pi4 system as an Ardiuno development system.  This is inexpensive and provides a Linux-based operating system.


## C code Simulator

Seperating code by providing several simple applications:
- generate.c     - from given LED parameters and desired logical layout, will modifiy a given template with defines and arrays.
- tester.c       - example template file that implments and does basic testing of a simulated scoreboard
- scoreboard.c   - 
- scoreboard.ino - 


## Arduino UNO with breadboard

## Arduino UNO and Adaptor

## ESP32 with breadboard


## Rough Notes Below

- input buttons
    - on/off (on power)
    - clear all
    - side
    - add
    - sub

- TODO: how wire up 5 buttons

- output
    - string of leds, 150, 5 meters (approx 33.33 mm spacing)
    - WS2812B allows addressing each and specifiy color/intensity with RGB
    - wrap around board
    - define number leds across, number rows, and if double sided 

- get 150 count WS2812B led strip
- cut connector
- strip wires
- solder to allow insert in arduino -or- solder to jumper
- white-ground
- red-5V
- gree-pin7


### scoreboard.c

This is a simple C program used to more quickly design code changes for the scoreboard.ino file.


### scoreboard.ino

This is the Arduino scetch code to operate the Arduino UNO


### Links to be reviewed

https://randomnerdtutorials.com/esp32-web-server-arduino-ide/

https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/#:~:text=One%20of%20the%20greatest%20features,it%20and%20access%20web%20pages.

https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/


## TODO - C applicaiton

- generate.c
    - read settings from config file

- tester.c
    - change led intesity for current side

- can this be simpler with include file?  can ardiuno include c-code file?