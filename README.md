# 🐘 GajaRaksha (GajaYanthra) - Wild Elephant Protection System

An IoT and AI-powered Wild Elephant Detection & Alert System using **ESP32 (PlatformIO)** and **YOLOv8 Real-Time Computer Vision**.

---

## 📁 Repository Directory Structure

```
GajaRaksha_Test/
├── firmware/                     # ⚡ ESP32 PlatformIO Microcontroller Code
│   ├── platformio.ini           # PlatformIO configuration (ESP32 Board, Framework & Serial Baud)
│   ├── include/                 # Hardware Header Files
│   │   ├── config.h             # GPIO Pin map (Buzzer, LEDs, Motor Driver pins)
│   │   └── bluetooth_handler.h  # Bluetooth Serial communication header
│   ├── src/                     # C++ Source Files
│   │   ├── main.cpp             # Main ESP32 setup & loop routines
│   │   └── bluetooth_handler.cpp# Bluetooth command parser ('S' = Stop/Alarm, 'F' = Clear)
│   ├── lib/                     # Custom hardware driver libraries
│   │   └── README
│   └── test/                    # Unit test suites
│       └── README
│
├── server/                      # 🧠 Python AI Vision & Web Command Center
│   ├── main.py                  # YOLOv8 Elephant Detection & Bluetooth sender script
│   ├── app.py                   # Flask Web Dashboard Server
│   ├── models/                  # AI Model Weights
│   │   ├── yolov8n.pt           # Default COCO pretrained YOLO model
│   │   └── best.pt              # Custom trained Elephant detection model
│   ├── templates/               # HTML Templates
│   │   └── index.html           # Live Control Center Web UI
│   ├── static/                  # Static Media Assets
│   │   ├── audio/               # Alert sound files (building-evacuation-sound.mp3)
│   │   └── snapshots/           # Captured detection snapshots
│   └── requirements.txt         # Python package dependencies
│
├── .gitignore                   # Ignore build artifacts & temporary files
└── README.md                    # Project setup & hardware guide
```

---

## ⚡ ESP32 Firmware (PlatformIO) Setup

### 1. Requirements
- [VS Code](https://code.visualstudio.com/) with **PlatformIO IDE Extension** installed.
- ESP32 Development Board (e.g., ESP32-WROOM-32).

### 2. Building & Flashing
1. Open VS Code and open the `firmware/` directory or the root directory.
2. Connect your ESP32 board via USB.
3. Click the **PlatformIO Upload** button (→ arrow in status bar) or run:
   ```bash
   cd firmware
   pio run --target upload
   ```
4. Open the Serial Monitor at `115200` baud rate to check connection state.

---

## 🧠 Python AI Server Setup

### 1. Requirements
- Python 3.9+
- Webcam / Camera Feed

### 2. Installation
Navigate to the `server/` directory and install dependencies:
```bash
cd server
pip install -r requirements.txt
```

### 3. Running AI Detection & Dashboard
- Run AI detection with Bluetooth control:
  ```bash
  python main.py
  ```
- Run Web Dashboard:
  ```bash
  python app.py
  ```
- Open your browser at `http://localhost:5000` to view the live dashboard.

---

## 🔌 Hardware Wiring Diagram (ESP32)

| Component | ESP32 GPIO Pin |
|---|---|
| Piezo Alarm / Buzzer | **GPIO 18** |
| High Intensity Alert LED | **GPIO 19** |
| Status / Heartbeat LED | **GPIO 2** (Onboard) |
| Motor Driver Enable (EN) | **GPIO 13** |
| Motor Driver IN1 | **GPIO 12** |
| Motor Driver IN2 | **GPIO 14** |
