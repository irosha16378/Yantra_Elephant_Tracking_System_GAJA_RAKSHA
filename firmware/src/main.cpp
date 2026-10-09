#include <Arduino.h>
#include "BluetoothSerial.h"
#include "config.h"

// Ensure Bluetooth is enabled in ESP32 config
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please enable Bluetooth in board configuration.
#endif

// Bluetooth Serial Instance
BluetoothSerial SerialBT;

void setupPins() {
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(ALERT_LED_PIN, OUTPUT);
    pinMode(STATUS_LED_PIN, OUTPUT);
    pinMode(MOTOR_ENABLE_PIN, OUTPUT);
    pinMode(MOTOR_IN1_PIN, OUTPUT);
    pinMode(MOTOR_IN2_PIN, OUTPUT);

    // Initial safe states
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(ALERT_LED_PIN, LOW);
    digitalWrite(STATUS_LED_PIN, HIGH);

    // Motor default: Driving Forward
    digitalWrite(MOTOR_ENABLE_PIN, HIGH);
    digitalWrite(MOTOR_IN1_PIN, HIGH);
    digitalWrite(MOTOR_IN2_PIN, LOW);
}

void setup() {
    Serial.begin(SERIAL_BAUD);
    Serial.println("==============================================");
    Serial.println("   Starting GajaRaksha ESP32 Controller...    ");
    Serial.println("==============================================");

    setupPins();

    // Start Bluetooth Serial
    SerialBT.begin(BT_DEVICE_NAME);
    Serial.print("[BT] Bluetooth Serial started! Device Name: ");
    Serial.println(BT_DEVICE_NAME);
    Serial.println("[BT] Waiting for AI commands ('S' or 'F')...");
}

void loop() {
    // Read command from Python script over Bluetooth
    if (SerialBT.available()) {
        char command = SerialBT.read();

        if (command == 'S') { 
            // Elephant Detected -> Emergency Stop & Trigger Alarm
            Serial.println("[ALERT] Elephant Detected! Stopping robot & activating siren.");
            
            digitalWrite(BUZZER_PIN, HIGH);
            digitalWrite(ALERT_LED_PIN, HIGH);
            
            digitalWrite(MOTOR_ENABLE_PIN, LOW);
            digitalWrite(MOTOR_IN1_PIN, LOW);
            digitalWrite(MOTOR_IN2_PIN, LOW);

        } else if (command == 'F') { 
            // Zone Clear -> Silence Alarm & Resume Driving Forward
            digitalWrite(BUZZER_PIN, LOW);
            digitalWrite(ALERT_LED_PIN, LOW);
            
            digitalWrite(MOTOR_ENABLE_PIN, HIGH);
            digitalWrite(MOTOR_IN1_PIN, HIGH);
            digitalWrite(MOTOR_IN2_PIN, LOW);
        }
    }

    delay(20);
}
