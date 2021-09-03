# vim: expandtab tabstop=4 shiftwidth=4

from time import sleep
import serial

arduino = serial.Serial(port='/dev/cu.usbmodem14201', baudrate=115200, timeout=.1)

while True:
    data = arduino.readline()
    print(data)
    sleep(1)
