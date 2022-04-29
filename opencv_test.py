# import cv2

# cap = cv2.VideoCapture(0)

# while True:
#     ret, frame = cap.read()

#     # Convert the image to grayscale for easier computation
#     image_grey = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)

#     cascade_classifier = cv2.CascadeClassifier(
#         f"{cv2.data.haarcascades}haarcascade_frontalface_default.xml")
#     detected_objects = cascade_classifier.detectMultiScale(image_grey, minSize=(100, 100))

#     # Draw rectangles on the detected objects
#     if len(detected_objects) != 0:
#         for (x, y, width, height) in detected_objects:
#             print("x = ", x, end = " ")
#             print("y = ", y)
#             cv2.rectangle(frame, (x, y),
#                         (x + height, y + width),
#                         (0, 255, 0), 2)


#     cv2.imshow("Webcam", frame)
#     if cv2.waitKey(1) & 0xFF == 27: # use ESC to quit
#         break

# cap.release()
# cv2.destroyAllWindows()

import cv2
import numpy as np
 
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW) 

while 1:
    ret,frame =cap.read()
    # ret will return a true value if the frame exists otherwise False
    into_hsv =cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
    # changing the color format from BGr to HSV
    # This will be used to create the mask
    L_limit=np.array([98,50,50]) # setting the blue lower limit
    U_limit=np.array([139,255,255]) # setting the blue upper limit
    b_mask=cv2.inRange(into_hsv,L_limit,U_limit)
    im = cv2.bitwise_not(b_mask)

    
        
    # Set up the detector with default parameters.
    params = cv2.SimpleBlobDetector_Params()
    # params.filterByInertia = False
    # params.filterByConvexity = False
    params.filterByCircularity = True
    params.minCircularity = 0.7
    params.filterByArea = True
    params.minArea = 1500


    detector = cv2.SimpleBlobDetector_create(params)

    # Detect blobs.
    keypoints = detector.detect(im)
    # Draw detected blobs as red circles.
    # cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS ensures the size of the circle corresponds to the size of blob
    im_with_keypoints = cv2.drawKeypoints(im, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
    # Show keypoints
    cv2.imshow("Keypoints", im_with_keypoints)
    if len(keypoints) == 1:
        x = keypoints[0].pt[0]
        y = keypoints[0].pt[1]
        print("x = ", x, ", y = ", y)


    
    # creating the mask using inRange() function
    # this will produce an image where the color of the objects
    # falling in the range will turn white and rest will be black
    blue=cv2.bitwise_and(frame,frame,mask=b_mask)
    # this will give the color to mask.
    cv2.imshow('Original',frame) # to display the original frame
    cv2.imshow('Blue Detector',blue) # to display the blue object output
 
    if cv2.waitKey(1)==27:
        break
    # this function will be triggered when the ESC key is pressed
    # and the while loop will terminate and so will the program
cap.release()
 
cv2.destroyAllWindows()