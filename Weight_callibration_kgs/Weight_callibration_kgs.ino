#include "HX711.h"  //You must have this library in your arduino library folder
 
#define DOUT  2
#define CLK  3
 
HX711 scale(DOUT, CLK);
 
//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = -38560.00; //-106600 worked for my 40Kg max scale setup 
float zero_factor=445695;

float wt;
//=============================================================================================
//                         SETUP
//=============================================================================================

void setup() {
  Serial.begin(9600);  
  
  
  scale.set_scale(); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.set_offset(zero_factor); //Zero out the scale using a previously known zero_factor
  scale.tare();
    
}

//=============================================================================================
//                         LOOP
//=============================================================================================
void loop() {
  scale.set_scale(calibration_factor);
  
//  for(int i=0;i<=9;i++)
//       wt+=scale.get_units();
//          
//  wt/=10;
  
  //wt-=0.2; // error manipulation
  
  wt=scale.get_units();
  //wt=wt*0.453592; // lbs to kgs
  
  Serial.print("Weight: ");
  Serial.print(wt,3);  //Up to 3 decimal points
  Serial.println(" kgs"); //Change this to kg and re-adjust the calibration factor if you follow lbs
  
  wt=0;
  
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == 't' || temp == 'T')
      scale.tare();  //Reset the scale to zero      
  }
}
