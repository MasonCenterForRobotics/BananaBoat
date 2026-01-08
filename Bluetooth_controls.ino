//first , you need to insstall the motor driver for L293D motor driver
// Go to Sketch-> Include Librabry-> Manage Library-> Search for Adafruit Motor Shield V1
// SoftwareSerial is included automatically with the Arduino IDE
#include <AFMotor.h>
#include <SoftwareSerial.h>

// setSpeed() function reference:
// - Range: 0 to 255 (8-bit PWM value)
// - 0 = 0% duty cycle (motor off/stopped)
// - 255 = 100% duty cycle (full speed/maximum power)
// - Values in between set proportional speed (e.g., 127 ≈ 50% speed)
// - Uses Pulse Width Modulation (PWM) to control motor power
// Reference: https://github.com/adafruit/Adafruit-Motor-Shield-library

SoftwareSerial HC05(10, 9); // RX, TX

//initial motors pin
AF_DCMotor motor1(1); // back left
AF_DCMotor motor2(2); // back right
AF_DCMotor motor3(3); // front right
AF_DCMotor motor4(4); // front left

char command;
unsigned long lastStatusTime = 0;
const unsigned long STATUS_INTERVAL = 2000; // Print status every 2 seconds

void setup()
{
  Serial.begin(9600);  // Initialize Serial for debugging
  HC05.begin(9600);  //Set the baud rate to your Bluetooth module.
  
  Serial.println("=== Bluetooth Motor Control Started ===");
  Serial.println("Waiting for Bluetooth connection...");
  Serial.print("HC05 initialized on pins: RX=10, TX=9, Baud=9600");
  Serial.println();
}

void loop() {
  // Periodic status logging (every 2 seconds)
  unsigned long currentTime = millis();
  if (currentTime - lastStatusTime >= STATUS_INTERVAL) {
    int availableBytes = HC05.available();
    Serial.print("[Status] HC05.available() = ");
    Serial.print(availableBytes);
    Serial.print(" | Time = ");
    Serial.print(currentTime / 1000);
    Serial.println("s");
    lastStatusTime = currentTime;
  }
  
  // Check for incoming data
  int availableBytes = HC05.available();
  if (availableBytes > 0) {
    Serial.print("[Data Received] Bytes available: ");
    Serial.println(availableBytes);
    
    command = HC05.read();
    Serial.print("[Command] Received character: '");
    Serial.print(command);
    Serial.print("' (ASCII: ");
    Serial.print((int)command);
    Serial.println(")");
    
    Stop(); //initialize with motors stoped
    if (command == 'F') {
      forward();
    } else if (command == 'B') {
      back();
    } else if (command == 'R') {
      right();
    } else if (command == 'L') {
      left();
    } else {
      Serial.print("[Command] Unknown command: '");
      Serial.print(command);
      Serial.println("' - Stopping motors");
      Stop();
    }
  }
} 
    
 
void forward()
{
  // setSpeed(127): 127/255 ≈ 50% speed (half speed)
  motor1.setSpeed(127); // back left - forward
  motor1.run(FORWARD);
  motor2.setSpeed(127); // back right - forward
  motor2.run(FORWARD);
  motor3.setSpeed(127); // front right - forward
  motor3.run(FORWARD);
  motor4.setSpeed(127); // front left - forward
  motor4.run(FORWARD);
}

void back()
{
  // setSpeed(127): 127/255 ≈ 50% speed (half speed)
  motor1.setSpeed(127); // back left - backward
  motor1.run(BACKWARD);
  motor2.setSpeed(127); // back right - backward
  motor2.run(BACKWARD);
  motor3.setSpeed(127); // front right - backward
  motor3.run(BACKWARD);
  motor4.setSpeed(127); // front left - backward
  motor4.run(BACKWARD);
}

void left()
{
  // Tank turn left: left side backward, right side forward
  // setSpeed(127): 127/255 ≈ 50% speed (half speed)
  motor1.setSpeed(127); // back left - backward
  motor1.run(BACKWARD);
  motor2.setSpeed(127); // back right - forward
  motor2.run(FORWARD);
  motor3.setSpeed(127); // front right - forward
  motor3.run(FORWARD);
  motor4.setSpeed(127); // front left - backward
  motor4.run(BACKWARD);
}

void right()
{
  // Tank turn right: left side forward, right side backward
  // setSpeed(127): 127/255 ≈ 50% speed (half speed)
  motor1.setSpeed(127); // back left - forward
  motor1.run(FORWARD);
  motor2.setSpeed(127); // back right - backward
  motor2.run(BACKWARD);
  motor3.setSpeed(127); // front right - backward
  motor3.run(BACKWARD);
  motor4.setSpeed(127); // front left - forward
  motor4.run(FORWARD);
}

void Stop()
{
  // setSpeed(0): 0 = motor off (0% duty cycle)
  motor1.setSpeed(0);  // back left - stop
  motor1.run(RELEASE);
  motor2.setSpeed(0);  // back right - stop
  motor2.run(RELEASE);
  motor3.setSpeed(0);  // front right - stop
  motor3.run(RELEASE);
  motor4.setSpeed(0);  // front left - stop
  motor4.run(RELEASE);
}
