#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>

Adafruit_LiquidCrystal lcd_1(0);
Servo servo_2;
Servo servo_3;

const int poten = A3; 
      int var;


void setup() {
  lcd_1.begin(16, 2);
  servo_2.attach(2, 500, 2500);
  servo_3.attach(3, 500, 2500);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);

  Serial.begin(9600);

  lcd_1.print("initialized");
  servo_2.write(180);
  servo_3.write(180);
  delay(500);
  lcd_1.clear();
  lcd_1.print("flap deployed");
  delay(500);
  lcd_1.clear();
  lcd_1.print("sending signal to mainboard...");

  Serial.println("Signal to mainboard: Flap deployed");

  long startTime = millis();
  bool responseReceived = false;

  while (millis() - startTime < 2000) {
    if (Serial.available() > 0) {
      String response = Serial.readString();
      if (response == "ACK") {
        responseReceived = true;
        break;
      }
    }
  }

  lcd_1.clear();
  if (responseReceived) {
    lcd_1.print("Connection established");
    digitalWrite(9, HIGH);
  } else {
    lcd_1.print("Failure in connection");
    digitalWrite(9, LOW);
  }
}

void loop() {
  var = analogRead(poten);
  analogWrite(6,var);
  delay(10); 
}
