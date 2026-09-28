/*
  Track Following Car with Arduino R3SMD
  Single IR Sensor Line Follower
  
  Hardware Requirements:
  - Arduino R3SMD
  - 1x IR Sensor (analog output)
  - 2x DC Motors with wheels
  - Motor Driver Module (L298N or similar)
  - 4x AA Battery holder (5-6V)
  - Castor wheel or ball caster
  - Connecting wires
  
  Connections:
  - IR Sensor: A0 (Analog Pin)
  - Motor Left Enable: Pin 5 (PWM)
  - Motor Left Forward: Pin 8
  - Motor Left Backward: Pin 9
  - Motor Right Enable: Pin 6 (PWM)
  - Motor Right Forward: Pin 10
  - Motor Right Backward: Pin 11
*/

// ============= PIN DEFINITIONS =============
#define IR_SENSOR A0          // Analog input from IR sensor

// Left Motor
#define LEFT_EN 5             // PWM pin for speed control
#define LEFT_FWD 8            // Forward direction
#define LEFT_BWD 9            // Backward direction

// Right Motor
#define RIGHT_EN 6            // PWM pin for speed control
#define RIGHT_FWD 10          // Forward direction
#define RIGHT_BWD 11          // Backward direction

// ============= CONFIGURATION =============
#define BASE_SPEED 200        // Base motor speed (0-255)
#define TURN_SPEED 150        // Speed when turning
#define IR_THRESHOLD 500      // Adjust based on your IR sensor (0-1023)
                              // Value < threshold = white/line detected
                              // Value > threshold = black/no line detected

// ============= VARIABLES =============
int irValue = 0;

void setup() {
  // Initialize serial for debugging
  Serial.begin(9600);
  
  // Set motor pins as outputs
  pinMode(LEFT_EN, OUTPUT);
  pinMode(LEFT_FWD, OUTPUT);
  pinMode(LEFT_BWD, OUTPUT);
  pinMode(RIGHT_EN, OUTPUT);
  pinMode(RIGHT_FWD, OUTPUT);
  pinMode(RIGHT_BWD, OUTPUT);
  
  // Set IR sensor as input
  pinMode(IR_SENSOR, INPUT);
  
  Serial.println("Track Following Car Initialized!");
  Serial.println("IR Threshold: " + String(IR_THRESHOLD));
  delay(2000);
}

void loop() {
  // Read IR sensor value
  irValue = analogRead(IR_SENSOR);
  
  // Print for debugging
  Serial.print("IR Value: ");
  Serial.println(irValue);
  
  // Decision logic based on single IR sensor
  if (irValue < IR_THRESHOLD) {
    // Line detected (white surface)
    // Move forward
    moveForward(BASE_SPEED);
  } else {
    // Line lost (black surface)
    // Search for line by turning right
    turnRight(TURN_SPEED);
  }
  
  delay(50);  // Small delay for stability
}

// ============= MOTOR CONTROL FUNCTIONS =============

void moveForward(int speed) {
  // Left Motor Forward
  digitalWrite(LEFT_FWD, HIGH);
  digitalWrite(LEFT_BWD, LOW);
  analogWrite(LEFT_EN, speed);
  
  // Right Motor Forward
  digitalWrite(RIGHT_FWD, HIGH);
  digitalWrite(RIGHT_BWD, LOW);
  analogWrite(RIGHT_EN, speed);
}

void moveBackward(int speed) {
  // Left Motor Backward
  digitalWrite(LEFT_FWD, LOW);
  digitalWrite(LEFT_BWD, HIGH);
  analogWrite(LEFT_EN, speed);
  
  // Right Motor Backward
  digitalWrite(RIGHT_FWD, LOW);
  digitalWrite(RIGHT_BWD, HIGH);
  analogWrite(RIGHT_EN, speed);
}

void turnLeft(int speed) {
  // Left Motor Slow/Stop
  digitalWrite(LEFT_FWD, HIGH);
  digitalWrite(LEFT_BWD, LOW);
  analogWrite(LEFT_EN, speed / 2);  // Reduce left motor speed
  
  // Right Motor Forward (Fast)
  digitalWrite(RIGHT_FWD, HIGH);
  digitalWrite(RIGHT_BWD, LOW);
  analogWrite(RIGHT_EN, speed);
}

void turnRight(int speed) {
  // Left Motor Forward (Fast)
  digitalWrite(LEFT_FWD, HIGH);
  digitalWrite(LEFT_BWD, LOW);
  analogWrite(LEFT_EN, speed);
  
  // Right Motor Slow/Stop
  digitalWrite(RIGHT_FWD, HIGH);
  digitalWrite(RIGHT_BWD, LOW);
  analogWrite(RIGHT_EN, speed / 2);  // Reduce right motor speed
}

void stopMotors() {
  digitalWrite(LEFT_FWD, LOW);
  digitalWrite(LEFT_BWD, LOW);
  analogWrite(LEFT_EN, 0);
  
  digitalWrite(RIGHT_FWD, LOW);
  digitalWrite(RIGHT_BWD, LOW);
  analogWrite(RIGHT_EN, 0);
}

void spinRight(int speed) {
  // Left Motor Forward
  digitalWrite(LEFT_FWD, HIGH);
  digitalWrite(LEFT_BWD, LOW);
  analogWrite(LEFT_EN, speed);
  
  // Right Motor Backward
  digitalWrite(RIGHT_FWD, LOW);
  digitalWrite(RIGHT_BWD, HIGH);
  analogWrite(RIGHT_EN, speed);
}

void spinLeft(int speed) {
  // Left Motor Backward
  digitalWrite(LEFT_FWD, LOW);
  digitalWrite(LEFT_BWD, HIGH);
  analogWrite(LEFT_EN, speed);
  
  // Right Motor Forward
  digitalWrite(RIGHT_FWD, HIGH);
  digitalWrite(RIGHT_BWD, LOW);
  analogWrite(RIGHT_EN, speed);
}