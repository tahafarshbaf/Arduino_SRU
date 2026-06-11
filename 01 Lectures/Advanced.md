```C++
// Define Define
enum RobotState {
  STOPPED,    // Value 1
  MOVING,     // Value 2
  ERROR       // Value 3
};

// Vriable defination
RobotState currentState = STOPPED;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // using enum in control loop
  switch (currentState) {
    case STOPPED:
      Serial.println("Robot is stopped.");
      // change status
      currentState = MOVING;
      break;
      
    case MOVING:
      Serial.println("Robot is moving.");
      break;
      
    case ERROR:
      Serial.println("Robot error!");
      break;
  }
  delay(1000);
}
```