#include "bluetooth_handler.h"
#include "config.h"

BluetoothHandler::BluetoothHandler() {
    isConnected = false;
    lastCommand = 'F';
    lastCommandTime = 0;
}

void BluetoothHandler::begin(const char* deviceName) {
    SerialBT.begin(deviceName);
    Serial.print("[BT] Bluetooth Serial initialized as: ");
    Serial.println(deviceName);
}

bool BluetoothHandler::checkConnection() {
    return SerialBT.hasClient();
}

char BluetoothHandler::readCommand() {
    if (SerialBT.available()) {
        char cmd = SerialBT.read();
        // Accept control commands
        if (cmd == 'S' || cmd == 'F') {
            lastCommand = cmd;
            lastCommandTime = millis();
        }
    }
    return lastCommand;
}

bool BluetoothHandler::hasTimedOut(unsigned long timeoutMs) {
    return (millis() - lastCommandTime > timeoutMs);
}

void BluetoothHandler::sendResponse(const char* message) {
    if (SerialBT.hasClient()) {
        SerialBT.println(message);
    }
}
