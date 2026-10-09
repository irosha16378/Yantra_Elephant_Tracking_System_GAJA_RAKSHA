import os
import cv2
import serial
import time
from ultralytics import YOLO

# Determine relative paths
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
CUSTOM_MODEL = os.path.join(BASE_DIR, 'models', 'best.pt')
DEFAULT_MODEL = os.path.join(BASE_DIR, 'models', 'yolov8n.pt')

MODEL_PATH = CUSTOM_MODEL if os.path.exists(CUSTOM_MODEL) else DEFAULT_MODEL

# Serial / Bluetooth Configuration
COM_PORT = 'COM10'
BAUD_RATE = 115200

print(f"[INFO] Loading AI model: {MODEL_PATH}")
model = YOLO(MODEL_PATH)

# Initialize Bluetooth Serial connection
try:
    esp32 = serial.Serial(port=COM_PORT, baudrate=BAUD_RATE, timeout=0.1)
    time.sleep(2) 
    print(f"[INFO] Bluetooth Connected on {COM_PORT}! GajaYanthra is active.")
except Exception as e:
    print(f"[WARNING] Bluetooth connection failed on {COM_PORT}: {e}")
    esp32 = None

cap = cv2.VideoCapture(0)

print("[INFO] Camera feed started. Press 'q' to exit.")

while True:
    ret, frame = cap.read()
    if not ret:
        print("[ERROR] Unable to read camera feed.")
        break

    results = model(frame, verbose=False)
    elephant_detected = False

    for r in results:
        for box in r.boxes:
            cls_id = int(box.cls[0])
            # Check for Elephant (COCO class index 20 or custom model class 0)
            if cls_id == 20 or cls_id == 0:
                elephant_detected = True
                x1, y1, x2, y2 = map(int, box.xyxy[0])
                cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 255), 3)
                cv2.putText(frame, "ELEPHANT DETECTED", (x1, max(y1 - 10, 20)),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 0, 255), 2)

    # Send state command to ESP32 over Bluetooth
    if esp32 and esp32.is_open:
        if elephant_detected:
            esp32.write(b'S')  # 'S' = Stop & Sound Alarm
        else:
            esp32.write(b'F')  # 'F' = Forward / Clear

    cv2.imshow("GajaYanthra AI Detection", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
if esp32 and esp32.is_open:
    esp32.close()