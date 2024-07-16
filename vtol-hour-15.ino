void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available to read
    String received = Serial.readString(); // Read the received data
    if (received == "Signal to mainboard: Flap deployed") {
      Serial.println("ACK"); // Send acknowledgment back to sender
    }
  }
  delay(10); // Delay to improve simulation performance
}
