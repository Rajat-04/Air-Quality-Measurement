#include <MQUnifiedsensor.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm  

#define MQ135S A3
#define MQ6S A2
#define MQ7S A5
#define dhtS 9
#define MQ4S A0

MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ135S, "MQ-135");
MQUnifiedsensor MQ7(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ7S, "MQ-7");
MQUnifiedsensor MQ4(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ4S, "MQ-4");
MQUnifiedsensor MQ6(placa, Voltage_Resolution, ADC_Bit_Resolution, MQ6S, "MQ-6");

// FOR DHT ----------------------------------->
#define DHTTYPE    DHT11     // DHT 11
DHT_Unified dht(dhtS, DHTTYPE);

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


MQ135Setup();
MQ7Setup();
MQ4Setup();
MQ6Setup();
dht.begin();

}


  
// For CO Carbon monoxide setup
void CORead(){
  // for MQ135
 MQ135.setA(605.18); MQ135.setB(-3.937); // Configure the equation to to calculate NH4 concentration
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ135.readSensor();
 MQ135.serialDebug();

 // FOR MQ4
 MQ4.setA(200000000000000); MQ4.setB(-19.05); // Configure the equation to to calculate NH4 concentration
 MQ4.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ4.readSensor();
 MQ4.serialDebug();

  // FOR MQ6
 MQ6.setA(1000000000000000); MQ6.setB(-13.5); // Configure the equation to to calculate NH4 concentration
 MQ6.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ6.readSensor();
 MQ6.serialDebug();

  
// MQ-7
 MQ7.setA(99.042); MQ7.setB(-1.518); // Configure the equation to to calculate NH4 concentration
 MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ7.readSensor();
 MQ7.serialDebug();

}

 // For alcohol measuerement 
void AlcoholRead(){
   Serial.println("ALCOHOL MQ135"); 
    // for MQ135
 MQ135.setA( 77.25); MQ135.setB(-3.18 ); // Configure the equation to to calculate NH4 concentration
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ135.readSensor();
 MQ135.serialDebug();
   Serial.println("ALCOHOL MQ4"); 
 // FOR MQ4
 MQ4.setA(60000000000 ); MQ4.setB(-14.01); // Configure the equation to to calculate NH4 concentration
 MQ4.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ4.readSensor();
 MQ4.serialDebug();
   Serial.println("ALCOHOL MQ6"); 
  // FOR MQ6
 MQ6.setA(50000000); MQ6.setB(-6.017); // Configure the equation to to calculate NH4 concentration
 MQ6.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ6.readSensor();
 MQ6.serialDebug();

     Serial.println("ALCOHOL MQ7"); 
// MQ-7
 MQ7.setA(40000000000000000); MQ7.setB(-12.35); // Configure the equation to to calculate NH4 concentration
 MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ7.readSensor();
 MQ7.serialDebug();
}


// FOR C02 carbon dioxide setup
void CO2Read(){
 Serial.println("CO2 Carboon dioxide MQ135"); 
  // for MQ135
 MQ135.setA( 110.47); MQ135.setB(-2.862 ); // Configure the equation to to calculate NH4 concentration
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ135.readSensor();
 MQ135.serialDebug();

}


// FOR Toulen
void ToulenRead(){
     Serial.println("toulen MQ135"); 
    // for MQ135
 MQ135.setA(44.947); MQ135.setB(-3.445 ); // Configure the equation to to calculate NH4 concentration
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ135.readSensor();
 MQ135.serialDebug();

}

// For NH4 Ammonium
void NH4Read(){
   Serial.println("AMMONIA NH4 MQ135"); 
    // for MQ135
 MQ135.setA( 102.2); MQ135.setB(-2.473 ); // Configure the equation to to calculate NH4 concentration
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ135.readSensor();
 MQ135.serialDebug();

}

 // FOR Aceaton
 void AceatonRead(){ 
     Serial.println("ACETON MQ135"); 
    // for MQ135
 MQ135.setA( 34.668); MQ135.setB(-3.369 ); // Configure the equation to to calculate NH4 concentration
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ135.readSensor();
 MQ135.serialDebug();
}

// FOR LPG
void LPGRead(){
   Serial.println("LPG MQ4"); 
 // FOR MQ4
 MQ4.setA(1012.7 ); MQ4.setB(-2.786); // Configure the equation to to calculate NH4 concentration
 MQ4.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ4.readSensor();
 MQ4.serialDebug();
   Serial.println("LPG MQ6"); 
  // FOR MQ6
 MQ6.setA(1009.2); MQ6.setB(-2.35); // Configure the equation to to calculate NH4 concentration
 MQ6.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ6.readSensor();
 MQ6.serialDebug();

     Serial.println("LPG MQ7"); 
// MQ-7
 MQ7.setA(700000000); MQ7.setB(-7.703); // Configure the equation to to calculate NH4 concentration
 MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ7.readSensor();
 MQ7.serialDebug();
}

// FOR Smoke
void SmokeRead(){
     Serial.println("SMOKE MQ4"); 
 // FOR MQ4
 MQ4.setA(30000000 ); MQ4.setB(-8.308); // Configure the equation to to calculate NH4 concentration
 MQ4.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ4.readSensor();
 MQ4.serialDebug();
  
  }


// For H2
void H2Read(){
    Serial.println("H2 MQ6"); 
  // FOR MQ6
 MQ6.setA(88158); MQ6.setB(-3.597); // Configure the equation to to calculate NH4 concentration
 MQ6.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ6.readSensor();
 MQ6.serialDebug();

     Serial.println("H2 MQ7"); 
// MQ-7
 MQ7.setA(69.014); MQ7.setB(-1.374); // Configure the equation to to calculate NH4 concentration
 MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
 MQ7.readSensor();
 MQ7.serialDebug();
  
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
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}

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

Serial.println("DHT 11 ---------");
dht11();
}
