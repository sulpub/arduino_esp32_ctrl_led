import serial
import argparse
import time
import glob
import os

def find_serial_port(target_serial_number):
    """
    Trouve le port série correspondant au numéro de série donné.

    Args:
        target_serial_number (str): Numéro de série du périphérique cible.

    Returns:
        str: Chemin du port série (ex: /dev/ttyUSB0) ou None si non trouvé.
    """
    serial_ports = glob.glob("/dev/serial/by-id/*")
    for port in serial_ports:
        if target_serial_number in port:
            return os.path.realpath(port)  # Obtenir le chemin réel (/dev/ttyUSBx)
    return None

def main(target_serial_number, baud_rate, num_leds, band_num, led_index, red, green, blue):
    # Recherche du port série basé sur le numéro de série
    serial_port = find_serial_port(target_serial_number)
    if not serial_port:
        print(f"Erreur : Aucun port série trouvé avec le numéro de série {target_serial_number}")
        return

    # Initialisation de la connexion série
    try:
        ser = serial.Serial(serial_port, baud_rate, timeout=1)
        print(f"Connecté au port {serial_port} avec un débit de {baud_rate} bauds.")
    except serial.SerialException as e:
        print(f"Erreur d'ouverture du port série : {e}")
        return

    def send_led_command(num_leds, band_num, led_index, red, green, blue):
        """
        Envoie une commande de contrôle LED sur le port série.

        Args:
            num_leds (int): Nombre total de LEDs sur la bande.
            band_num (int): Numéro de la bande LED.
            led_index (int): Index de la LED à contrôler (0 basé).
            red (int): Niveau de rouge (0-255).
            green (int): Niveau de vert (0-255).
            blue (int): Niveau de bleu (0-255).
        """
        if ser and ser.is_open:
            # Création de la commande
            command = f"{num_leds},{band_num},{led_index},{red},{green},{blue}\n"
            ser.write(command.encode())  # Envoi de la commande
            print(f"Commande envoyée : {command.strip()}")
            time.sleep(0.01)  # Pause de 10 millisecondes
        else:
            print("Erreur : Port série non ouvert.")

    # Envoi de la commande
    send_led_command(num_leds, band_num, led_index, red, green, blue)

    # Fermeture de la connexion série
    ser.close()
    print("Connexion série fermée.")

if __name__ == "__main__":
    # Configuration de l'analyse des arguments
    parser = argparse.ArgumentParser(description="Contrôler une bande de LEDs via un port série.")
    parser.add_argument("target_serial_number", type=str, help="Numéro de série du périphérique (ex: 12345678)")
    parser.add_argument("baud_rate", type=int, help="Vitesse de communication (ex : 115200)")
    parser.add_argument("num_leds", type=int, help="Nombre total de LEDs sur la bande")
    parser.add_argument("band_num", type=int, help="Numéro de la bande de LEDs")
    parser.add_argument("led_index", type=int, help="Index de la LED à contrôler (0 basé)")
    parser.add_argument("red", type=int, help="Niveau de rouge (0-255)")
    parser.add_argument("green", type=int, help="Niveau de vert (0-255)")
    parser.add_argument("blue", type=int, help="Niveau de bleu (0-255)")

    # Récupération des arguments
    args = parser.parse_args()
    main(args.target_serial_number, args.baud_rate, args.num_leds, args.band_num, args.led_index, args.red, args.green, args.blue)

#Example turn one led ON: python script_python_ctrl_led.py "29525308F3" 115200 10 0 3 255 0 0
#Example turn all OFF : python script_python_ctrl_led.py "29525308F3" 115200 10 2025 3 255 0 0
