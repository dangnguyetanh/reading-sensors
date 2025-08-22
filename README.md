# Sensor and Communication Interface Collection

This repository contains a collection of Arduino and ESP32 projects for interfacing with various sensors, communication modules, and hardware components. These projects can be used as reference implementations for IoT applications, home automation, and embedded systems development.

## Project Categories

### Sensors
- **DHT11**: Temperature and humidity sensor implementation using PlatformIO
- **MPU-6050**: Accelerometer and gyroscope sensor
  - `mpu-6050_picth-roll-yaw`: Pitch, roll, and yaw calculation
  - `mpu6050_calib`: Calibration for the MPU-6050 sensor
- **HC-SR04**: Ultrasonic distance sensor
- **TCS34725**: RGB color sensor with I2C interface
- **TDS**: Total Dissolved Solids water quality sensor
- **YF-S201_DN15**: Water flow sensor (DN15)
- **MR60FDA1**: 60GHz mmWave radar sensor for fall detection and human presence

### Communication Modules
- **EC800M 4G Module**:
  - `EC800M_4g_mqtt_esp32`: MQTT communication using ESP32
  - `EC800M_4g_mqtt_uno`: MQTT communication using Arduino Uno
  - `EC800M_GPS_esp32`: GPS functionality with ESP32
  - `EC800M_sms`: SMS sending functionality
- **Telegram**: Communication with Telegram API
  - `telegram`: Basic Telegram bot implementation
  - `camera_esp32-telegram`: ESP32 camera integration with Telegram
- **Google Sheets**: Data logging to Google Sheets (`gg_sheets_esp32`)
- **GPS**: Interface with NEO-6M GPS module (`GPS_neo6m`)

### Control Systems
- **Dimmer**: AC power control systems
  - `dimmer_cross`: Dimmer implementation
  - `dimmer_cross_ctrlAC`: AC control using dimmer
- **Servo**: Servo motor control
- **RFID**: RFID card reading and identification

### Utilities
- **I2C Scanner**: Tool to scan and identify I2C devices on the bus
- **Flow Sensor**: Implementation for 3D printing applications

## Installation and Setup

Most projects are designed for Arduino IDE or PlatformIO. To use these projects:

1. Clone this repository
2. Open the specific project folder in Arduino IDE or PlatformIO
3. Install any required libraries mentioned in the project files
4. Configure the board settings according to your hardware (ESP32, Arduino Uno, etc.)
5. Upload the code to your board

## Project Structure

Each project folder typically contains:
- Main code file (`.ino` for Arduino IDE or `.cpp` for PlatformIO)
- Configuration files (if applicable)
- Library dependencies in the `lib` folder (for PlatformIO projects)

## Special Projects

### DHT11 (PlatformIO Project)
A complete temperature and humidity sensing project with structured folders:
- `src/`: Contains the main application code
- `include/`: Header files
- `lib/`: External libraries
- `platformio.ini`: PlatformIO configuration

### MR60FDA1 60GHz mmWave Radar Sensor
Multiple examples for the Seeed Studio MR60FDA1 sensor:
- Fall detection
- Human presence detection
- Raw data output
- Sensor reset functionality
- Frame transmission

## Dependencies

Each project may require specific libraries. Please check the individual project files for library requirements and install them through the Arduino Library Manager or PlatformIO's library management system.

## License

This collection is maintained for educational and reference purposes. Please respect the original licenses of any included libraries or dependencies.

## Contributing

Feel free to contribute to this collection by adding new sensor implementations or improving existing ones. Please follow the established project structure and provide proper documentation for your contributions.

## Authors

- DANG NGUYET ANH  📧 Contact me: dangnguyetanh1908@gmail.com