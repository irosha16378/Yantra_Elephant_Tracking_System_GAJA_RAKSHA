#ifndef CONFIG_H
#define CONFIG_H

// ==========================================
// GajaRaksha Hardware & Pin Configuration
// ==========================================

// Bluetooth Configuration
#define BT_DEVICE_NAME "GajaYanthra_BT"

// Pin Definitions for Actuators & Indicators
#define BUZZER_PIN       18   // Piezo Buzzer / Alarm output
#define ALERT_LED_PIN    19   // Red High-Intensity Alert LED
#define STATUS_LED_PIN   2    // Onboard Status LED (GPIO 2)

// Motor / Robot Control Pins (L298N / TB6612FNG driver or Relays)
#define MOTOR_ENABLE_PIN 13   // Enable pin or Relay control
#define MOTOR_IN1_PIN    12   // Motor Direction 1
#define MOTOR_IN2_PIN    14   // Motor Direction 2

// Timing & Safety Configuration
#define BT_BAUD_RATE     115200
#define ALERT_TIMEOUT_MS 3000 // Time to maintain alert state if signal drops

#endif // CONFIG_H
