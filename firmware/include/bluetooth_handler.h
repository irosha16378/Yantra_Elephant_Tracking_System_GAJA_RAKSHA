#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include <Arduino.h>
#include "BluetoothSerial.h"

class BluetoothHandler {
private:
    BluetoothSerial SerialBT;
    bool isConnected;
    char lastCommand;
    unsigned long lastCommandTime;

public:
    BluetoothHandler();
    void begin(const char* deviceName);
    bool checkConnection();
    char readCommand();
    bool hasTimedOut(unsigned long timeoutMs);
    void sendResponse(const char* message);
};

#endif // BLUETOOTH_HANDLER_H
