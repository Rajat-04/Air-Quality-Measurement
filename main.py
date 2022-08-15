from datetime import datetime
from fileinput import filename
import serial
from collections import defaultdict
import os
# For importing pandas library
import pandas as pd
import csv
# For plotting thye graph
import matplotlib.pyplot as plt

# bool for csv file exists or not
csvExists, flag, close = False, True, False

headers = ['H2 MQ7', 'CO', 'ALCOHOL MQ135', 'AMMONIA NH4 MQ135', 'ACEATON MQ135',
           'LPG MQ6', 'SMOKE MQ4', 'TOULEN MQ135', 'CO2 Carboon dioxide MQ135', 'Temperature', 'Humidity %', 'Time']

filename = 'readings.csv'
plotcount = 0

# checking if csv file already exists
try:
    if os.path.exists('readings.csv'):
        csvExists = True
except:
    csvExists = False

# if the csv file doesnot exist already creating one
if(csvExists == False):
    with open('readings.csv', 'a', encoding='UTF8', newline='') as csvfile:
        filewriter = csv.writer(csvfile)
        filewriter.writerow(headers)
        csvfile.close()


def write_to_csv(data):
    try:
        with open(filename, 'a', newline='') as csvfile:
            writer = csv.DictWriter(csvfile, fieldnames=headers)
            writer.writerows(data)
            csvfile.close()
    except:
        print('Data Not Stored')

# Reading csv file using pandas

# checking for float value


def isfloat(num):
    try:
        float(num)
        return True
    except ValueError:
        return False


def getData():
    global conn, plotcount, close
    try:
        sensor_names = defaultdict(lambda: 0)
        count = 0
        val = []
        while True:
            if(count < 12):
                while(conn.inWaiting() == 0 and conn.isOpen()):
                    pass
                packet = conn.readline()
                incoming = packet.decode('utf').rstrip('\n')
                if(incoming == "1 Hour"):
                    print("1 hour triggered")
                    # adding an empty row in every 1 hour mark
                    #df.loc[df.shape[0]] = [None, None, None, None, None, None, None, None, None, None, None, None]

                if(isfloat(incoming)):
                    incoming = incoming[:-2]
                    val.append(float(incoming))
                    # updating the dict value

                if(len(val) == 11):
                    now = datetime.now()
                    current_time = now.strftime("%H:%M:%S")
                    x = [{'H2 MQ7': val[0], 'CO': val[1], 'ALCOHOL MQ135': val[2], 'AMMONIA NH4 MQ135': val[3], 'ACEATON MQ135': val[4], 'LPG MQ6': val[5],
                          'SMOKE MQ4': val[6], 'TOULEN MQ135': val[7], 'CO2 Carboon dioxide MQ135': val[8], 'Temperature': val[9], 'Humidity %': val[10], 'Time': str(current_time)}]
                    write_to_csv(x)
                    count = count+1
                    val = []
            else:
                plot(True)
                count = 0
    except:
        print("Disconnected")


# to read serial port
def main():
    global flag, conn
    try:
        conn = serial.Serial("COM12", 9600)
        getData()
    except:
        print('Port Not Connected')


def plot(val):
    if(val):
        df = pd.read_csv(filename)
        df2 = df['Time']
        df.plot(subplots=True, layout=(4,3), x='Time',sharex=False)
        plt.show(block='False')
        getData()
    else:
        main()

plot(False)