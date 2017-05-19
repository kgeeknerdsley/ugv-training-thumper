#rev2, with third detection

import cv2
import numpy as np
import imutils

import smbus
import time

#open the i2c bus
bus = smbus.SMBus(1)

#give it an address
address = 0x04

#func to send value to arduino
def writeNumber(value):
  bus.write_byte(address, value)
  return -1
  
#cap camera for color detection
cap = cv2.VideoCapture(0)

#loop to get infinite loop of camera
while True:
  #reading the frame off the camera to be analyzed
  _, frame = cap.read()
  #convert to color to hsv
  hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
  
  
