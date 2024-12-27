import serial
import argparse

def main(serial_port, baud_rate, num_leds, led_index, red, green, blue):
    # Initialisation de la connexion série
    try:
        ser = serial.Serial(serial_port, baud_rate, timeout=1)
        print(f"Connecté au port {serial_port} avec un débit de {baud_rate} bauds.")
    except serial.SerialException as e:
        print(f"Erreur d'ouverture du port série : {e}")
        return

    def send_led_command(num_leds, led_index, red, green, blue):
        """
        Envoie une commande de contrôle LED sur le port série.

        Args:
            num_leds (int): Nombre total de LEDs sur la bande.
            led_index (int): Index de la LED à contrôler (0 basé).
            red (int): Niveau de rouge (0-255).
            green (int): Niveau de vert (0-255).
            blue (int): Niveau de bleu (0-255).
        """
        if ser and ser.is_open:
            # Création de la commande
            command = f"{num_leds},{led_index},{red},{green},{blue}\n"
            ser.write(command.encode())  # Envoi de la commande
            print(f"Commande envoyée : {command.strip()}")
        else:
            print("Erreur : Port série non ouvert.")

    # Envoi de la commande
    send_led_command(num_leds, led_index, red, green, blue)

    # Fermeture de la connexion série
    ser.close()
    print("Connexion série fermée.")

if __name__ == "__main__":
    # Configuration de l'analyse des arguments
    parser = argparse.ArgumentParser(description="Contrôler une bande de LEDs via un port série.")
    parser.add_argument("serial_port", type=str, help="Port série utilisé (ex : /dev/ttyUSB0)")
    parser.add_argument("baud_rate", type=int, help="Vitesse de communication (ex : 115200)")
    parser.add_argument("num_leds", type=int, help="Nombre total de LEDs sur la bande")
    parser.add_argument("led_index", type=int, help="Index de la LED à contrôler (0 basé)")
    parser.add_argument("red", type=int, help="Niveau de rouge (0-255)")
    parser.add_argument("green", type=int, help="Niveau de vert (0-255)")
    parser.add_argument("blue", type=int, help="Niveau de bleu (0-255)")

    # Récupération des arguments
    args = parser.parse_args()
    main(args.serial_port, args.baud_rate, args.num_leds, args.led_index, args.red, args.green, args.blue)
