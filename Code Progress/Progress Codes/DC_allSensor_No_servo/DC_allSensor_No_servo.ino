/*********************************************************
 * Controlling Car using Flex,Force and Accelerometer.                  
 * Rishabh Verma, Rishi Chandak, Saurabh Saluja            
 * Computer Science and Engineering Department            
 * Sharda University, Batch 2012-2016                      
 * ********************************************************/
//Define pins for Communication
const int forcePin1 = 2;
const int forcePin2 =1 ;
const int flexPin =  0;

const int xPin=A3;
int sensorvalue =0;   //Acceleration
int forcePosition1;    // Input value from the analog pin.
int forcePosition2;
int flexPosition;// Input value from the analog pin.
int dc1position;   // Output value to the dc.
int dc2position;   // Output value to the dc.
  

void setup() {
  Serial.begin(9600);
  pinMode(A3,INPUT);// voltage divider value input
  
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
}

void loop() {
  
  forcePosition1 = analogRead(forcePin1);
  delay(10);
  forcePosition2 = analogRead(forcePin2);
  delay(10);
  flexPosition = analogRead(flexPin);
  delay(10);
  Serial.println(flexPosition);
  

  sensorvalue = analogRead(xPin); //read analog value from sensor
 //  Serial.println(sensorvalue);
 
 /*Turning The Forward Wheels*/
 
  if(sensorvalue>560) //Value from Accelerometer
  {
    dc2position=0;
    dc2position = constrain(dc2position, 0, 255);
    analogWrite(7,dc2position); 
  }
  else if(sensorvalue<460)//Value from Accelerometer
  {
    dc2position=0;
    dc2position = constrain(dc2position, 0, 255);
    analogWrite(4,dc2position);
  }
  else  //Keeping Axel at 90 Degree [Straight]
  {
    dc2position=255;
    dc2position = constrain(dc2position, 0, 255);
    analogWrite(7,dc2position);
    analogWrite(4,dc2position);
  }
  Serial.print("DC2 Value ");
  Serial.print(dc2position);
  
  /* Force Mapping  */

  if(forcePosition1 <800 && forcePosition2 < 800){
    Serial.println("Multiple Sensor Value.");
    
      dc1position = 255;
  /* Force Mapping  */
      dc1position = constrain(dc1position, 0, 255);
      analogWrite(3,dc1position);
      analogWrite(6,dc1position);
  }
  else if(forcePosition1<800)
  {
    Serial.println("Force 1");
    dc1position = map(flexPosition, 800, 1023,255, 0);
  /* Force Mapping  */
    dc1position = constrain(dc1position, 0, 255);
    analogWrite(6,dc1position);
    }
    else if(forcePosition2<800)
    {  
      Serial.println("Force 2");
      dc1position = map(flexPosition, 800, 1023,255, 0);
  /* Force Mapping  */
      dc1position = constrain(dc1position, 0, 255);
      analogWrite(3,dc1position);
    }
    else{
      Serial.println("None");
      dc1position = 255;
  /* Force Mapping  */
      dc1position = constrain(dc1position, 0, 255);
       analogWrite(3,dc1position);
       analogWrite(6,dc1position);
    }
  delay(150);
}
