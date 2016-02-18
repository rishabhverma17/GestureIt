int variable = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  analogWrite(3,255);
  analogWrite(6,0);
}
