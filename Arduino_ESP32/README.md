# ESP32 Arduino FastLED Code

[![ESP32 Waves Video](http://img.youtube.com/vi/hK_PNbOJsvM/0.jpg)](https://youtu.be/hK_PNbOJsvM "LED Waves")

This project uses an MQTT broker to exchange data between an Android phone and an ESP32. The ESP32 has 2 cores and built in Wifi. One of the cores is running the network code while the other is controlling the LEDs using the FastLED library. The LED strip is a WS2812b strip.

The mqtt server is mosquitto, which you can find here: https://mosquitto.org/download/ 

Mqtt is great because no server configuration is necassary when running locally. I am actually running on an AWS EC2 instance running ubuntu accessible via my site to site VPN from my home to Amazon. 
