#!/usr/bin/env python3
#
# Python program to run on the computer to read data coming in from
# the Serial Port and print it to standard output.
#
# Use in conjunction with the Accelerometer programs and
# plotXYZ.sh/plotAngles.sh to show live streaming data in graphical form.
#
# e.g. ReadSerial.py | plotXYZ.sh
#
# Make sure you set the serial port to match your Arduino configuration.
#
import serial
import os
import sys, getopt

serialPort='/dev/ttyUSB0'

#
# Python way of defining functions
#
def printVector(vector):
    "Print the incoming vector"
    for coord in vector:
        print(coord, end=" ")
    print()
    sys.stdout.flush()
    
def usage():
    global serialPort
    print('ReadSerial.py -s {serial port}')
    print()
    print('Receive data via the serial port and print them out')
    print()
    print('Options:')
    print("   -s {serial port} (default ", serialPort, ")")
    print()
    sys.exit(2)
    
def main(argv):
    global serialPort
    global ax
    try:
        opts, args=getopt.getopt(argv, "h:s:", ["serial="])
    except getopt.GetoptError:
        usage()
    for opt, arg in opts:
        if opt == '-h':
            usage
        elif opt in ("-s", "--serial"):
            serialPort=arg

    try:
        ser=serial.Serial(serialPort,9600,timeout=999)

        while (1 == 1):
            try:
                line=ser.readline()
                tokens=line.split()
                # print if we have more than one input item
                if len(tokens)>1:
                    # convert to floating point numbers
                    vector=[float(i) for i in tokens]
                    printVector(vector)
                    # clear the serial buffer   
                    ser.flushInput()
            except serial.serialutil.SerialException as e:
                print()
            except TypeError:
                print();
            except ValueError:
                print();
            
    except serial.serialutil.SerialException as e:
        print("Error opening serial port ", serialPort)
    except TypeError:
        print("Error in type")

if __name__ == "__main__":
    main(sys.argv[1:])
