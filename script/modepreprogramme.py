import sys
import serial
import serial.tools.list_ports
import time

# Paramètres globaux
baudrate = 115200
timeout = 1  # secondes
wait_after_send_ms = 10

# Vérification de l'argument
if len(sys.argv) != 2:
    print("Usage : python modecomplet.py <valeur_de_x (0 à 100)>")
    sys.exit(1)

try:
    x = int(sys.argv[1])
    if not (0 <= x <= 100):
        raise ValueError
except ValueError:
    print("Erreur : x doit être un entier entre 0 et 100.")
    sys.exit(1)

# Recherche du port /dev/ttyUSB*
usb_ports = [
    port for port in serial.tools.list_ports.comports()
    if "ttyUSB" in port.device
]

if not usb_ports:
    print("Aucun port /dev/ttyUSB* détecté.")
    sys.exit(1)

if len(usb_ports) > 1:
    print("Plusieurs ports USB détectés. Le script utilisera uniquement le premier.")

port = usb_ports[0]
device_number = None

# Extraction du numéro de série
if "SER=" in port.hwid:
    for p in port.hwid.split():
        if p.startswith("SER="):
            device_number = p.split("SER=")[-1]
else:
    device_number = port.serial_number or "UNKNOWN"

print(f"Port : {port.device}")
print(f"Numéro de série : {device_number}")
print(f"Envoi de : 2025,{x}")

# Ouverture du port série, envoi et lecture
try:
    with serial.Serial(port.device, baudrate, timeout=timeout) as ser:
        command = f"2025,{x}\n"
        ser.write(command.encode())

        time.sleep(wait_after_send_ms / 1000)
        response = ser.readline().decode(errors='ignore').strip()

        print(f"Réponse reçue : {response if response else '[aucune réponse]'}")

except serial.SerialException as e:
    print(f"Erreur série : {e}")
