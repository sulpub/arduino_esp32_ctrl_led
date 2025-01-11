# Script information

## PYTHON

Send these command for controlling one led :

```
python script_python_ctrl_led.py "29525308F3" 115200 30 0 3 255 0 0
```

Send these command to turn off all led on all bands :

```
python script_python_ctrl_led.py "29525308F3" 115200 30 2025 0 0 0 0
```

The pyserial library will be installed : ***pip install pyserial***


## BASH SHELL

Command read serial number of COM PORTS  :

```
ls -l /dev/serial/by-id/
```

Send these command for control led strip : 

```
./script_shell_ctrl_led.sh 115200  21 0 255 0 0
```
The parameters are :
 - Serial link
 - baudrate=115200
 - number of led on the strip
 - number of the band strip led
 - led index for control
 - Red level 0 to 255
 - Green level 0 to 255
 - Bleu level 0 to 255

Send these command for turn off all led on all bands :

```
./script_shell_ctrl_led_all_off.sh
```

***nota*** : the script will be executable with sending these command

```
sudo chmod +x script_shell_ctrl_led.sh script_shell_ctrl_led_all_off.sh
```
