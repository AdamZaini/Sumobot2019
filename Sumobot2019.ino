//LIBRARIES
#include <MD25IIC.h>
#include <Wire.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <boarddefs.h>
#include <IRremoteInt.h>
#include <IRremote.h>
#include <Ultrasonic.h>

MD25IIC MyBoard;

//PINS
int RECV_PIN = 11;
#define sensor A0
#define sensor1 A1
Ultrasonic ultraleft(9,8);   // (Trig PIN,Echo PIN)
Ultrasonic ultraright(7,6);  // (Trig PIN,Echo PIN)
Ultrasonic ultramid(5,4);  // (Trig PIN,Echo PIN)

//DEFINITIONS
IRrecv irrecv(RECV_PIN);
decode_results results;

//SETUP
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  MyBoard.enableTimeOut(false);    // Stop motor if no command sent
  MyBoard.enableController(true); // Enable On-board speed controller
  MyBoard.resetEncoders();  
}

//MAIN CODE
void loop() {

  if (irrecv.decode(&results))
  {
    unsigned long start = millis();
    Serial.println("Signal Received");
    while(1)
    {
      unsigned long current = millis();
      unsigned long difference = current - start;
      Serial.println(difference);
      delay(50);
      if(difference < 120000)
      {
        int reading = analogRead(sensor);
        int reading1 = analogRead(sensor1);
        int leftdist = ultraleft.Ranging(CM);
        int rightdist = ultraright.Ranging(CM);
        int middist = ultramid.Ranging(CM);
        // Wait some time
        delay(50);
        if(reading < 400 || reading1 < 400)
        {
          Reverse(10,2);
          TurnBack(10,23);
          delay(50);
        }
        else
        {
          if(leftdist < 15)
          {
            AngleCCW(10,23);
            delay(50);
          }
          else if(rightdist < 15)
          {
            AngleCW(10,23);
            delay(50);
          }
          else if(middist < 15)
          {
            Strike();
            delay(50);
          }
          else
          {
            MoveForward();
            delay(50);
          }
        }
      }
      else
      {
        break;
      }
    }
    Stop();
    delay(100000);
  }
}




//FUNCTIONS


//**********************************************************//

int FindRev(int wd, int dist) 
{
    int rev = round((dist/(PI*wd))*360+1);
    return rev;  
}

//*********************************************************//

void Travel(int wd, int dist)
{ 
    int w = FindRev(wd, dist);
    while(1)
    {
      int Val = MyBoard.getMotor1Encoder();
      if(Val > -w){
          MoveForward();         
      }
      else{
          Stop();
          MyBoard.resetEncoders();
          break; 
      }
      Serial.println(MyBoard.getMotor1Encoder()); // Print data
    }
}

void Reverse(int wd, int dist)
{ 
    int x = FindRev(wd, dist);
    while(1)
    {
      int Val = MyBoard.getMotor1Encoder();
      if(Val < x){
          MoveBackward();         
      }
      else{
          Stop();
          MyBoard.resetEncoders();
          break; 
      }
      Serial.println(MyBoard.getMotor1Encoder()); // Print data
    }
}

//*********************************************************//

void AngleCW(int wd, int r_len)
{
    unsigned long cir = (0.25)*PI*r_len;
    int y = round((cir/(PI*wd))*360+1);
    while(1)
    {
      int Val = MyBoard.getMotor1Encoder();
      if(Val < y)
      {
          RotateCW();
      }
      else
      {
          Stop();
          MyBoard.resetEncoders();
          break;
      }
      //Serial.println(MyBoard.getMotor1Encoder());
    }   
}

void AngleCCW(int wd, int r_len)
{
    unsigned long cir = (0.25)*PI*r_len;
    int z = round((cir/(PI*wd))*360+1);
    while(1)
    {
      int Val = MyBoard.getMotor1Encoder();
      if(Val > -z)
      {
          RotateCCW();
      }
      else
      {
          Stop();
          MyBoard.resetEncoders();
          break;
      }
      //Serial.println(MyBoard.getMotor1Encoder());
    }   
}

void TurnBack(int wd, int r_len)
{
    unsigned long cir = (0.5)*PI*r_len;
    int z = round((cir/(PI*wd))*360+1);
    while(1)
    {
      int Val = MyBoard.getMotor1Encoder();
      if(Val > -z)
      {
          RotateCCW();
      }
      else
      {
          Stop();
          MyBoard.resetEncoders();
          break;
      }
      //Serial.println(MyBoard.getMotor1Encoder());
    }   
}


//*********************************************************//

void Stop() 
{
    MyBoard.setMotor1Speed(128);
    MyBoard.setMotor2Speed(128);
}

void Strike() 
{
    MyBoard.setMotor1Speed(0);
    MyBoard.setMotor2Speed(0);
}

void MoveForward() 
{
    MyBoard.setMotor1Speed(110);
    MyBoard.setMotor2Speed(110);
}

void MoveBackward() 
{
     MyBoard.setMotor1Speed(181);
     MyBoard.setMotor2Speed(181);
}

void RotateCCW() 
{
     MyBoard.setMotor1Speed(75);
     MyBoard.setMotor2Speed(181);    
}

void RotateCW() 
{
     MyBoard.setMotor1Speed(181);
     MyBoard.setMotor2Speed(75);    
}

//*********************************************************//

