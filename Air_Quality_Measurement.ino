#include <MQUnifiedsensor.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO

#define MQ135S A3
#define MQ6S A1
#define MQ7S A0
#define dhtS 7
#define MQ135th 2
#define MQ6th 3
#define MQ7th 4
#define MQ4th 5
#define buzzPin 11

#define MQ4S A2

MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ135S, "MQ-135");
MQUnifiedsensor MQ7(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ7S, "MQ-7");
MQUnifiedsensor MQ4(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ4S, "MQ-4");
MQUnifiedsensor MQ6(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ6S, "MQ-6");

#define         RatioMQ6CleanAir          (5) //RS / R0 = 5 ppm 
#define         RatioMQ4CleanAir          (5) //RS / R0 = 5 ppm 
#define         RatioMQ135CleanAir        (3.6) //RS / R0 = 10 ppm 
#define         RatioMQ7CleanAir          (5) //RS / R0 = 27.5 ppm  

float    MQ6calcR0 = 0,
         MQ4calcR0 = 0,
         MQ135calcR0 = 0,
         MQ7calcR0 = 0;

// FOR DHT ----------------------------------->
#define DHTTYPE  DHT11     // DHT 11
DHT dht(dhtS, DHTTYPE);



void setup () {
  Serial.begin(9600);
  pinMode(MQ135S,INPUT);
  pinMode(MQ6S,INPUT);
  pinMode(MQ7S,INPUT);
  pinMode(dhtS,INPUT);
  pinMode(MQ4S,INPUT);

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);

  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);

  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);


  calb();

  MQ135Setup();
  MQ7Setup();
  MQ4Setup();
  MQ6Setup();
  dht.begin();

}


  
// For CO Carbon monoxide setup
String gName = " ";

void CORead(){
   float sensor_volt;
   float RS_gas; // Get value of RS in a GAS
   float R0 = 10.81; //example value of R0. Replace with your own
   float ratio; // Get ratio RS_GAS/RS_air

 
   gName= " ";
   Serial.println("CO MQ7 "); 
   sensor_volt=(float)(analogRead(MQ7S )/1024)*5.0;
   RS_gas = (5.0-sensor_volt)/sensor_volt;
   ratio = RS_gas/R0;
   float x = 1538.46*ratio ;
   float CO_ppm = pow(x,-1.709);//LPG PPM
   MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
   gName = PPMPercentage( CO_ppm,gName);
   checkThreshold(7);

}

 // FOR Alcohol
 void AlcoholRead(){ 
  gName = " ";
     Serial.println("ALCOHOL MQ135"); 
    // for MQ135
   MQ135.setA( 77.255); MQ135.setB(-3.18 ); // Configure the equation to to calculate NH4 concentration
   MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
   gName = PPMPercentage( MQ135.readSensor() ,gName);
   checkThreshold(135);
}


// FOR C02 carbon dioxide setup
void CO2Read(){
  gName = " ";
 Serial.println("CO2 Carboon dioxide MQ135"); 
  // for MQ135
 MQ135.setA( 110.47); MQ135.setB(-2.862 ); 
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
 float co2ppm = map(MQ135.readSensor(),0,1023,400,5000);   
 gName=PPMPercentage( co2ppm ,gName);

checkThreshold(135);
}


// FOR Toulen
void ToulenRead(){
  gName=" ";
  Serial.println("TOULEN MQ135"); 
    // for MQ135
  MQ135.setA(44.947); MQ135.setB(-3.445 ); // Configure the equation to to calculate NH4 concentration
  MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
  gName=PPMPercentage( MQ135.readSensor() ,gName);
  checkThreshold(135);
}
// For NH4 Ammonium
void NH4Read(){
  gName = " ";
  Serial.println("AMMONIA NH4 MQ135"); 
    // for MQ135
  MQ135.setA( 102.2); MQ135.setB(-2.473 ); // Configure the equation to to calculate NH4 concentration
  MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
  gName = PPMPercentage( MQ135.readSensor() ,gName);
  checkThreshold(135);
 

}

 // FOR Aceaton
 void AceatonRead(){ 
  gName = " ";
  Serial.println("ACEATON MQ135"); 
    // for MQ135
  MQ135.setA( 34.668); MQ135.setB(-3.369 ); // Configure the equation to to calculate NH4 concentration
  MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
  gName = PPMPercentage( MQ135.readSensor() ,gName);
  checkThreshold(135);
}

// FOR CH4
void Ch4Read(){
    Serial.println("CH4 MQ4"); 
    MQ4.setA(1012.7); MQ4.setB(-2.786); //CH4
    MQ4.update();
    gName = PPMPercentage( MQ4.readSensor() ,gName);
    checkThreshold(4);
}

// FOR LPG
void LPGRead(){
   float sensor_volt;
   float RS_gas; // Get value of RS in a GAS
   float R0 = 10.81; //example value of R0. Replace with your own
   float ratio; // Get ratio RS_GAS/RS_air
   float LPG_PPM;
 
   gName= " ";
   Serial.println("LPG MQ6 "); 
   sensor_volt=(float)(analogRead(MQ6S )/1024)*5.0;
   RS_gas = (5.0-sensor_volt)/sensor_volt;
   ratio = RS_gas/R0;
   float x = 1000*ratio ;
   LPG_PPM = pow(x,-1.431);//LPG PPM
   gName = PPMPercentage(LPG_PPM,gName);
   checkThreshold(6);
}

