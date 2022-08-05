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


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
//Set math model to calculate the PPM concentration and the value of constants
  MQ6.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ6.init(); 

    MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ4.init(); 

    MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.init(); 

    MQ7.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ7.init(); 
  
/*While calibrating Your sensor Uncomment this calibration portion and calibrate for R0.*/
  /*****************************  MQ CAlibration ********************************************/
  Serial.print("Calibrating please wait.");
  float  MQ6calcR0 = 0,
         MQ4calcR0 = 0,
         MQ135calcR0 = 0,
         MQ7calcR0 = 0;
  for (int i = 1; i <= 10; i ++)
  {
    //Update the voltage lectures
    MQ6.update();
    MQ4.update();
    MQ135.update();
    MQ7.update();

    MQ6calcR0 += MQ6.calibrate(RatioMQ6CleanAir);
    MQ4calcR0 += MQ4.calibrate(RatioMQ4CleanAir);
    MQ135calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    MQ7calcR0 += MQ7.calibrate(RatioMQ7CleanAir);

    Serial.print(".");
  }
  MQ6.setR0(MQ6calcR0 / 10);
  MQ4.setR0(MQ4calcR0 / 10);
  MQ135.setR0(MQ135calcR0 / 10);
  MQ7.setR0(MQ7calcR0 / 10);

  Serial.println("  done!.");

  Serial.print("(MQ6 - MQ7):");
  Serial.print(MQ6calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ4calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ135calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ7calcR0 / 10); Serial.print(" | ");


  /*****************************  MQ CAlibration ********************************************/ 
}

void loop() {
  delay(1000);
}
