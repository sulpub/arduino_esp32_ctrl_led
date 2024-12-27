# Script information

## PYTHON

Send these command :

```
python script_python_ctrl_led.py /dev/ttyUSB1 115200 10 3 255 255 255
```

The pyserial library will be installed : ***pip install pyserial***


## BASH SHELL

Send these command : 
```
./script_shell_ctrl_led.sh /dev/ttyUSB1 115200  21 0 255 0 0
```
The parameters are :
 - Serial link
 - baudrate=115200
 - number of led on the strip
 - led number for control
 - Red level 0 to 255
 - Green level 0 to 255
 - Bleu level 0 to 255

***nota*** : the script will be executable with sending these command

```
sudo chmod +x script_shell_ctrl_led.sh  script_shell_ctrl_led_all_off.sh
```
