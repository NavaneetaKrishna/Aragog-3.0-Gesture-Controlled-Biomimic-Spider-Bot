void setup() {
Serial.begin(9600); // Initialize serial communication at 9600 bits per second
}

void loop() {
Serial.println("Hello World!"); // Print "Hello World!" to the serial monitor
delay(1000); // Wait for a second
}