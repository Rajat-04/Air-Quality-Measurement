#include <MQUnifiedsensor.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm  

#define MQ135S A3
#define MQ6S A1
#define MQ7S A0
#define dhtS 7
#define MQ4S A2

MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ135S, "MQ-135");
MQUnifiedsensor MQ7(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ7S, "MQ-7");
MQUnifiedsensor MQ4(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ4S, "MQ-4");
MQUnifiedsensor MQ6(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ6S, "MQ-6");

#define         RatioMQ6CleanAir          (5) //RS / R0 = 5 ppm 
#define         RatioMQ4CleanAir          (5) //RS / R0 = 5 ppm 
#define         RatioMQ135CleanAir        (3.6) //RS / R0 = 10 ppm 
#define         RatioMQ7CleanAir          (5) //RS / R0 = 27.5 ppm  


// FOR DHT ----------------------------------->
#define DHTTYPE  DHT11     // DHT 11
DHT dht(dhtS, DHTTYPE);

// Defining the threshold values
#define co2Th = 999;


void setup() {
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
  gName = " ";
     Serial.println("CO CarbonMonoxide MQ7"); 
// MQ-7
 MQ7.setA(99.042); MQ7.setB(-1.518); // Configure the equation to to calculate NH4 concentration
 MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
gName = PPMPercentage( MQ7.readSensor() ,gName);

}

 // FOR Alcohol
 void AlcoholRead(){ 
  gName = " ";
     Serial.println("ALCOHOL MQ135"); 
    // for MQ135
 MQ135.setA( 77.255); MQ135.setB(-3.18 ); // Configure the equation to to calculate NH4 concentration
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
gName = PPMPercentage( MQ135.readSensor() ,gName);
}


// FOR C02 carbon dioxide setup
void CO2Read(){
  gName = " ";
 Serial.println("CO2 Carboon dioxide MQ135"); 
  // for MQ135
 MQ135.setA( 110.47); MQ135.setB(-2.862 ); // Configure the equation to to calculate NH4 concentration
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
 float co2ppm = map(MQ135.readSensor(),0,1023,400,5000);   
 gName=PPMPercentage( co2ppm ,gName);


}


// FOR Toulen
void ToulenRead(){
  gName=" ";
     Serial.println("TOULEN MQ135"); 
    // for MQ135
 MQ135.setA(44.947); MQ135.setB(-3.445 ); // Configure the equation to to calculate NH4 concentration
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
gName=PPMPercentage( MQ135.readSensor() ,gName);

}

// For NH4 Ammonium
void NH4Read(){
  gName = " ";
   Serial.println("AMMONIA NH4 MQ135"); 
    // for MQ135
 MQ135.setA( 102.2); MQ135.setB(-2.473 ); // Configure the equation to to calculate NH4 concentration
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
gName = PPMPercentage( MQ135.readSensor() ,gName);

}

 // FOR Aceaton
 void AceatonRead(){ 
  gName = " ";
     Serial.println("ACEATON MQ135"); 
    // for MQ135
 MQ135.setA( 34.668); MQ135.setB(-3.369 ); // Configure the equation to to calculate NH4 concentration
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
gName = PPMPercentage( MQ135.readSensor() ,gName);
}

// FOR CH4
void Ch4Read(){
  Serial.println("CH4 MQ4"); 
    MQ4.setA(1012.7); MQ4.setB(-2.786); //CH4
    MQ4.update();
    gName = PPMPercentage( MQ4.readSensor() ,gName);
}

// FOR LPG
void LPGRead(){
  float sensor_volt;
float RS_gas; // Get value of RS in a GAS
float R0 = 15000; //example value of R0. Replace with your own
float ratio; // Get ratio RS_GAS/RS_air
float LPG_PPM;
 
  gName= " ";
   Serial.println("LPG MQ6 "); 
  sensor_volt=(float)analogRead(MQ6S )/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt;
    ratio = RS_gas/R0;
    float x = 1000*ratio ;
    LPG_PPM = pow(x,-1.431);//LPG PPM
    gName = PPMPercentage(LPG_PPM,gName);
}

// FOR Smoke
void SmokeRead(){
  gName =" ";
     Serial.println("SMOKE MQ4"); 
 // FOR MQ4
 MQ4.setA(30000000 ); MQ4.setB(-8.308); // Configure the equation to to calculate NH4 concentration
 MQ4.update(); // Update data, the arduino will read the voltage from the analog pin
gName =PPMPercentage( MQ4.readSensor() ,gName);
  
  }


// For H2
void H2Read(){
  gName = " ";
    Serial.println("H2  MQ7"); 

// MQ-7
 MQ7.setA(69.014); MQ7.setB(-1.374); 
 MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
gName =PPMPercentage( MQ7.readSensor() ,gName);
  
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
  MQ7.setA(99.042); MQ7.setB(-1.518); // Configure the equation to calculate CO concentration value
  //Remarks: Configure the pin of arduino as input.
    MQ7.setR0(3.39);
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
  Serial.print(gasName);
  return gasName;
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
//  float  MQ6calcR0 = 0,
//         MQ4calcR0 = 0,
//         MQ135calcR0 = 0,
//         MQ7calcR0 = 0;
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
  MQ6.setR0(10.71);
  MQ4.setR0(5.87);
  MQ135.setR0(5.25);
  MQ7.setR0(2.21);

//  Serial.println("  done!.");
//
//  Serial.print("(MQ6 - MQ7):");
//  Serial.print(MQ6calcR0 / 10); Serial.print(" | ");
//  Serial.print(MQ4calcR0 / 10); Serial.print(" | ");
//  Serial.print(MQ135calcR0 / 10); Serial.print(" | ");
//  Serial.print(MQ7calcR0 / 10); Serial.print(" | ");
//

  /*****************************  MQ CAlibration ********************************************/ 
}


int count = 0;
void loop() {
Serial.println("Reading Sensor Vlaues");
H2Read();
Serial.println();
CORead();
Serial.println();
AlcoholRead();
Serial.println();
NH4Read();
Serial.println();
AceatonRead();
Serial.println();
LPGRead();
Serial.println();
SmokeRead();
Serial.println();
ToulenRead();
Serial.println();
CO2Read();
Serial.println();
dht11();
count++;
delay(2000);

if(count==11){
  Serial.println("1 Hour");
  count=0;
  delay(1000);
}

}
