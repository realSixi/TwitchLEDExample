# TwitchLEDExample

A quick & dirty example for a ESP32 connecting to Twitch-Chat via IRC Client and setting LED Color for a WS2812b LED Stripe. 

## Usage

1. Create a `credentials.h` file in root folder:
   - define `WIFI_SSID` and `WIFI_PASSWORD` with your WIFI Credentials
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


### Used Libraries / Tools

- PlatformIO http://platformio.org/
- ArduinoIRC: https://github.com/fredimachado/ArduinoIRC
- FastLED: https://github.com/FastLED/FastLED