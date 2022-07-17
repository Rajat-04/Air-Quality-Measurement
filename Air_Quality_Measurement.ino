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
void MQ6read(){
  MQ6.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ6.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  MQ6.serialDebug(); // Will print the table on the serial port
}
void MQ135read(){
 MQ135.update(); // Update data, the arduino will read the voltage from the analog pin

  MQ135.setA(605.18); MQ135.setB(-3.937); // Configure the equation to calculate CO concentration value
  float CO = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(77.255); MQ135.setB(-3.18); //Configure the equation to calculate Alcohol concentration value
  float Alcohol = MQ135.readSensor(); // SSensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(110.47); MQ135.setB(-2.862); // Configure the equation to calculate CO2 concentration value
  float CO2 = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(44.947); MQ135.setB(-3.445); // Configure the equation to calculate Toluen concentration value
  float Toluen = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  
  MQ135.setA(102.2 ); MQ135.setB(-2.473); // Configure the equation to calculate NH4 concentration value
  float NH4 = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup

  MQ135.setA(34.668); MQ135.setB(-3.369); // Configure the equation to calculate Aceton concentration value
  float Aceton = MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  Serial.print("|   "); Serial.print(CO); 
  Serial.print("   |   "); Serial.print(Alcohol);
  // Note: 400 Offset for CO2 source: https://github.com/miguel5612/MQSensorsLib/issues/29
  /*
  Motivation:
  We have added 400 PPM because when the library is calibrated it assumes the current state of the
  air as 0 PPM, and it is considered today that the CO2 present in the atmosphere is around 400 PPM.
  https://www.lavanguardia.com/natural/20190514/462242832581/concentracion-dioxido-cabono-co2-atmosfera-bate-record-historia-humanidad.html
  */
  Serial.print("   |   "); Serial.print(CO2 + 400); 
  Serial.print("   |   "); Serial.print(Toluen); 
  Serial.print("   |   "); Serial.print(NH4); 
  Serial.print("   |   "); Serial.print(Aceton);
  Serial.println("   |"); 
  /*
    Exponential regression:
  GAS      | a      | b
  CO       | 605.18 | -3.937  
  Alcohol  | 77.255 | -3.18 
  CO2      | 110.47 | -2.862
  Toluen  | 44.947 | -3.445
  NH4      | 102.2  | -2.473
  Aceton  | 34.668 | -3.369
  */
  MQ135.serialDebug();
}
void MQ7read(){
  MQ7.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ7.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  MQ7.serialDebug(); // Will print the table on the serial port
}
void MQ4read(){
  MQ4.update(); // Update data, the arduino will read the voltage from the analog pin
  MQ4.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  MQ4.serialDebug(); // Will print the table on the serial port
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
//MQ135'
int MQ135S;
Serial.println("MQ135 ---------");
MQ135read();
Serial.println("MQ7 ---------");
MQ7read();
Serial.println("MQ4 ---------");
MQ4read();
Serial.println("MQ6 ---------");
MQ6read();
Serial.println("DHT 11 ---------");
dht11();
}
