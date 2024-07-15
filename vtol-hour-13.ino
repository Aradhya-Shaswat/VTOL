#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>

Adafruit_LiquidCrystal lcd(0);
Servo s2, s3;
const int pot = A3;
int pos2 = 180, pos3 = 180, val;

void setup() {
  lcd.begin(16, 2);
  s2.attach(2, 500, 2500);
  s3.attach(3, 500, 2500);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);

  lcd.print("init");
  s2.write(pos2);
  s3.write(pos3);
  delay(500);
  lcd.clear();
  lcd.print("flap dep");
  delay(500);
  lcd.clear();
  lcd.print("sending...");
  Serial.println("Flap dep");

  bool ack = false;
  long t = millis();
  while (millis() - t < 2000) {
    if (Serial.available() > 0 && Serial.readString() == "ACK") {
      ack = true;
      break;
    }
  }

  lcd.clear();
  lcd.print(ack ? "Connected" : "Fail");
  digitalWrite(9, ack ? HIGH : LOW);
}

void loop() {
  val = analogRead(pot);
  analogWrite(6, val);
  pos2 = map(val, 0, 1023, 0, 180);
  pos3 = 180 - pos2;
  s2.write(pos2);
  s3.write(pos3);

  lcd.setCursor(0, 0);
  lcd.print("Flap2: " + String(pos2));
  lcd.setCursor(0, 1);
  lcd.print("Flap3: " + String(pos3));
  delay(500);
}
