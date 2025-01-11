#!/bin/bash

# Numéro de série du port série cible (ajustez cette valeur)
TARGET_SERIAL_NUMBER="29525308F3"  # Remplacez par le numéro de série réel de votre port série

# Trouver le port série correspondant au numéro de série
SERIAL_PORT=$(ls -l /dev/serial/by-id | grep "$TARGET_SERIAL_NUMBER" | awk '{print $NF}' | sed 's|../../||')

if [ -z "$SERIAL_PORT" ]; then
    echo "Erreur : Aucun port série trouvé avec le numéro de série $TARGET_SERIAL_NUMBER"
    exit 1
fi

# Configuration du port série
BAUD_RATE=${1:-115200}           # Vitesse de communication, valeur par défaut : 115200

# Initialiser le port série
stty -F "/dev/$SERIAL_PORT" "$BAUD_RATE" cs8 -cstopb -parenb

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
    echo -ne "$command" > "/dev/$SERIAL_PORT"
    echo "Commande envoyée : $command"
}

# Vérifier que suffisamment d'arguments sont passés
if [ "$#" -lt 6 ]; then
    echo "Usage: $0 <baud_rate> <num_leds> <band_num> <led_index> <red> <green> <blue>"
    echo "Exemple : $0 115200 10 0 3 255 0 0"
    echo "Exemple : $0 115200 30 2025 0 0 0 0  -> erase all band"
    exit 1
fi

# Récupérer les arguments pour la commande LED
BAUD_RATE=$1
NUM_LEDS=$2
BAND_NUM=$3
LED_INDEX=$4
RED=$5
GREEN=$6
BLUE=$7

# Envoyer la commande
send_led_command "$NUM_LEDS" "$BAND_NUM" "$LED_INDEX" "$RED" "$GREEN" "$BLUE"
