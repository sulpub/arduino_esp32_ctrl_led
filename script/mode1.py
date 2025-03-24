import subprocess

# Définition des commandes à exécuter
commands = [
    ["6D52D82916", "115200", "200", "2025", "0", "0", "0", "0", "0"],


    ["6D52D82916", "115200", "200", "0", "4", "0", "0", "0", "50"],
    ["6D52D82916", "115200", "200", "0", "5", "0", "0", "0", "50"],
    ["6D52D82916", "115200", "200", "0", "6", "0", "0", "0", "50"],
    ["6D52D82916", "115200", "200", "0", "8", "0", "0", "0", "50"],
    ["6D52D82916", "115200", "200", "0", "15", "0", "0", "0", "50"],
    ["6D52D82916", "115200", "200", "0", "16", "0", "0", "0", "50"],
    ["6D52D82916", "115200", "200", "0", "18", "0", "0", "0", "50"],
    ["6D52D82916", "115200", "200", "0", "21", "0", "0", "50", "0"],

]

# Script à exécuter
script_name = "script_python_ctrl_led.py"

# Exécuter chaque commande
for cmd in commands:
    full_command = ["python", script_name] + cmd
    print(f"Exécution de : {' '.join(full_command)}")
    subprocess.run(full_command)
