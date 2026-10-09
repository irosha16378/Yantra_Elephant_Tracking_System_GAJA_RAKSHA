import cv2
from ultralytics import YOLO
import serial
import time

# ඔබේ නිවැරදි Bluetooth Outgoing COM Port එක මෙතනට ලබා දෙන්න
try:
    esp32 = serial.Serial(port='COM10', baudrate=115200, timeout=0.1)
    time.sleep(2) 
    print("Bluetooth Connected! GajaYanthra is Wireless now.")
except Exception as e:
    print(f"Error: {e}")
    exit()

model = YOLO('yolov8n.pt') 
cap = cv2.VideoCapture(0) 

while True:
    ret, frame = cap.read()
    if not ret: break

    results = model(frame, verbose=False)
    elephant_detected = False

    for r in results:
        for box in r.boxes:
            if int(box.cls[0]) == 20: # Elephant
                elephant_detected = True
                x1, y1, x2, y2 = map(int, box.xyxy[0])
                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 255), 3)

    if elephant_detected:
        esp32.write(b'S') 
    else:
        esp32.write(b'F') 

    cv2.imshow("GajaYanthra Bluetooth AI", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'): break

cap.release()
cv2.destroyAllWindows()
esp32.close()