#!/bin/bash

# Chemin vers le script control_leds.sh
CONTROL_SCRIPT="./script_shell_ctrl_led.sh"

# Paramètres pour le port série
SERIAL_PORT="/dev/ttyUSB1"
BAUD_RATE=115200
NUM_LEDS=21

# Éteindre toutes les LEDs de 0 à 21
for LED_INDEX in $(seq 0 $((NUM_LEDS - 1))); do
    $CONTROL_SCRIPT $SERIAL_PORT $BAUD_RATE $NUM_LEDS $LED_INDEX 0 0 0
    sleep 0.02  # Délai de 20 ms
done