// FOR Smoke
void SmokeRead(){
  gName =" ";
  Serial.println("SMOKE MQ4"); 
 // FOR MQ4
  MQ4.setA(30000000 ); MQ4.setB(-8.308); // Configure the equation to to calculate NH4 concentration
  MQ4.update(); // Update data, the arduino will read the voltage from the analog pin
  gName =PPMPercentage( MQ4.readSensor() ,gName);
  checkThreshold(4);
  }


// For H2
void H2Read(){
  gName = " ";
  Serial.println("H2  MQ7"); 
  MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
  gName =PPMPercentage( MQ7.readSensor() ,gName);
  checkThreshold(7);
  
}

// SETIP ALL SENSRS

void MQ6Setup(){

  MQ6.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ6.setA(2127.2); MQ6.setB(-2.526); // Configure the equation to to calculate CH4 concentration 
    MQ6.init();

}
void MQ4Setup(){

  //Set math model to calculate the PPM concentration and the value of constants
  MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ4.setA(1012.7); MQ4.setB(-2.786); // Configure the equation to to calculate CH4 concentration
      MQ4.init();

}
void MQ7Setup(){

  MQ7.setRegressionMethod(1); //_PPM =  a*ratio^b
        MQ7.init();
}
void MQ135Setup(){
  
  //Set math model to calculate the PPM concentration and the value of constants
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.setA(102.2); MQ135.setB(-2.473); // Configure the equation to to calculate NH4 concentration
  //Remarks: Configure the pin of arduino as input.
    MQ135.init(); 

}

void dht11(){
   // Get temperature event and print its value.
    Serial.println(F("Temperature °C "));
    Serial.println(dht.readTemperature());
  // Get humidity event and print its value.
    Serial.println(F("Humidity % "));
    Serial.println(dht.readHumidity());

}


// GET PPM PERCENTAGE
String PPMPercentage(float sensorValue, String gasName){
  gasName = sensorValue;
  Serial.println(gasName);
  return gasName;
}

// Check for threshold value
void checkThreshold(int pin){
   
  if(pin==135){
      if(digitalRead(MQ135th)==0){
    //play buzzer
     analogWrite(buzzPin,135);
     
  }
  }
  if(pin == 6){
          
          if(digitalRead(MQ6th)==0){
    //play buzzer
         analogWrite(buzzPin,60);

  }
  }
  if(pin == 4){
              
          if(digitalRead(MQ4th==0))                                                                                                                                                                                                                                                                                                                                                         {
    //play buzzer
         analogWrite(buzzPin,160);

  }
  }
  if(pin ==7){
             
          if(digitalRead(MQ7th==0)){
    //play buzzer
         analogWrite(buzzPin,210);

  }
  }
  
}

// For setting Ro value
void setRo(){
   MQ6.setR0(10.81);
  MQ4.setR0(1.27);
  MQ135.setR0(16.42);
  MQ7.setR0(12.72);
}

// FOR CALIBRATION
void calb(){
//   // put your setup code here, to run once:
//Serial.begin(9600);
//Set math model to calculate the PPM concentration and the value of constants
//  MQ6.setRegressionMethod(1); //_PPM =  a*ratio^b
//  MQ6.init(); 
//
//    MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
//  MQ4.init(); 
//
//    MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
//  MQ135.init(); 
//
//    MQ7.setRegressionMethod(1); //_PPM =  a*ratio^b
//  MQ7.init(); 
////  
/////*While calibrating Your sensor Uncomment this calibration portion and calibrate for R0.*/
////  /*****************************  MQ CAlibration ********************************************/
//  Serial.print("Calibrating please wait.");
//  for (int i = 1; i <= 10; i ++)
//  {
//    //Update the voltage lectures
//    MQ6.update();
//    MQ4.update();
//    MQ135.update();
//    MQ7.update();
//
//    MQ6calcR0 += MQ6.calibrate(RatioMQ6CleanAir);
//    MQ4calcR0 += MQ4.calibrate(RatioMQ4CleanAir);
//    MQ135calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
//    MQ7calcR0 += MQ7.calibrate(RatioMQ7CleanAir);
//
//    Serial.print(".");
//  }
//
////
//  Serial.println("  done!.");
//
//  Serial.print("(MQ6 - MQ7):");
//  Serial.print(MQ6calcR0 / 10); Serial.print(" | ");
//  Serial.print(MQ4calcR0 / 10); Serial.print(" | ");
//  Serial.print(MQ135calcR0 / 10); Serial.print(" | ");
//  Serial.print(MQ7calcR0 / 10); Serial.print(" | ");
//
   setRo();
  /*****************************  MQ CAlibration ********************************************/ 
}

int count = 0;
void loop() {
Serial.println("Reading Sensor Vlaues");
H2Read();
CORead();
AlcoholRead();
NH4Read();
AceatonRead();
LPGRead();
SmokeRead();
ToulenRead();
CO2Read();
dht11();
count++;
delay(3000);

if(count==11){
  Serial.println("1 Hour");
  count=0;
  delay(1000);
}

}
