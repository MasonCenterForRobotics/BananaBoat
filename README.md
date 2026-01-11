# Bluetooth Motor Control for Arduino

A Bluetooth-controlled robot using an Arduino with Adafruit Motor Shield V1. This project allows you to control a 4-wheel robot via Bluetooth commands, with tank-style turning for regular wheels.

## Overview

This code enables wireless control of a 4-motor robot through Bluetooth communication. The robot uses tank-style turning (opposite sides rotate in opposite directions) and runs at 50% speed for safer operation.

## Hardware Requirements

- **Arduino Board** (Uno R3)
- **Adafruit Motor Shield V1** (for L293D motor driver)
- **HC-05 Bluetooth Module** (or compatible)
- **4 DC Motors** (connected to motor ports 1-4)
- **Power Supply** (appropriate for your motors)
- **Jumper Wires** (for Bluetooth module connections)

### Motor Layout

The motors are configured as follows:
- **Motor 1** (Port 1): Back Left
- **Motor 2** (Port 2): Back Right
- **Motor 3** (Port 3): Front Right
- **Motor 4** (Port 4): Front Left

### Bluetooth Module Connections

- **HC-05 RX** → Arduino Pin 10
- **HC-05 TX** → Arduino Pin 9
- **HC-05 VCC** → 5V (or 3.3V depending on your module)
- **HC-05 GND** → GND

**Note:** Some HC-05 modules may require a voltage divider for the RX pin if they operate at 3.3V. Check your module's specifications.

## Software Requirements

- **Arduino IDE** (version 1.8.x or later recommended)
- **Adafruit Motor Shield Library** (V1)

## Installation & Setup

### Step 1: Install Arduino IDE

1. Download and install the Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Launch the Arduino IDE

### Step 2: Install Required Library

1. Open Arduino IDE
2. Go to **Sketch** → **Include Library** → **Manage Libraries...**
3. In the Library Manager, search for **"Adafruit Motor Shield"**
4. Install **"Adafruit Motor Shield library"** (V1 version)
5. Wait for installation to complete

**Note:** The `SoftwareSerial` library is included automatically with the Arduino IDE, so no additional installation is needed.

### Step 3: Configure Arduino Board

1. Connect your Arduino to your computer via USB
2. In Arduino IDE, go to **Tools** → **Board** → Select your Arduino board (e.g., "Arduino Uno")
3. Go to **Tools** → **Port** → Select the COM port your Arduino is connected to

### Step 4: Upload the Code

1. Open `Bluetooth_controls.ino` in the Arduino IDE
2. Click the **Verify** button (checkmark icon) to compile the code
3. If compilation is successful, click the **Upload** button (arrow icon) to upload to your Arduino
4. Wait for the upload to complete

### Step 5: Open Serial Monitor (for Debugging)

1. Go to **Tools** → **Serial Monitor**
2. Set baud rate to **9600**
3. You should see startup messages indicating the system is ready

## How It Works

### Bluetooth Communication

- The code uses `SoftwareSerial` to communicate with the HC-05 Bluetooth module
- Communication baud rate: **9600**
- The Arduino continuously checks for incoming Bluetooth commands
- Status updates are printed to Serial Monitor every 2 seconds

### Motor Control

- All motors run at **50% speed** (127 out of 255) by deafult for safer operation
- The `setSpeed()` function accepts values from **0 to 255**:
  - `0` = Motor off (0% duty cycle)
  - `255` = Full speed (100% duty cycle)
  - `127` ≈ 50% speed (half speed)

### Movement Commands

The robot responds to the following single-character Bluetooth commands:

| Command | Action | Description |
|---------|--------|-------------|
| `F` | Forward | All motors rotate forward |
| `B` | Backward | All motors rotate backward |
| `L` | Left Turn | Tank turn left (left side backward, right side forward) |
| `R` | Right Turn | Tank turn right (left side forward, right side backward) |
| "S" but also any other | Stop | Motors stop powering but do not brake |

### Tank-Style Turning

Unlike mecanum wheels, this code uses tank-style turning for regular wheels:
- **Left Turn**: Left side motors (1 & 4) go backward, right side motors (2 & 3) go forward
- **Right Turn**: Left side motors (1 & 4) go forward, right side motors (2 & 3) go backward

This creates a rotation in place, similar to how a tank turns.

