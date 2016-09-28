# TrippyShadez
Sound-reactive sunglasses

This code is designed for the Adafruit 3v Trinket microcontroller, but it is pretty easily portable to other arduino based microcontrollers.

There is a microphone, button, and 62 neopixel LEDs in my hardware setup. The button is attached to the Trinket GPIO #2 (which is Interrupt 0, so the button is declared as Input_Pullup on pin 2, but the interrupt is attached to pin 0 - this will vary by microcontroller). The microphone is attached to GPIO #3 and the Neopixels connect to GPIO #0. 

The first mode is the sound-reactive mode, which samples audio for 20 ms and sets the display peak to tell the pixels how "high" to illuminate. They reset to off after each sample window.

The second mode is the default rainbow mode from the neopixel library demo functions.

The third mode just randomly illuminates lights until resetting after a certain number of lights - it looks like Christmas lights and reminds me of Stranger Things :) 

There are a ton of other modes included that could not fit onto this microcontroller - Cylon mode, Fire (really awesome) and randomCycle (one of my favs that I really want to fit)
