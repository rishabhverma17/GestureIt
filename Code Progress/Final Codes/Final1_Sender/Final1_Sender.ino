const int flexPin =  0;
const int forcePin1 = 1;
const int forcePin2 = 2 ;
const int xPin=A3;

int sensorvalue=0;   //accele
int flexPosition;// Input value from the analog pin.
int forcePosition1;    // Input value from the analog pin.
int forcePosition2;

int Send_sensorvalue;   //accele
int Send_flexPosition;// Input value from the analog pin.
int Send_forcePosition1;    // Input value from the analog pin.
int Send_forcePosition2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A3,INPUT);// voltage divider value input
  
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
}
void print_pretty(int val)
{
  int new_val;
  //All Numbers must range from zero to 255.
  if      (val<0)   new_val = 0;
  else if (val>255) new_val = 255;
  else    new_val = val;

  //Add Leading zeros
  if (new_val < 10)
  {
    Serial.print(0);
    Serial.print(0);
    Serial.print(new_val);
  }
  else if (new_val >= 10 && new_val <100)
  {
    Serial.print(0);
    Serial.print(new_val);
  }
  else Serial.print(new_val);
}

void loop() {

  flexPosition = analogRead(flexPin);
  delay(10);
  forcePosition1 = analogRead(forcePin1);
  delay(10);
  forcePosition2 = analogRead(forcePin2);
  delay(10);
  sensorvalue = analogRead(xPin); //read analog value from sensor
  delay(10);
  
  //Map Values for Transmission
  Send_flexPosition=map(flexPosition,0,1023,0,255); //will give this value directly to motor
  Send_forcePosition1=map(forcePosition1,0,1023,0,255); // will check if less than 255
  Send_forcePosition2=map(forcePosition2,0,1023,0,255); // will check if less than 255
  Send_sensorvalue=map(sensorvalue,0,1023,0,255); // will check if less than 114.6(left)----and grtr thn 139.58(right). In between-> still

  Send_flexPosition = constrain(Send_flexPosition, 0, 255);
  Send_forcePosition1 = constrain(Send_forcePosition1, 0, 255);
  Send_forcePosition2 = constrain(Send_forcePosition2, 0, 255);
  Send_sensorvalue = constrain(Send_sensorvalue, 0, 255);

 
  //Sending out data
  Serial.print('.');
  print_pretty(Send_flexPosition);
  print_pretty(Send_forcePosition1);
  print_pretty(Send_forcePosition2);
  print_pretty(Send_sensorvalue);
  //while (Serial.read() != 'a');
  
  delay(500);
}
