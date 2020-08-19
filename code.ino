
int leftCenterSensor = 3;   //ANALOG PINS   //OUT OF 8 IR SENSORS USING ONLY 6 SENSORS
int leftNearSensor = 4;
int leftFarSensor = 5;
int rightCenterSensor = 2;
int rightNearSensor = 1;
int rightFarSensor =0;

int enable1 = 11;
int enable2 = 10;

int leftCenterReading;
int leftNearReading;
int leftFarReading;
int rightCenterReading;
int rightNearReading;
int rightFarReading;

int leftMotor1 = 7;   //DIGITAL PINS   //MOTOR PIN CONNECTIONS
int leftMotor2 = 6;
int rightMotor1 = 5;
int rightMotor2 = 8;


int replaystage;
int leapTime = 200;

int led = 13;
char path[30] = {}; //ARRAY TO STORE PATH OF BOT
int pathLength;
int readLength;


void setup()
{
   Serial.begin(115200);
  
   pinMode(leftCenterSensor, INPUT);
   pinMode(leftNearSensor, INPUT);
   pinMode(leftFarSensor, INPUT);
   pinMode(rightCenterSensor, INPUT);
   pinMode(rightNearSensor, INPUT);
   pinMode(rightFarSensor, INPUT);
    
   pinMode(leftMotor1, OUTPUT);
   pinMode(leftMotor2, OUTPUT);
   pinMode(rightMotor1, OUTPUT);
   pinMode(rightMotor2, OUTPUT);
   pinMode(led, OUTPUT);

   
   digitalWrite(led, HIGH);  //TURING LED ON
   delay(1000);
}


void readSensors()
{  
   leftCenterReading  = analogRead(leftCenterSensor);
   leftNearReading    = analogRead(leftNearSensor);
   leftFarReading     = analogRead(leftFarSensor);
   rightCenterReading = analogRead(rightCenterSensor);
   rightNearReading   = analogRead(rightNearSensor);
   rightFarReading    = analogRead(rightFarSensor);  
}


//   (>200) MEANS BLACK AND (<200) MEANS WHITE


void loop()                            
{    
   readSensors();                                                                                     
   if(leftFarReading<200 && rightFarReading<200 && (leftCenterReading>200 || rightCenterReading>200) )  //CONDITIONS FOR BOT TO GO STRAIGHT
   {     
      straight();                                                                                      
   }
   else
   {                                                                                                
      leftHandWall();                                                                                   
   }
}


void straight()
{  
   if( analogRead(leftCenterSensor)<200)
   {  
      digitalWrite(leftMotor1, HIGH);   //GO STRAIGHT
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(1);
      digitalWrite(leftMotor1, HIGH);   //GO RIGHT
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(5);
      return;
    }
    if(analogRead(rightCenterSensor)<200)
    {
      digitalWrite(leftMotor1, HIGH);     //GO STRAIGHT
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(1);
      digitalWrite(leftMotor1, LOW);     //GO LEFT
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(5);
      return;
    }
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(enable1,200);          
    analogWrite(enable2,200);          
    delay(4);
    digitalWrite(leftMotor1, LOW);      //IF WE DON'T KEEP STOPING IT AFTER EVERY MOTION IT WOUNLD BE VERY DIFFICULT TO TURN DUE TO HIGH SPEED MOTORS
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    analogWrite(enable1,200);          
    analogWrite(enable2,200);          
    delay(1);
}


