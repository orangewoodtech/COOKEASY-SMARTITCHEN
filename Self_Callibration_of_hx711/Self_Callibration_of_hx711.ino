

#include "HX711.h"  //You must have this library in your arduino library folder

#define DOUT  2
#define CLK  3

HX711 scale(DOUT, CLK);

//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = -38000.00; //-106600 worked for my 40Kg max scale setup 

//=============================================================================================
//                         SETUP
//=============================================================================================
void setup() {
  Serial.begin(9600);
  Serial.println("HX711 Calibration");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press a,s,d,f to increase calibration factor by 10,100,1000,10000 respectively");
  Serial.println("Press z,x,c,v to decrease calibration factor by 10,100,1000,10000 respectively");
  Serial.println("Press t for tare");
  
  scale.set_scale();
  //scale.set_offset(578162);  // 578162
  scale.tare(); //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

//=============================================================================================
//                         LOOP
//=============================================================================================
void loop() {
float tw=3.450;  // in kgs

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  Serial.print(scale.get_units(10), 3);
  Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" calibration_factor: ");
  //Serial.print(calibration_factor);
  Serial.println();

if(Serial.available())
{ Serial.println(" self callibrating");
  if(scale.get_units(10)*-1 <= tw)
   { Serial.println(calibration_factor); 
     }
 else calibration_factor-=10;
}
 
  
}
//=============================================================================================
