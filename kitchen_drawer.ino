#include "HX711.h"
#define DOUT 2
#define CLK 3

HX711 scale(DOUT, CLK);
float calibration_factor = -38560; //-106600 worked for my 40Kg max scale setup 
float zero_factor=445695;

int r1 = 10; // pins for limit switch
int r2 = 7;  // pins for limit switch
int r3 = 8;  // pins for limit switch

int dop1, dop2, dop3; // flags for drawer open
float tw, w1, w2, w3; // total and individual weights
float cw1, cw2, cw3; // calculation for individual weights of drawers

void setup()
{ pinMode(r1,INPUT); digitalWrite(r1,0);  // initializing the IR sensors to input and pull down
  pinMode(r2,INPUT); digitalWrite(r2,0);
  pinMode(r3,INPUT); digitalWrite(r3,0);
  Serial.begin(9600);
  
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.set_offset(zero_factor); //Zero out the scale using a previously known zero_factor
  scale.tare(); // Set the scale to zero
}

void loop()
{ 
  if (digitalRead(r1) == 1 && digitalRead(r2) == 1 && digitalRead(r3) == 1)
    { Serial.print("all OPEN  "); Serial.println(scale.get_units(5), 3);}
   

 
 //------------------------------------------------------------------
 
 
 
 if (digitalRead(r1) == 1 && dop1 == 1) // set drawer1 open flag
 { dop1 = 0;
  Serial.println("drawer 1 open");
 }

 if (digitalRead(r2) == 1 && dop2 == 1) // set drawer2 open flag
 {
   dop2 = 0;  
   Serial.println("drawer 2 open");
 }
 if (digitalRead(r3) == 1 && dop3 == 1)  // set drawer3 open flag
 {   dop3 = 0;
  Serial.println("drawer 3 open");
 }
 
 
//------------------------------------------------------------------

if (digitalRead(r1) == 0 && dop1 == 0)  // drawer close
 { cw1=0;
   w1=-2*scale.get_units(5);      // measure current weight again
   cw1=tw-w1; cw1=abs(cw1);
   Serial.println("drawer 1 close  ");
  // Serial.println(cw1); //calculate weight 1 i.e previous - current
   dop1=1;     delay(1000);                    //set drawer open flag to 1
 }            
//----
if (digitalRead(r2) == 0 && dop2 == 0)  // drawer close
 { cw2=0; 
  w2=-2*scale.get_units(5);      // measure current weight again
   cw2=tw-w2;  cw2=abs(cw2);
   Serial.println("drawer 2 close  "); //delay(1000);
   //Serial.println(cw2); //calculate weight 1 i.e previous - current
   dop2=1;         delay(1000);                 //set drawer open flag to 1
 }      

//-------
if (digitalRead(r3) == 0 && dop3 == 0)  // drawer close
 { cw3=0; 
  w3=-2*scale.get_units(5);      // measure current weight again
   cw3=tw-w3;   cw3=abs(cw3);
   Serial.println("drawer 3 close  "); //delay(1000);
   //Serial.println(cw3); //calculate weight 1 i.e previous - current
   dop3=1;         delay(1000);                //set drawer open flag to 1
 }

if (digitalRead(r1) == 0 && digitalRead(r2) == 0 && digitalRead(r3) == 0)
   {
     //Serial.print("all CLOSE- MEASURING WEIGHT   ");
     tw=-2* scale.get_units(5);  // in kg
    // Serial.print("total weight--> ");
    // Serial.println(tw);
   }        
Serial.print(digitalRead(r1)); Serial.print(digitalRead(r2)); Serial.print(digitalRead(r3));
Serial.print("  D1-->"); Serial.print(cw1);  Serial.print("  D2-->"); Serial.print(cw2);  Serial.print("  D3-->"); Serial.print(cw3);
Serial.print("  TW-->"); Serial.println(-2*scale.get_units(5));
//cw1=0; cw2=0; cw3=0;
}