void leftHandWall()          //APPLYING LEFT HAND LOGIC
{    
   if( leftFarReading>200 && rightFarReading>200)   //IF BOT HAS THE OPTION TO TAKE BOTH LEFT AND RIGHT IT WILL CHOSE TO GO LEFT BUT BEFORE THAT WE NEED TO CHECK IF IT IS END OF THE MAZE
   {                                                //OR NOT
      
      digitalWrite(leftMotor1, HIGH);    //MOVE THE BOT AN INCH FORWARD
      digitalWrite(leftMotor2, LOW);     
      digitalWrite(rightMotor1, HIGH);   
      digitalWrite(rightMotor2, LOW);    
     analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(leapTime);
      
      readSensors();            //NOW AGAIN READ SENSORS ==> NEW VALUES GET STORED IN VARIABLES
      
      if(leftFarReading>200 || rightFarReading>200)
      {  
         done();
      }
      if(leftFarReading<200 && rightFarReading<200)  //IF THIS CONDITION SATISFIES ==> STRAIGHT PATH IS AVAILABLE BUT GOING LEFT IS PREFERRED OVER STRAIGHT PATH
      {   
         turnLeft();
      }
   } 
  
   if(leftFarReading>200)                  // IF YOU CAN TURN LEFT
   {       
      
      digitalWrite(leftMotor1, HIGH);      //MOVE THE BOT AN INCH FORWARD
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(leapTime);
      
      readSensors();            //NOW AGAIN READ SENSORS ==> NEW VALUES GET STORED IN VARIABLES
      
      if(leftFarReading<200 && rightFarReading<200)    //IF THIS CONDITION SATISFIES ==> STRAIGHT PATH IS AVAILABLE BUT GOING LEFT IS PREFERRED OVER STRAIGHT PATH
      {  
         turnLeft();
      }
      else
      {  
         done();
      }
   }
    
   if(rightFarReading>200)                  // IF YOU CAN TURN RIGHT
   {
      digitalWrite(leftMotor1, HIGH);     //MOVE THE BOT AN INCH FORWARD
      digitalWrite(leftMotor2, LOW);  
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(30);
      
      readSensors();            //NOW AGAIN READ SENSORS ==> NEW VALUES GET STORED IN VARIABLES
      
      if(leftFarReading>200)
      {    
         delay(leapTime-30);
         
         readSensors();
         
         if(rightFarReading>200 && leftFarReading>200)
         {
           done();
         }
         else
         {
           turnLeft();
           return;
         }
      }
      delay(leapTime-30);
      
      readSensors();
      
      if(leftFarReading<200 && leftCenterReading<200 && rightCenterReading<200 && rightFarReading<200)
      {  
         turnRight();
         return;
      }
      path[pathLength]='S';
      // Serial.println("s");
      pathLength++;
      //Serial.print("Path length: ");
      //Serial.println(pathLength);
      if(path[pathLength-2]=='B')
      {
         //Serial.println("shortening path");
         shortPath();
      }
      straight();
   } 
      
   readSensors();
   
   if(leftFarReading<200 && leftCenterReading<200 && rightCenterReading<200 && rightFarReading<200 && leftNearReading<200 && rightNearReading<200)
   {
     turnAround();
   }

}  


    
void done()
{
   digitalWrite(leftMotor1, LOW);  //STOP THE ROBOT
   digitalWrite(leftMotor2, LOW);
   digitalWrite(rightMotor1, LOW);
   digitalWrite(rightMotor2, LOW);
   analogWrite(enable1,200);          
   analogWrite(enable2,200);          
   
   replaystage=1;
   
   path[pathLength]='D';
   pathLength++;
   
    while(analogRead(leftFarSensor)>200)
   {
      digitalWrite(led, LOW);
      delay(150);
      digitalWrite(led, HIGH);
      delay(150);
   }
   delay(500);
   
   replay();
}
  


void turnLeft()
{
    while(analogRead(rightCenterSensor)>200||analogRead(leftCenterSensor)>200)
    {
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, HIGH);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(2);
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(1);
    }
    
    while(analogRead(rightCenterSensor)<200)   //BRING IT BACK ON LINE
    {
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, HIGH);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(2);
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(1);
    }
 
    if(replaystage==0)
    {
      path[pathLength]='L';
      //Serial.println("l");
      pathLength++;
      //Serial.print("Path length: ");
      //Serial.println(pathLength);
      if(path[pathLength-2]=='B')
      {
        //Serial.println("shortening path");
        shortPath();
      }
    }  
}



void turnRight()
{
   while(analogRead(rightCenterSensor)>200)
   {
     digitalWrite(leftMotor1, HIGH);
     digitalWrite(leftMotor2, LOW);
     digitalWrite(rightMotor1, LOW);
     digitalWrite(rightMotor2, HIGH);
     analogWrite(enable1,200);          
     analogWrite(enable2,200);          
     delay(2);
     digitalWrite(leftMotor1, LOW);
     digitalWrite(leftMotor2, LOW);
     digitalWrite(rightMotor1, LOW);
     digitalWrite(rightMotor2, LOW);
     analogWrite(enable1,200);          
     analogWrite(enable2,200);          
     delay(1);
   }
   while(analogRead(rightCenterSensor)<200)
   {
     digitalWrite(leftMotor1, HIGH);
     digitalWrite(leftMotor2, LOW);
     digitalWrite(rightMotor1, LOW);
     digitalWrite(rightMotor2, HIGH);
     analogWrite(enable1,200);          
     analogWrite(enable2,200);          
     delay(2);
     digitalWrite(leftMotor1, LOW);
     digitalWrite(leftMotor2, LOW);
     digitalWrite(rightMotor1, LOW);
     digitalWrite(rightMotor2, LOW);
     analogWrite(enable1,200);          
     analogWrite(enable2,200);          
     delay(1);
   }
   while(analogRead(leftCenterSensor)<200)
   {
     digitalWrite(leftMotor1, HIGH);
     digitalWrite(leftMotor2, LOW);
     digitalWrite(rightMotor1, LOW);
     digitalWrite(rightMotor2, HIGH);
     analogWrite(enable1,200);          
     analogWrite(enable2,200);          
     delay(2);
     digitalWrite(leftMotor1, LOW);
     digitalWrite(leftMotor2, LOW);
     digitalWrite(rightMotor1, LOW);
     digitalWrite(rightMotor2, LOW);
     analogWrite(enable1,200);          
     analogWrite(enable2,200);          
     delay(1);
   }
  if(replaystage==0)
  {
    path[pathLength]='R';
    //Serial.println("r");
    pathLength++;
    //Serial.print("Path length: ");
    //Serial.println(pathLength);
    if(path[pathLength-2]=='B')
    {
      //Serial.println("shortening path");
      shortPath();
    }
  }
 
}


