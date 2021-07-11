#include <Arduino_APDS9960.h>

const int pin1 = 3;//MID-left sensor //0
const int pin2 = 5;//MID-right sensor //1
const int pin3 = 6;//right //2
const int pin4 = 7;//left //3

const int enR = 10; // right motor
const int in1 = 8 ;
const int in2 = 11 ;

const int in3 = 12 ;//left motor
const int in4 = 13 ;
const int enL = 9;                      

 //int num [4]={pin1,pin2,pin3,pin4};
 int midL = pin1;
 int midR = pin2;
 int Right = pin3;
 int Left = pin4;
 
  int count = 0;
  int check;
  int prev=0;
  int Res=15;
//  stright_count=0;
  

 const int motorR = 160;
 const int motorL = motorR*1;

// rgb
int red_out=A0;
int green_out=A1;
int blue_out=A3;
int proximity;
 int r, g, b;


void setup() {
  
 //מנועים
 pinMode(in1, OUTPUT );
 pinMode(in2, OUTPUT) ;
 pinMode(enR, OUTPUT) ;
 pinMode(in3, OUTPUT) ;
 pinMode(in4, OUTPUT) ;
 pinMode(enL, OUTPUT) ;

//חיישנים
 pinMode(pin1,INPUT);
 pinMode(pin2,INPUT);
 pinMode(pin3,INPUT);
 pinMode(pin4,INPUT);

  if (!APDS.begin()) {
   //Serial.println("Error initializing APDS9960 sensor!");
  }
}

void loop() {

//rgb
if (APDS.proximityAvailable()) 
  {
     proximity = APDS.readProximity();

  }
    analogWrite(green_out,0);
    analogWrite(blue_out,0);
    analogWrite(red_out,0);
 if(proximity<215)
 {
  STOP();
  turn_light();
 }

 if(count == 0)
 {
delay (2000);
 }
 count++;


 midL = digitalRead(pin1);
 midR = digitalRead(pin2);
 Right = digitalRead(pin3);
 Left = digitalRead(pin4);


Res = ((Left*2)*4) + ((midL*2)*2) + ((midR*2)*1) + (Right);

if ( Res==5||Res==9||Res==10||Res==11||Res==13)
{
  Res=prev;
  
}


switch (Res)
{ 


case 1:
  Right_hard ();
  break;

case 2:
  Right_weak();
  break;

case 3:
   Right_weak();
  break;

case 4:
  Left_weak();
  break;
  
case 6:
  Straight();
  break;

case 7:
  Right_hard ();
  break;

case 8:
  Left_hard();
  break;

case 12:
   Left_weak();
  break;


case 14:
  Left_hard();
  break;

case 15:
  Straight();
  break;

default:
  break;
  
}
prev = Res;

}




 /////////////////right_weak/////////////////////
  void Right_weak ()
  {
    do{
   // RIGHT
 digitalWrite(in1, HIGH) ;
 digitalWrite(in2, LOW) ;
// LEFT
 digitalWrite(in3, LOW) ;
 digitalWrite(in4, HIGH) ;


 analogWrite(enR,  motorL*1.3) ;
 analogWrite(enL, 0) ;
 
 midL = digitalRead(pin1);
 midR = digitalRead(pin2);
 Right = digitalRead(pin3);
 Left = digitalRead(pin4);
if(midL==0&& midR==0&& Right==0&&Left==0)
{prev=6;
  break;
}
} while(midL == 0 || midR == 0 );


 }

 ///////////////stop////////////////////////
  void STOP()
  {

 // RIGHT
 digitalWrite(in1, LOW) ;
 digitalWrite(in2,HIGH) ;
// LEFT
 digitalWrite(in3, HIGH) ;
 digitalWrite(in4, LOW) ;

 analogWrite(enL, motorL) ;
 analogWrite(enR, motorR) ;
 delay(6);
 
 analogWrite(enL, 0) ;
 analogWrite(enR, 0) ;
 }

 ///////////////Straight//////////////////
  void Straight()
  {
//Serial.println("Straight");
 // RIGHT
 digitalWrite(in1, HIGH) ;
 digitalWrite(in2, LOW) ;
// LEFT
 digitalWrite(in3, LOW) ;
 digitalWrite(in4, HIGH) ;
 
 analogWrite(enL, motorL) ;
 analogWrite(enR, motorR) ;

 }
