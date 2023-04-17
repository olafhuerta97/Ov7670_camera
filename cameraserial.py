import serial
import numpy as np
import matplotlib.pyplot as plt
import time

n_rows = 320 #this is the row!!!
n_cols = 240 #240 h events
#n_rows = 160
#n_cols = 156 #274
data_size = n_rows * n_cols
count = 0

with serial.Serial('/dev/tty.usbmodem11103', 1000000) as ser:
    start_time = time.monotonic()
    while True:
        data = ser.read(data_size)
        matrix = np.array(list(data)).reshape((n_cols, n_rows))
        np.set_printoptions(threshold=400*400)
        transpose = matrix.T
        plt.imshow(matrix, cmap='gray')
        plt.show()
        plt.pause(0.01)
        #plt.close()
        #print(matrix)
        count += 1
        end_time = time.monotonic()
        elapsed_time = end_time - start_time
        if elapsed_time >= 1.0:  # print count and reset every second
            print(f"Executions per second: {count / elapsed_time:.2f}")
            count = 0
            start_time = time.monotonic()

ser.close()
