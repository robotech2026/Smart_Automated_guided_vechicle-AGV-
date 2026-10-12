# Smart AGV (Automated Guided Vehicle)

An ESP32-based Smart Automated Guided Vehicle (AGV) prototype designed to follow a path, detect nearby obstacles, and provide basic audio alerts. The project uses affordable embedded-system components and can be extended with camera-based QR navigation.

## Project Overview

The Smart Automated Guided Vehicle (AGV) is designed to transport materials from one location to another with minimal human intervention. It uses an ESP32 controller, IR sensors for line following, and an ultrasonic sensor to detect nearby obstacles, helping the vehicle move along a predefined path and improve operational efficiency. This system can be useful in factories, warehouses, manufacturing units, and material-handling areas where repetitive transportation tasks are required. Camera-based QR-code navigation can be added to support location identification and route selection in future development.

## Key Features

- ESP32-based control system
- Four-wheel drive prototype using DC motors
- IR-sensor line following
- Ultrasonic obstacle-distance sensing
- Buzzer alerts
- Planned camera-based QR navigation using ESP32-CAM
- Low-cost prototype suitable for further development

## Hardware Components

-> ESP32 development board
-> AI Thinker ESP32-CAM
-> L298N motor driver 
-> 4 DC gear motors and 4 wheels 
-> 2 IR sensors 
-> HC-SR04 ultrasonic sensor 
-> Buzzer 
-> Battery / regulated power supply 
-> Chassis and connecting wires 

## Pin Connections

These are the current main ESP32 pin assignments used in the prototype. Confirm them against your exact board and wiring before powering the circuit.

| Function | ESP32 pin |

| L298N ENA | GPIO 33 |
| L298N IN1 | GPIO 25 |
| L298N IN2 | GPIO 26 |
| L298N ENB | GPIO 32 |
| L298N IN3 | GPIO 27 |
| L298N IN4 | GPIO 14 |

| IR sensor 1 output | GPIO 4 |
| IR sensor 2 output | GPIO 5 |

| HC-SR04 TRIG | GPIO 18 |
| HC-SR04 ECHO | GPIO 19 |

| Buzzer | GPIO 13 |

Electrical caution:The HC-SR04 ECHO output is commonly 5 V, while ESP32 GPIO inputs are not 5 V tolerant. Use an appropriate voltage divider or level shifter before connecting ECHO to GPIO 19. Verify motor-driver wiring and power polarity before switching on.

### ESP32-CAM Integration

The AI Thinker ESP32-CAM is intended for camera-based QR recognition and route selection. Integration and UART pin assignments depend on the final firmware and board configuration. Do not treat this feature as complete unless camera-to-controller communication has been tested. If using UART, connect TX to the other board's RX, RX to TX, and GND to GND, with compatible 3.3 V logic levels.

## Software and Tools

- Arduino IDE
- ESP32 board support package for Arduino IDE
- ESP32 firmware for motor control, sensor reading, and line following
- ESP32-CAM firmware for QR recognition (planned / experimental)
- USB data cable and Serial Monitor for uploading and debugging

## Working Principle

1. IR sensors read the line or track beneath the AGV.
2. The ESP32 processes the sensor readings and controls the L298N to move the motors.
3. The ultrasonic sensor measures the distance to an object in front of the vehicle.
4. The buzzer provides an alert when triggered by the firmware.
5. In a future integrated version, the ESP32-CAM can identify QR codes and communicate route instructions to the main ESP32.

Sensor thresholds, motor direction, and speed values may need calibration for the actual floor, lighting, chassis, battery, and motors.

## Setup

1. Install the Arduino IDE.
2. Install ESP32 board support and select the correct ESP32 board and COM port.
3. Open the firmware `.ino` file from this repository.
4. Review the pin mapping and confirm it matches the hardware.
5. Check motor supply, regulator output, common ground, and sensor voltage levels.
6. Upload the firmware and open Serial Monitor at the baud rate specified in the code.
7. Test with the wheels lifted off the ground before placing the AGV on the floor.
8. Test line following, ultrasonic sensing, and buzzer alerts separately before combined operation.
9. Integrate the ESP32-CAM only after its firmware and communication protocol are ready.

## Testing Status

The prototype has been tested for basic line-following and buzzer operation. Ultrasonic sensing has shown delayed / no-echo behaviour during testing and requires further debugging. Solar-panel powering was explored but was not adopted as a completed power feature. Camera-based QR routing remains a planned integration unless later tests confirm otherwise.

## Safety and Limitations

- This is a prototype, not a safety-certified industrial AGV.
- Test at low speed in a clear, controlled area.
- Keep wheels lifted during initial motor-direction and firmware tests.
- Add reliable safe-stop / emergency-stop behaviour before autonomous operation around people.
- Ultrasonic readings can be affected by target angle, surface, sensor placement, and electrical noise.
- QR navigation requires a working camera pipeline, defined QR-to-route mapping, and tested communication between controllers.

## Future Improvements

- Complete and validate ESP32-CAM QR-code navigation
- Improve ultrasonic measurement reliability and obstacle-stop behaviour
- Add robust safe-stop and emergency-stop logic
- Calibrate motor speed and line-following thresholds
- Add battery-voltage monitoring and power-management improvements
- Record repeatable test results for different tracks and obstacles

## Suggested Repository Structure

```text
Smart-AGV/
├── README.md
├── firmware/
│   ├── agv_controller/
│   │   └── agv_controller.ino
│   └── esp32_cam_qr/        # Add when camera firmware is ready
├── docs/
│   ├── wiring-diagram.png
│   └── project-photos/
└── LICENSE
```

Adjust filenames to match the files actually included in your repository.

## License

Add a license file if you intend to publish this project for reuse. Choose a license that matches how you want others to use and modify the code.
