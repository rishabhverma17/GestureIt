
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
int dc1position;   // Output value to the dc.
int dc2position;   // Output value to the dc.

char buffer[12];  //There are 4 3-digit commands
const int buffer_len = 12;  
boolean characterSent = false;

//Sensor Value

int sensorvalue;       //accelerometer
int forcePosition1;    // Input value from the analog pin.
int forcePosition2;
int flexPosition;      // Input value from the analog pin.


  
void setup() {
  
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  clearBuffer();
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
   // if(!characterSent){
  //  Serial.print('a'); 
   // characterSent = true;
  //}
     //Get commands
     
  if(mySerial.available()){
 //   characterSent = false;
    char check = mySerial.read();
  
    if(check == '.')
    { 
      for (int i=0; i <buffer_len; i++)
      {
        buffer[i] = mySerial.read();
        delay(10);
      }
       //Get the data from the XBee Transmission
       char flex[3] =    {buffer[0], buffer[1], buffer[2]}; 
       char force1[3] =  {buffer[3], buffer[4], buffer[5]}; 
       char force2[3] =  {buffer[6], buffer[7], buffer[8]}; 
       char accele[3] =  {buffer[9], buffer[10], buffer[11]}; 

      //Parse buffer into our sensor values
      flexPosition=(int)( 100*(flex[0] - '0') + 10*(flex[1]-'0') + (flex[2]-'0'));
      forcePosition1=(int)( 100*(force1[0] - '0') + 10*(force1[1]-'0') + (force1[2]-'0'));
      forcePosition2=(int)( 100*(force2[0] - '0') + 10*(force2[1]-'0') + (force2[2]-'0'));
      sensorvalue=(int)( 100*(accele[0] - '0') + 10*(accele[1]-'0') + (accele[2]-'0'));

      flexPosition=map(flexPosition,0,255,0,1023); //will give this value directly to motor
      forcePosition1=map(forcePosition1,0,255,0,1023); // will check if less than 255
      forcePosition2=map(forcePosition2,0,255,0,1023); // will check if less than 255
      sensorvalue=map(sensorvalue,0,255,0,1023); // will check if less than 114.6(left)----and grtr thn 139.58(right). In between-> still
    
      flexPosition = constrain(flexPosition, 0, 1023);
      forcePosition1 = constrain(forcePosition1, 0, 1023);
      forcePosition2 = constrain(forcePosition2, 0, 1023);
      sensorvalue = constrain(sensorvalue, 0, 1023);


  
  //Accelerometer Control
  if(sensorvalue>560)
  {
    dc2position=0;
    //dc2position = constrain(dc2position, 0, 255);
    analogWrite(7,dc2position);
  }
  else if(sensorvalue<450)
  {
    dc2position=0;
    //dc2position = constrain(dc2position, 0, 255);
    analogWrite(4,dc2position);
  }
  else
  {
    dc2position=255;
    //dc2position = constrain(dc2position, 0, 255);
    analogWrite(7,dc2position);
    analogWrite(4,dc2position);
  }
  
  // Force and Flex Control
  
  if(forcePosition1 <800 && forcePosition2 < 800){
     
      dc1position = 255;
     
      analogWrite(3,dc1position);
      analogWrite(6,dc1position);
  }
  else if(forcePosition1<800)
  {
    
    dc1position =map(flexPosition, 845, 1023,255, 0);
    analogWrite(6,dc1position);
    }
    else if(forcePosition2<800)
    {  
      dc1position = map(flexPosition, 845, 1023,255, 0);;
      analogWrite(3,dc1position);
    }
    else{
      //Serial.println("None");
      dc1position = 255;
       analogWrite(3,dc1position);
       analogWrite(6,dc1position);
    }
    }
  }   
  delay(150);
}

void clearBuffer(){
   for(int i = 0; i < buffer_len; i++)
    buffer[i] = 0;
  }
