#!/usr/bin/env python3

import serial
import numpy as np
import matplotlib.pyplot as plt

with serial.Serial('/dev/ttyACM0', 115200, timeout=1) as ser:
    while True:
        # Condition line read from sensor
        readout = ser.readline().decode('utf-8').replace(";\r\n","").split(";")
        if len(readout) != 64:
            continue

        data_2d = []
        data_1d = []
        
        for y in range(0, 7):
            data_1d = []

            for x in range(0, 7):
                data_1d.append(float(readout[x*8+y]))

            data_2d.append(data_1d)

        plt.imshow(data_2d, cmap="turbo", interpolation="spline36", vmin=20, vmax=40)
        plt.pause(0.01)
        plt.cla()
