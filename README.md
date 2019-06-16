# led-art
LED Art Code
============

This is a repo for my LED code. I have code for your average Arduino, like the Uno, and I have code for the ESP32.

For both I use the FastLED library. For the ESP32 I use both cores and the on chip wifi capability.

My main code is a function I wrote a decade ago for the TLC5940 and converted recently to fastled. It consists of 3 sin waves, one red, one blue, one green.

By changing the properties of these sin waves, different sets of colors can be generated, either repeating regularly or offset so as to appear random. You can also prioritize certain colors.
