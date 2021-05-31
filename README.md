# TwitchLEDExample

A quick & dirty example for a ESP32 connecting to Twitch-Chat via IRC Client and setting LED Color for a WS2812b LED Stripe. 

I would not recommend this approach for production use. It's really better to use a de-centralized approach: 

- use a MQTT Server, e.g. Mosquitto as a central message broker
- use e.g. PubSubClient library to connect the ESP32 to MQTT
- use whatever you prefer to push Twitch-Messages to MQTT, e.g.:
   - Node-Red (nodejs based 'graphical' automation-system with a huge community and plugins, ready to use twitch-plugin exists)
   - write your own Twitch-to-MQTT Integration, e.g. with tmi.js, twitchlib or whatever Language you prefer :) 

## Setup

1. Create a `credentials.h` file in root folder:
   - define `WIFI_SSID` and `WIFI_PASSWORD` with your WIFI Credentials
   - see `credentials_example.h` for an example :)
2. see `src/main.cpp` to adjust `DATA_PIN` for the LEDs and `IRC_CHANNEL`:
```
#define IRC_SERVER "irc.chat.twitch.tv"
#define IRC_PORT 6667
#define IRC_CHANNEL "#sascha_lb" // Twitch Channel to join, prepend with #
String IRC_NICKNAME; //will be generated


#define DATA_PIN 16 // data PIN for WS2812
#define NUM_LEDS 5
```

3. Change the `board` in `platformio.ini`
   - Find your board at https://platformio.org/boards


## Usage

Type `!led` followed by a color into the twitch chat to change the LED Stripes color:
- `!led rot` changes color to red
- `!led grün` changes color to green
- `!led blau` changes color to blue

The commands are parsed in the `callback` function (~lines 29++), the color is being set at the begin of the `loop` function.

## Used Libraries / Tools

- PlatformIO http://platformio.org/
- ArduinoIRC: https://github.com/fredimachado/ArduinoIRC
- FastLED: https://github.com/FastLED/FastLED
