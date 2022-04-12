import cv2

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    # Convert the image to grayscale for easier computation
    image_grey = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)

    cascade_classifier = cv2.CascadeClassifier(
        f"{cv2.data.haarcascades}haarcascade_frontalface_default.xml")
    detected_objects = cascade_classifier.detectMultiScale(image_grey, minSize=(100, 100))

    # Draw rectangles on the detected objects
    if len(detected_objects) != 0:
        for (x, y, width, height) in detected_objects:
            print("x = ", x, end = " ")
            print("y = ", y)
            cv2.rectangle(frame, (x, y),
                        (x + height, y + width),
                        (0, 255, 0), 2)


    cv2.imshow("Webcam", frame)
    if cv2.waitKey(1) & 0xFF == 27: # use ESC to quit
        break

cap.release()
cv2.destroyAllWindows()

