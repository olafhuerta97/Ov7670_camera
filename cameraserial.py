import serial
import numpy as np
import matplotlib.pyplot as plt


n_rows = 320
n_cols = 240
#n_rows = 174
#n_cols = 144
matrix = [[0 for j in range(n_cols)] for i in range(n_rows)]


ser = serial.Serial('COM4',460800)  # open serial port
print(ser.name)    
z= 0

for y in range(n_cols):
    #print(z)
    for x in range(n_rows):
        in_bin = ser.read(1)
        in_hex = hex(int.from_bytes(in_bin,byteorder='little')) 
        matrix[x][y] = float.fromhex(in_hex)
        z= z+1


print(matrix)
transpose = [list(row) for row in zip(*matrix)]
plt.imshow(transpose, cmap='gray')  # cmap is optional, it sets the color map

plt.show()


ser.close()             # close port