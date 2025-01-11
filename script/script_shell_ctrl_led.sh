#!/bin/bash

# Configuration du port série
SERIAL_PORT=${1:-"/dev/ttyUSB2"}  # Port série utilisé, valeur par défaut : /dev/ttyUSB0
BAUD_RATE=${2:-115200}           # Vitesse de communication, valeur par défaut : 115200

# Initialiser le port série
stty -F "$SERIAL_PORT" "$BAUD_RATE" cs8 -cstopb -parenb

# Fonction pour envoyer une commande LED
send_led_command() {
    local num_leds=$1
    local band_num=$2
    local led_index=$3
    local red=$4
    local green=$5
    local blue=$6

    # Construire la commande au format attendu
    local command="${num_leds},${band_num},${led_index},${red},${green},${blue}\n"

    # Envoyer la commande sur le port série
    echo -ne "$command" > "$SERIAL_PORT"
    echo "Commande envoyée : $command"
}

# Vérifier que suffisamment d'arguments sont passés
if [ "$#" -lt 6 ]; then
    echo "Usage: $0 <serial_port> <baud_rate> <num_leds> <band_num> <led_index> <red> <green> <blue>"
    echo "Exemple : $0 /dev/ttyUSB0 115200 10 0 3 255 0 0"
    echo "Exemple : $0 /dev/ttyUSB0 115200 30 2025 0 0 0 0  -> erase all band"
    exit 1
fi

# Récupérer les arguments pour la commande LED
NUM_LEDS=$3
BAND_NUM=$4
LED_INDEX=$5
RED=$6
GREEN=$7
BLUE=$8

# Envoyer la commande
send_led_command "$NUM_LEDS" "$BAND_NUM" "$LED_INDEX" "$RED" "$GREEN" "$BLUE"
