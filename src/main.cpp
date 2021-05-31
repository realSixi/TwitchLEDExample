#include <Arduino.h>
#include <FastLED.h>
#include <IRCClient.h>
#include <WiFi.h>

#include "../credentials.h"

#define IRC_SERVER "irc.chat.twitch.tv"
#define IRC_PORT 6667
#define IRC_CHANNEL "#sascha_lb"
String IRC_NICKNAME;

#define DATA_PIN 16
#define NUM_LEDS 5

WiFiClient wifiClient;
IRCClient client(IRC_SERVER, IRC_PORT, wifiClient);

CRGB leds[NUM_LEDS];

CRGB color;

void callback(IRCMessage ircMessage) {
  // PRIVMSG ignoring CTCP messages
  if (ircMessage.command == "PRIVMSG" && ircMessage.text[0] != '\001') {
    String message("<" + ircMessage.nick + "> " + ircMessage.text);
    Serial.println(message);

    if (String(ircMessage.text).startsWith("!led")) {
      String colorStr = String(ircMessage.text);
      colorStr.replace("!led ", "");

      if (colorStr == "rot") {
        color = CRGB::Red;
      } else if (colorStr == "grün") {
        color = CRGB::Green;
      } else if (colorStr == "blau") {
        color = CRGB::Blue;
      }
    }

    return;
  }
  Serial.println(ircMessage.original);
}

void debugSentCallback(String data) { Serial.println(data); }

void setup() {
  Serial.begin(115200);

  // generate random string and prepend 'justinfan' for anonymous twitch login
  IRC_NICKNAME = "justinfan" + String(random(1000000, 9999999));

  Serial.println("Connecting to Wifi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (!WiFi.isConnected()) {
    Serial.print(".");
    delay(50);
  }

  Serial.println(" Done!");

  client.setCallback(callback);
  client.setSentCallback(debugSentCallback);

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  FastLED.showColor(color);
  FastLED.show();

  if (!client.connected()) {
    Serial.println("Attempting IRC connection...");
    // Attempt to connect

    if (client.connect(IRC_NICKNAME, "")) {
      client.sendRaw("JOIN " + String(IRC_CHANNEL));

      Serial.println("connected");
    } else {
      Serial.println("failed... try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
    return;
  }

  client.loop();
}
