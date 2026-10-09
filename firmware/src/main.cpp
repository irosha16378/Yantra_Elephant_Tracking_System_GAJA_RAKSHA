#include <Arduino.h>
#include "config.h"
#include "bluetooth_handler.h"

// Instantiate Bluetooth Handler
BluetoothHandler btHandler;

// State Tracking Variables
bool isElephantDetected = false;

void setupPins() {
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(ALERT_LED_PIN, OUTPUT);
    pinMode(STATUS_LED_PIN, OUTPUT);
    pinMode(MOTOR_ENABLE_PIN, OUTPUT);
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);

    // Initial Pin States (Safe Default)
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(ALERT_LED_PIN, LOW);
    digitalWrite(STATUS_LED_PIN, HIGH); // Heartbeat LED ON
    
    // Robot default state: Driving forward
    digitalWrite(MOTOR_ENABLE_PIN, HIGH);
    digitalWrite(MOTOR_IN1_PIN, HIGH);
    digitalWrite(MOTOR_IN2_PIN, LOW);
}

void triggerAlarm(bool active) {
    if (active) {
        // Elephant Detected! Activate Alarm & Emergency Stop
        digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(ALERT_LED_PIN, HIGH);
        
        // Stop Motors
        digitalWrite(MOTOR_ENABLE_PIN, LOW);
        digitalWrite(MOTOR_IN1_PIN, LOW);
        digitalWrite(MOTOR_IN2_PIN, LOW);
    } else {
        // Clear / Safe state: Silence Alarm & Move Forward
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(ALERT_LED_PIN, LOW);
        
        // Motor Forward
        digitalWrite(MOTOR_ENABLE_PIN, HIGH);
        digitalWrite(MOTOR_IN1_PIN, HIGH);
        digitalWrite(MOTOR_IN2_PIN, LOW);
    }
}

void setup() {
    Serial.begin(BT_BAUD_RATE);
    Serial.println("==============================================");
    Serial.println("   GajaRaksha ESP32 Firmware Starting...      ");
    Serial.println("==============================================");

    setupPins();
    btHandler.begin(BT_DEVICE_NAME);

    Serial.println("[SYSTEM] Ready! Waiting for Bluetooth Connection...");
}

void loop() {
    // Read command from Python AI Detection Server via Bluetooth Serial
    char command = btHandler.readCommand();

    if (command == 'S') {
        if (!isElephantDetected) {
            Serial.println("[ALERT] Elephant Detected! Triggering Emergency Stop & Buzzers.");
            isElephantDetected = true;
        }
        triggerAlarm(true);
    } else if (command == 'F') {
        if (isElephantDetected) {
            Serial.println("[INFO] Zone Clear. Resuming standard operation.");
            isElephantDetected = false;
        }
        triggerAlarm(false);
    }

    // Safety check
    if (btHandler.hasTimedOut(ALERT_TIMEOUT_MS) && isElephantDetected) {
        Serial.println("[WARNING] Signal timeout during alert mode.");
    }

    delay(20);
}
