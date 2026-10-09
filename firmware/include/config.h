#ifndef GAJA_RAKSHA_CONFIG_H
#define GAJA_RAKSHA_CONFIG_H

// ==========================================
// GajaRaksha Hardware Pin & Setup Configuration
// ==========================================

// Bluetooth Device Name
#define BT_DEVICE_NAME "GajaYanthra_BT"

// Actuators & Indicators GPIO Pins
#define BUZZER_PIN       18   // Piezo Buzzer / Siren
#define ALERT_LED_PIN    19   // High-intensity Alert LED
#define STATUS_LED_PIN   2    // Onboard Status LED

// Motor Driver Pins (e.g. L298N / Relays)
#define MOTOR_ENABLE_PIN 13   // Enable pin / Relay
#define MOTOR_IN1_PIN    12   // Motor Direction 1
#define MOTOR_IN2_PIN    14   // Motor Direction 2

// Serial Baud Rate
#define SERIAL_BAUD      115200

#endif // GAJA_RAKSHA_CONFIG_H
