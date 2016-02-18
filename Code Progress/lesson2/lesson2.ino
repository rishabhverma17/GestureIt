
int switchPin = 8;
int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(switchPin,INPUT);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(switchPin) == HIGH)
  {
    digitalWrite(ledPin,HIGH);
  }
  else
  {
    digitalWrite(ledPin,LOW);
  }
}
