# Arduino Scoreboard

<b style="color:red">***WORK IN PROGRESS***</b>



## Background
Mainly geared to Volleyball, but should be useable for other socring.

- using WS2812B led strip
- arduino Uno


- input buttons
    - on/off
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


## scoreboard.c

This is a simple C program used to more quickly design code changes for the scoreboard.ino file.


## scoreboard.ino

This is the Arduino scetch code to operate the Arduino UNO


## Links to be reviewed

https://randomnerdtutorials.com/esp32-web-server-arduino-ide/

https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/#:~:text=One%20of%20the%20greatest%20features,it%20and%20access%20web%20pages.


## TODO - C applicaiton

- simple looping, with reset, sideout, plus, minus, and display in text
- comment mapping for 150 led for a couple different directions
- create dot matric digits
- use dot matrix digits for counting
- port to ino scetch and test
