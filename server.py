#!/usr/bin/env python
import time
from time import sleep
import string
import os
import serial
import eeml
import pprint

API_KEY = 'YOUR API KEY'
API_URL = '/v2/feeds/79839.xml'
port = '/dev/tty.usbserial-A600eoro'
ser = serial.Serial(port, 9600, timeout=20)

while True:
    data = ser.readline()

    if len(data) > 0:
        data = string.split(data, ':')
        pprint.pprint(data)

        try:
            print "Temperature is " + data[0] + " and lux is " + data[1]

            # Log data to cosm
            pac = eeml.Pachube(API_URL, API_KEY)
            pac.update([
                eeml.Data('Temperature', data[0], unit=eeml.Fahrenheit()),
                eeml.Data('Lux', data[1])
            ])

            pac.put() 

            sleep(10)
    
        except Exception, err:
            print "data error"

ser.close()
