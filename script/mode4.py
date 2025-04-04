import time
import serial
import serial.tools.list_ports
from script_python_ctrl_led import main

# Paramètres généraux
baudrate = 115200
led_number = 200
wait_ms = 20  # millisecondes
read_timeout = 1  # secondes

# Sélection du port USB
usb_ports = [
    port for port in serial.tools.list_ports.comports()
    if "ttyUSB" in port.device
]

if not usb_ports:
    print("Aucun port /dev/ttyUSB* détecté.")
    exit(1)

port = usb_ports[0]
device_number = None

# Récupération du numéro de série
if "SER=" in port.hwid:
    for p in port.hwid.split():
        if p.startswith("SER="):
            device_number = p.split("SER=")[-1]
else:
    device_number = port.serial_number or "UNKNOWN"

print(f"Port détecté : {port.device}")
print(f"Numéro de série détecté : {device_number}")

# Liste manuelle des commandes
params_list = [
    #all off
    (device_number, baudrate, led_number, 2025, 0, 0, 0, 0, 0),  
    
    #led du haut
    (device_number, baudrate, led_number, 0, 4, 0, 0, 0, 50),
    (device_number, baudrate, led_number, 0, 5, 0, 0, 0, 50),
    (device_number, baudrate, led_number, 0, 6, 0, 0, 0, 50),
    (device_number, baudrate, led_number, 0, 8, 0, 0, 0, 50),
    (device_number, baudrate, led_number, 0, 15, 0, 0, 0, 50),
    (device_number, baudrate, led_number, 0, 16, 0, 0, 0, 50),
    (device_number, baudrate, led_number, 0, 18, 0, 0, 0, 50),
    (device_number, baudrate, led_number, 0, 21, 0, 0, 50, 0),
    
    #led du bas
    (device_number, baudrate, led_number, 1, 3, 0, 0, 1, 0),
    (device_number, baudrate, led_number, 1, 4, 0, 0, 1, 0),
    (device_number, baudrate, led_number, 1, 5, 0, 0, 1, 0),
    (device_number, baudrate, led_number, 1, 6, 0, 0, 1, 0),
    (device_number, baudrate, led_number, 1, 7, 0, 0, 1, 0),

    (device_number, baudrate, led_number, 2, 3, 0, 0, 1, 0),
    (device_number, baudrate, led_number, 2, 4, 0, 0, 1, 0),
    (device_number, baudrate, led_number, 2, 5, 0, 0, 1, 0),
    (device_number, baudrate, led_number, 2, 6, 0, 0, 1, 0),
    (device_number, baudrate, led_number, 2, 7, 0, 0, 1, 0)
    
  
]

# Envoi et lecture UART
for params in params_list:
    print(f"\nRun : {params}")
    
    # Exécution de la commande LED
    main(*params)

    # Lecture du retour série (accusé de réception)
    try:
        with serial.Serial(port.device, baudrate, timeout=read_timeout) as ser:
            time.sleep(0.01)  # court délai pour que la réponse arrive
            response = ser.readline().decode(errors='ignore').strip()
            print(f"Ans : {response if response else '[aucune réponse]'}")
    except serial.SerialException as e:
        print(f"Erreur d'accès au port série : {e}")
    
    time.sleep(wait_ms / 1000)  # délai entre commandes
