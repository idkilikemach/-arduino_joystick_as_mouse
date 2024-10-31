import pyautogui #import pyautogui to control the mouse
import pyautogui as pg
import serial
from pyrect import BOTTOM

pyautogui.FAILSAFE = False #turn FAILSAFE off so run code without stop the code
ser = serial.Serial("COM3", 9600) #idk

while True:
    read = ser.readline().decode('ascii') #read code from arduino output
    read_output = read.split()
    y_value = read_output[0]
    x_value = read_output[1]
    mouse_click = read_output[2]

    pg.moveTo(int(x_value), int(y_value))
    if mouse_click == "0":
        pg.click(button="left")
