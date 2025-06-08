# Embedded-Systems-Project---LPC1769

#Objective
This project was developed for the Embedded Systems course and aims to implement an autonomous system for lighting control based on occupancy detection and ambient light levels.

Architecture
The system is based on the NXP LPCXpresso LPC1769 development board, which includes the LPC1769 microcontroller. It also integrates:

A motion detection module using the AM312 sensor

A light intensity sensor module using the BH1750 sensor

A 128 Kb non-volatile EEPROM memory with an SPI interface

A local user interface with a rotary and push-button control

An MC1602C LCD display based on the HD44780 controller

Operation
The system supports two distinct modes: Normal Mode and Maintenance Mode, and operates autonomously, starting automatically when powered on.

Normal Mode
In this mode, the system turns on the lights whenever motion is detected and the ambient light level is below a configured threshold. Detected events are logged in non-volatile memory.

When the button is pressed, the system briefly displays the date, time, and current light level on the LCD for 5 seconds. The rest of the time, the LCD remains off.

Maintenance Mode
This mode allows the user to:

Set the minimum ambient light threshold for activating the lights

Set the date and time

View stored detection logs

The system enters Maintenance Mode with a double-click of the button.

In this mode:

The rotary encoder is used to navigate the menu

Pressing the button selects the highlighted menu item

While setting the date and time:

The rotary encoder increments/decrements the selected value

Pressing the button moves to the next field or confirms the input

While setting the light threshold:

The rotary encoder adjusts the value

Pressing the button confirms and returns to the menu

While viewing logs:

The rotary encoder browses through previous/next records

Pressing the button exits the view and returns to the menu

The system saves the light threshold configuration and motion detection logs (date, time, and light level) in non-volatile memory.
