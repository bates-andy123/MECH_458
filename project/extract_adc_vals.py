import numpy as np
import sys
import serial

try:
	filename = sys.argv[1]
except IndexError:
	filename = "default_name"

con = serial.Serial(
	port='COM3',
	baudrate=9600,
	#parity=serial.None,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS
)

data = []
k =0
i =0

max1 = 0
max2 = 0
max3 = 0


while True:
	try:
		k += 1
		i =0
		file = open(filename + '-' + str(k) + ".csv",'w')
		file.write("Reading Num, ADC value\r\n")
		while True:
			if(con.in_waiting >= 4):
				x = con.read(4)
				file.write(str(i) + ',' + x.decode("utf-8") + '\n')
				i += 1
				data.append(x)
	except KeyboardInterrupt:
		file.close()
		data = []


"""	
from msvcrt import getch
while True:
    key = ord(getch())
    elif key == 13: #Enter
        break
    elif key == 224: #Special keys (arrows, f keys, ins, del, etc.)
        key = ord(getch())
        if key == 80: #Down arrow
            moveDown()
        elif key == 72: #Up arrow
            moveUp()	

"""
			
file.close()
	
print("Mean: " + str(np.mean(data)))
print("Stddev: " + str(np.std(data)))
print("Min: " + str(np.min(data)))
print("Max: " + str(np.max(data)))