void turnAround()
{
   digitalWrite(leftMotor1, HIGH);      //MOVE THE BOT AN INCH FORWARD
   digitalWrite(leftMotor2, LOW);
   digitalWrite(rightMotor1, HIGH);
   digitalWrite(rightMotor2, LOW);
   analogWrite(enable1,200);          
   analogWrite(enable2,200);          
   delay(150);
   
   while(analogRead(leftCenterSensor)<200)   //IF IT SHOWS WHITE
   {
      digitalWrite(leftMotor1, LOW);     //BOT REVERSES DIRECTION
      digitalWrite(leftMotor2, HIGH);
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(2);
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, LOW);
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, LOW);
     analogWrite(enable1,200);          
      analogWrite(enable2,200);          
      delay(1);
    }
    
   path[pathLength]='B';
   pathLength++;
   straight();
   Serial.println("b");
   Serial.print("Path length: ");
   Serial.println(pathLength);
}



void shortPath()
{
   int shortDone=0;
   
   if(path[pathLength-3]=='L' && path[pathLength-1]=='R')
   {
     pathLength-=3;
     path[pathLength]='B';
     shortDone=1;
   }
   
   if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0)
   {
     pathLength-=3;
     path[pathLength]='R';
     shortDone=1;
    }
   
   if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0)
   {
     pathLength-=3;
     path[pathLength]='B';
     shortDone=1;
   }
  
   if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0)
   {
     pathLength-=3;
     path[pathLength]='R';
     shortDone=1;
   }
     
   if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0)
   {
     pathLength-=3;
     path[pathLength]='B';
     shortDone=1;
   }
    
   if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0)
   {
     pathLength-=3;
     path[pathLength]='S';
     shortDone=1;
   }
    
   path[pathLength+1]='D';
   path[pathLength+2]='D';
   pathLength++;
   //Serial.print("Path length: ");
   //Serial.println(pathLength);
   //printPath();
}




void printPath()
{
  Serial.println("+++++++++++++++++");
  int x;
  while(x<=pathLength)
  {
    Serial.println(path[x]);
    x++;
  }
  Serial.println("+++++++++++++++++");
}


void replay()
{
   readSensors();
   if(leftFarReading<200 && rightFarReading<200)
   {
      straight();
   }
   else
   {
     if(path[readLength]=='D')
     {
       digitalWrite(leftMotor1, HIGH);
       digitalWrite(leftMotor2, LOW);
       digitalWrite(rightMotor1, HIGH);
       digitalWrite(rightMotor2, LOW);
       analogWrite(enable1,200);          
       analogWrite(enable2,200);          
       delay(100);
       digitalWrite(leftMotor1, LOW);
       digitalWrite(leftMotor2, LOW);
       digitalWrite(rightMotor1, LOW);
       digitalWrite(rightMotor2, LOW);
       analogWrite(enable1,200);          
       analogWrite(enable2,200);          
       endMotion();
     }
     
     if(path[readLength]=='L')
     {
       digitalWrite(leftMotor1, HIGH);
       digitalWrite(leftMotor2, LOW);
       digitalWrite(rightMotor1, HIGH);
       digitalWrite(rightMotor2, LOW);
       analogWrite(enable1,200);          
       analogWrite(enable2,200);          
       delay(leapTime);
       turnLeft();
     }
     
     if(path[readLength]=='R')
     {
       digitalWrite(leftMotor1, HIGH);
       digitalWrite(leftMotor2, LOW);
       digitalWrite(rightMotor1, HIGH);
       digitalWrite(rightMotor2, LOW);
      analogWrite(enable1,200);          
      analogWrite(enable2,200);          
       delay(leapTime);
       turnRight();
     }
     
     if(path[readLength]=='S')
     {
       digitalWrite(leftMotor1, HIGH);
       digitalWrite(leftMotor2, LOW);
       digitalWrite(rightMotor1, HIGH);
       digitalWrite(rightMotor2, LOW);
       analogWrite(enable1,200);          
      analogWrite(enable2,200);          
       delay(leapTime);
       straight();
     }
     
    readLength++;
    
  }
    
  replay();
  
}

void endMotion()
{
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(200);
      digitalWrite(led, LOW);
    delay(200);
    digitalWrite(led, HIGH);
    delay(500);
    endMotion();
}


