#!/usr/bin/env python3
import cv2
import numpy as np

dispW=640
dispH=480
flip=2
# camSet='nvarguscamerasrc !  video/x-raw(memory:NVMM), width=3264, height=2464, format=NV12, framerate=21/1 ! nvvidconv flip-method='+str(flip)+' ! video/x-raw, width='+str(dispW)+', height='+str(dispH)+', format=BGRx ! videoconvert ! video/x-raw, format=BGR ! appsink'
# cam= cv2.VideoCapture(camSet)

#Or, if you have a WEB cam, uncomment the next line
cam=cv2.VideoCapture(0)

## Windows
cv2.namedWindow("cameraFeed")
cv2.moveWindow("cameraFeed",0,0)

cv2.namedWindow("maskOutput")
cv2.moveWindow("maskOutput",650,0)

# Hue 0-179
cv2.createTrackbar("h","cameraFeed",0,179,lambda x:None)
cv2.createTrackbar("H","cameraFeed",179,179,lambda x:None)

# Saturation 0-255
cv2.createTrackbar("s","cameraFeed",100,255,lambda x:None)
cv2.createTrackbar("S","cameraFeed",255,255,lambda x:None)

# Value 0-255
cv2.createTrackbar("v","cameraFeed",100,255,lambda x:None)
cv2.createTrackbar("V","cameraFeed",255,255,lambda x:None)


while True:
    ## Get image from camera
    ret, camFeed = cam.read()
    
    ## Convert image to HSV
    hsv=cv2.cvtColor(camFeed,cv2.COLOR_BGR2HSV)

    ## Get values from trackbars
    h = cv2.getTrackbarPos("h","cameraFeed")
    H = cv2.getTrackbarPos("H","cameraFeed")
    s = cv2.getTrackbarPos("s","cameraFeed")
    S = cv2.getTrackbarPos("S","cameraFeed")
    v = cv2.getTrackbarPos("v","cameraFeed")
    V = cv2.getTrackbarPos("V","cameraFeed")
 
    ## Mask => Foreground
    foregdMask = cv2.inRange(hsv,(h,s,v),(H,S,V))
    foregd = cv2.bitwise_and(camFeed,camFeed,mask=foregdMask)

    ## Invert Mask => Background
    backgdMask = cv2.bitwise_not(foregdMask)
    backgd = cv2.cvtColor(backgdMask,cv2.COLOR_GRAY2BGR)
    backgd = cv2.add(backgd,foregd)
    # backgd = cv2.bitwise_and(camFeed,backgd,mask=backgdMask)

    ## Stack images vertically
    stacked = np.vstack((foregd,backgd))
    stacked = cv2.resize(stacked,(640,700))

    ## Show 
    cv2.imshow('maskOutput',stacked)
    cv2.imshow('cameraFeed',camFeed)

    if cv2.waitKey(1)==ord('q'):
        break
cam.release()
cv2.destroyAllWindows()