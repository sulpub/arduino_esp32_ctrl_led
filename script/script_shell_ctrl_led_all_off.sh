#!/bin/bash

# Chemin vers le script control_leds.sh
CONTROL_SCRIPT="./script_shell_ctrl_led.sh"

# Paramètres pour le port série
SERIAL_PORT="/dev/ttyUSB2"
BAUD_RATE=115200
NUM_LEDS=30

$CONTROL_SCRIPT $SERIAL_PORT $BAUD_RATE $NUM_LEDS 2025 0 0 0 0

