# Arduino Scoreboard

<b style="color:red">***WORK IN PROGRESS***</b>



## Background
This project is geared to Volleyball, but should be useable for other scoring.  The basic idea is drive a string of LEDs wrapped around a board to form a grid, and drive that with and Arduino and a few buttons to create a scoreboard.

Unlike some of the other Arduino based scoreboards, there should be very little physical construction, soldering etc.

The first design will be using a full Arduino UNO and bread as a proof of concept.  Other designs will refine the system, like using a simple Arduino adaptor board to solder buttons, and then move to a less expensive ESP32 (vs UNO) that has more memory, wireless, and bluetooth.  Wireless and bluetooth will be used for experimenting with user configurations.

All designs will user the WS2812B LED string, that has individually addressable LEDs and is well supported with the Arduino FastLED library.

Prior to any of the hardware designs, we will create a simple C code simulator that should allow faster prototyping of firmware.


## C code Simulator

- faster to code and test ideas
- main loop for c app
- code with setup() and loop() that can be ported to arduino .ino file


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


## TODO - C applicaiton

- simple looping, with reset, sideout, plus, minus, and display in text
- comment mapping for 150 led for a couple different directions
- create dot matric digits
- use dot matrix digits for counting
- port to ino scetch and test