/////////////////////////////////////////

/////////////////left_weak//////////////
  void Left_weak ()
  {
    

 // Serial.println("Left Weak ");
  do{
     // RIGHT
 digitalWrite(in1, HIGH) ;
 digitalWrite(in2, LOW ) ;
// LEFT
 digitalWrite(in3, LOW) ;
 digitalWrite(in4, HIGH) ;
 
 analogWrite(enL,  motorR*1.3) ;
 analogWrite(enR, 0) ;

  midL = digitalRead(pin1);
 midR = digitalRead(pin2);
 Right = digitalRead(pin3);
 Left = digitalRead(pin4);
if(midL==0&& midR==0&& Right==0&&Left==0)
{prev=6;
  break;
}
 

} while(midL == 0 || midR == 0);


 }
 /////////////////right_hard//////////////////////
  void Right_hard ()
  {
    delay(10);
   if(avarg()==15) return;
   
do{
  // RIGHT
 digitalWrite(in1, LOW ) ;
 digitalWrite(in2, HIGH) ;
// LEFT
 digitalWrite(in3, LOW) ;
 digitalWrite(in4, HIGH) ;
 
 analogWrite(enL, motorL*1.5) ;
 analogWrite(enR, motorR*1.5) ;

 midL = digitalRead(pin1);
 midR = digitalRead(pin2);
 Right = digitalRead(pin3);
 
} while(midL == 0 || midR == 0 || midL == 1 && midR == 1 && Right == 1);
 digitalWrite(in1, HIGH) ;
 digitalWrite(in2, LOW) ;
// LEFT
 digitalWrite(in3, LOW) ;
 digitalWrite(in4, HIGH) ;
 
 analogWrite(enL, motorL*1.35);
 analogWrite(enR, motorR*1.35);
 delay(10);

}
 
 ///////////////////////////////////////////

 //////////////Left_Hard////////////////
 void Left_hard ()
  {
     delay(10);
   if(avarg()==15) return;
 
if(avarg()==15) return;
  do{
 // RIHGT
 digitalWrite(in1, HIGH) ;
 digitalWrite(in2, LOW) ;
// LEFT
 digitalWrite(in3, HIGH) ;
 digitalWrite(in4, LOW) ;

 
 analogWrite(enR, motorR*1.5) ;
 analogWrite(enL, motorL*1.5) ;
 
 midL = digitalRead(pin1);
 midR = digitalRead(pin2);
 Left = digitalRead(pin4);

} while(midL == 0 && midR == 0 || midL == 1 && midR == 1 && Left == 1);
 digitalWrite(in1, HIGH) ;
 digitalWrite(in2, LOW) ;
// LEFT
 digitalWrite(in3, LOW) ;
 digitalWrite(in4, HIGH) ;
 
 analogWrite(enL, motorL*1.35);
 analogWrite(enR, motorR*1.35);
 delay(10);
 }

 
 ///////////////rgb/////////////////////////
 void turn_light() {

    while (! APDS.colorAvailable()) {
    delay(5);
  }
  
  APDS.readColor(r, g, b);
 
    if(r>b&&r>g&&r>50)
  {
    digitalWrite(green_out,LOW);
    digitalWrite(blue_out,LOW);
    digitalWrite(red_out,HIGH);
  }
    if(g>b&&g>r&&g>50)
  {
    digitalWrite(green_out,HIGH);
    digitalWrite(blue_out,LOW);
    digitalWrite(red_out,LOW);
  }
     if(b>g&&b>r&&b>50)
  {
    digitalWrite(green_out,LOW);
    digitalWrite(blue_out,HIGH);
    digitalWrite(red_out,LOW);
  }
 delay(500);
  }

   ///////// avrg/////
 
  int avarg(){


 midL = digitalRead(pin1);
 midR = digitalRead(pin2);
 Right = digitalRead(pin3);
 Left = digitalRead(pin4);

//if (flag != 1)

Res = ((Left*2)*4) + ((midL*2)*2) + ((midR*2)*1) + (Right);


return Res;
  }
