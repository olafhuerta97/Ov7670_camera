import serial
import numpy as np
import matplotlib.pyplot as plt

n_rows = 320
n_cols = 240
data_size = n_rows * n_cols

with serial.Serial('/dev/tty.usbmodem1103', 600000) as ser:
    while True:
        data = ser.read(data_size)
        matrix = np.array(list(data)).reshape((n_cols, n_rows))
        transpose = matrix.T
        plt.imshow(transpose, cmap='gray')
        plt.show()
        plt.pause(0.001)  # pause for 1 millisecond

ser.close()             # close port