## Using the Robot

### Connecting via Bluetooth

1. Power on your Arduino and wait for the HC-05 module to initialize
2. On your phone/computer, search for Bluetooth devices
3. Look for your HC-05 module (default name is usually "HC-05" or similar)
4. Pair with the device (default PIN is "1234")
5. Use a Bluetooth serial terminal app to connect and send commands

### Recommended Bluetooth Apps

- **Android**: "Arduino Bluetooth control" app - use the **Car Control** section for robot control
- **iOS**: Will update when we test iOS apps
- **Windows**: Will update when we test Windows applications
- **Mac**: Will update when we test macOS applications

### Sending Commands

##note: this is for serial Bluetooth applications, NONE of the recommended apps use serial

1. Open your Bluetooth app
2. Connect to your HC-05 module
3. Send single characters: `F`, `B`, `L`, `R`
4. The robot will execute the command until a new command is received
5. Send any other character to stop the robot

## Debugging

### Serial Monitor Output

The code includes extensive logging to help diagnose issues:

- **Startup Messages**: Confirms initialization
- **Status Updates**: Every 2 seconds, shows:
  - Number of bytes available from Bluetooth (`HC05.available()`)
  - Elapsed time since startup
- **Data Reception**: When commands are received, shows:
  - Number of bytes available
  - The received character and its ASCII value
- **Command Processing**: Logs which command was executed

### Common Issues

**Problem: `HC05.available()` always returns 0**
- Check Bluetooth module wiring (RX/TX connections)
- Verify baud rate matches (9600)
- Ensure Bluetooth device is paired and connected
- Check if the module is powered correctly
- Try resetting the HC-05 module

**Problem: Motors not responding**
- Verify motor shield is properly seated on Arduino
- Check motor connections to shield ports 1-4
- Ensure adequate power supply for motors
- Verify motors are connected to the correct ports

**Problem: Serial Monitor shows nothing**
- Check USB connection to Arduino
- Verify Serial Monitor baud rate is set to 9600
- Ensure code uploaded successfully

## Code Structure

- `setup()`: Initializes Serial communication and Bluetooth module
- `loop()`: Continuously checks for Bluetooth commands and executes them
- `forward()`: Moves robot forward (all motors forward)
- `back()`: Moves robot backward (all motors backward)
- `left()`: Tank turn left
- `right()`: Tank turn right
- `Stop()`: Stops all motors

## Customization

### Changing Motor Speed

To change the motor speed, modify the `setSpeed()` values in the movement functions:
- Current: `setSpeed(127)` = 50% speed
- Full speed: `setSpeed(255)` = 100% speed
- Quarter speed: `setSpeed(64)` = 25% speed

### Changing Status Update Interval

Modify `STATUS_INTERVAL` constant (line 25) to change how often status updates are printed:
- Current: `2000` = 2 seconds
- More frequent: `1000` = 1 second
- Less frequent: `5000` = 5 seconds

## References

- **Adafruit Motor Shield Library**: [GitHub Repository](https://github.com/adafruit/Adafruit-Motor-Shield-library)
- **Arduino SoftwareSerial**: Included with Arduino IDE
- **HC-05 Bluetooth Module**: Check your module's datasheet for specific wiring requirements

## License

This code is provided as-is for educational and personal use.

## Troubleshooting Tips

1. **Always check Serial Monitor first** - it provides valuable debugging information
2. **Verify all connections** - loose wires are a common issue, always double check the wires
3. **Test Bluetooth connection** - use a simple serial terminal to verify data is being sent
4. **Check power supply** - motors require adequate power, especially under load, the simple usb connector does not provide enough power to run the motors
5. **Verify motor shield compatibility** - ensure you're using Adafruit Motor Shield V1, not V2 and not the one for R4 arduino
6. **Bluetooth connections don't work** - ensure you have the right RX and TX pins set in your code to initialize the HC-05 Bluetooth controller
7. **Bluetooth connections don't work, still** - the HC-05 uses Serial Bluetooth, which isn't as fancy as newer Bluetooth connections - so ensure that whatever you're connecting from supports Serial Bluetooth
8. **Motors run the wrong way** - DO NOT switch the polarity of the motor controller UNLESS you want to blow up the motor controller, you have to switch all eight motor wires instead 

---

**Happy Robot Building! 🤖**

