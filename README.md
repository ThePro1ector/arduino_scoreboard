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
- scoreboard.c   - example template that implements a simulation of the scoreboard with ascii dump of LEDs
- scoreboard/scoreboard.ino - Arduino file that is also a template

Each file is already configured with a set of values for 150 count WS2812B LED strip.  If you want to change anything, you can alter the defines in generate.c and re-run with the templates, for example with the tester:

<pre>
rm -f ./runme
gcc generate.c -o runme
./runme tester.c
rm -f ./runme
gcc tester.c -o runme
./runme
</pre>

If there are configuration problems, like COL not matching expected column count based on other parameters,
then the tester.c will not compile.

Also note, the generated section of the template, will contain comments describing the size of a physical
frame that will support this configuratio.

## Dealing with power limits

Before building the frame and starting up the scoreboard Arduino sketch, we need to address a power limit that
is possible with the WS2812B.  It is convienent to just use the 5V supply of the Arduino UNO board to drive the
LED strip.  Unfortunately, we discovered that we cannot drive all 150 LEDs at once, even with a single color.
From observation, the limit seems to be around 80 LEDs, then the Arudino UNO resets the system.  This can be
difficult to debug, so finding the limit is important.

NOTE: Be aware that with the Arduino UNO resetting, it can be difficult to reload a new Arduino sketch.  We found
that it may require restarting/reconnecting the Arduino and some timing to reload code.

The applications power.c and power.ino can be used to experiment with your own system to find these limits.
The power.c is a simulation to help build changes to power.ino.


## Physical Frame and LED Strip

TBD

## Arduino UNO with breadboard

TBD

## Arduino UNO and Adaptor

TBD

## ESP32 with breadboard

TBD

## Rough Notes Below

- input buttons
    - on/off (on power)
    - clear all
    - side
    - add
    - sub

- TODO: how wire up 5 buttons


- get 150 count WS2812B led strip
- cut connector
- strip wires
- solder to allow insert in arduino -or- solder to jumper
- white-ground
- red-5V
- gree-pin7




### Reference Links

Base article for controlling WS2812B from an Arduino:<br>
https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/

Interesting Idea about WS2812B power consumption:<br>
https://cpldcpu.wordpress.com/2014/11/16/ws2812_length/

How to use ESP32 WiFi:<br>
https://randomnerdtutorials.com/esp32-web-server-arduino-ide/


How to use ESP32 WiFi:<br>
https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/#:~:text=One%20of%20the%20greatest%20features,it%20and%20access%20web%20pages.




## TODO - C applicaiton

- finsh README.md
- implement button hardware and .ino code to drive operation for scoreboard.ino
- implement side identification using led intensity of scorebaord.ino
- read settings from generate.config for generate.c
- how to share similar scoreboard display and operation code
- add other functionality like:
    - pomodora clock
    - running clock
    - other?

