# Arduino Scoreboard

<b style="color:red">***WORK IN PROGRESS***</b>



## Background
This project is geared to Volleyball, but should be useable for other scoring.  The basic idea is to drive a string of LEDs wrapped around a frame (cardboard or lastic) to form a grid, and drive that with and Arduino and a few buttons to create a scoreboard.

Unlike some of the other Arduino based scoreboards, there should be very little physical construction, soldering etc.

The first design will be using a full Arduino UNO and breadboard as a proof of concept.  Other designs will refine the system, like using a simple Arduino adaptor board to solder buttons, and then move to a less expensive ESP32 (vs UNO) that has more memory, wireless, and bluetooth.  Wireless and bluetooth will be used for experimenting with user configurations.

All designs will user the WS2812B LED string, that has individually addressable LEDs and is well supported with the Arduino FastLED library.

Prior to any of the hardware designs, we will create a simple C code simulator that should allow faster prototyping of firmware.


## Note about Arduino Development Environment
This project relies on build and running a helper applications to generate tables of LED position.  We are assuming that the users development system
has gcc.  If not, then the user will need to figure out how to comple the helper applications.

We have been using a simple Raspberry Pi4 system as an Ardiuno development system.  This is inexpensive and provides a Linux-based operating system.


## C Code Simulator

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

If there are configuration problems, like COLS not matching expected column count based on other parameters,
then the tester.c will not compile.

Also note, the generated section of the template, will contain comments describing the size of a physical
frame that will support this configuratio.

## Dealing with Power Limits

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

## Arduino UNO with Breadboard

TBD

## Arduino UNO and Shield

TBD

## ESP32 with Breadboard

TBD


### Reference Hardware Need

Below are links to various hardware pieces needed to build the scoreboard in this project.  The prices and links are from Amazon and will likely vary.

WS2812B LED strips come in various forms.  This is what was used here:<br>
$19.49<br>
WS2812B RGB LED Strip Light 30 Pixels/M Digital Programmable, Aclorol WS2812B Individually Addressable 16.4ft 150 5050 RGB SMD Pixels Dream Color Black PCB 5V<br>
https://www.amazon.com/Programmable-Aclorol-Individually-Addressable-Raspberry/dp/B07BKNS7DJ

Basic Arduino Setup will include the following items:
1) Arduio UNO R3:<br>
$23.00<br>
https://smile.amazon.com/Arduino-A000066-ARDUINO-UNO-R3/dp/B008GRTSV6/ref=sr_1_3?dchild=1&keywords=ARDUINO+UNO+R3&qid=1597478769&sr=8-3

2) Shield for Arduino:<br>
$6.69 for 2.<br>
HiLetgo 2pcs UNO R3 Proto Shield Prototype Expansion Board with SYB-170 Mini Breadboard Based for Arduino UNO R3 ProtoShield.<br>
https://smile.amazon.com/HiLetgo-Prototype-Expansion-Breadboard-ProtoShield/dp/B00HHYBWPO/ref=sr_1_1?dchild=1&keywords=HiLetgo+2pcs+UNO+R3+Proto+Shield+Prototype+Expansion+Board+with+SYB-170+Mini+Breadboard+Based+for+Arduino+UNO+R3+ProtoShield&qid=1597478667&sr=8-1

3) Power Cord:<br>
$9.95<br>
9V 1.5A Power Adapter, for Arduino UNO R3, Router, Kitchen Scale, Schwinn Bike, Exercise Elliptical Recumbent Upright Trainer, Crosley Cruiser Record Player, Power Supply, 5ft Cable, UL Listed<br>
https://www.amazon.com/Adapter-Arduino-Exercise-Elliptical-Recumbent/dp/B07SJRF9RT

4) Various buttons and resistors


OR buy a starter kit:<br>
$47.99<br>
REXQualis UNO R3 Complete Starter Kit w/Detailed Tutorial and UNO R3 Compatible with Arduino IDE<br>
https://smile.amazon.com/REXQualis-Complete-Development-Detailed-Tutorial/dp/B07BLV5LFY/ref=sr_1_1?dchild=1&keywords=REXQualis+UNO+R3+Complete+Starter+Kit+w%2FDetailed+Tutorial+and+UNO+R3+Compatible+with+Arduino+IDE&qid=1597479383&s=electronics&sr=1-1


### Reference Links

Base article for controlling WS2812B from an Arduino:<br>
https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/

Interesting Idea about WS2812B power consumption:<br>
https://cpldcpu.wordpress.com/2014/11/16/ws2812_length/

How to use ESP32 WiFi:<br>
https://randomnerdtutorials.com/esp32-web-server-arduino-ide/


How to use ESP32 WiFi:<br>
https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/#:~:text=One%20of%20the%20greatest%20features,it%20and%20access%20web%20pages.

Arduino Button Tutorial<br>
https://www.arduino.cc/en/tutorial/button

Ardiuno Interupt Buttons:<br>
https://create.arduino.cc/projecthub/Svizel_pritula/10-buttons-using-1-interrupt-2bd1f8


## TODO - C applicaiton

- finsh README.md
- implement button hardware/code to drive operation for scoreboard.ino
- implement side-active using led intensity of scorebaord.ino
- read settings from generate.config for generate.c
- how to share similar scoreboard display and operation code
- add other functionality like:
    - pomodora clock
    - running clock
    - other?


## Rough Notes Below

- input buttons
    - reset (via reset button)
    - side
    - plus
    - minus

- TODO: how wire up buttons


- get 150 count WS2812B led strip
- cut connector
- strip wires
- solder to allow insert in arduino -or- solder to jumper
- white-ground
- red-5V
- gree-pin7


