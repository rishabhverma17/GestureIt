const int flexpin = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int flexposition;    // Input value from the analog pin.
  int dcposition;   // Output value to the servo.
  flexposition = analogRead(flexpin);
  dcposition = map(flexposition, 782, 950,255, 0);
  dcposition = constrain(dcposition, 0, 255);
  //analogWrite(3,dcposition);
  analogWrite(6,dcposition);
  Serial.print("sensor: ");
  Serial.print(flexposition);
  Serial.print("  dc: ");
  Serial.println(dcposition);
  delay(150);
}
