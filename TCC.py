import cvzone
from cvzone.HandTrackingModule import HandDetector
import cv2

cap = cv2.VideoCapture(0)
detector = HandDetector(detectionCon=1, maxHands=1)
mySerial = cvzone.SerialObject("COM4", 9600, 1)


while True:
    success, img = cap.read()
    img = detector.findHands(img)
    lmList, bbox = detector.findPosition(img)

    if lmList:
        dedos = detector.fingersUp()
        mao = detector.handType()
        print(mao)
        print(dedos)
        mySerial.sendData(dedos)



    cv2.imshow("Image", img)
    cv2.waitKey(1)
cap.release()
cv2.destroyAllWindows()