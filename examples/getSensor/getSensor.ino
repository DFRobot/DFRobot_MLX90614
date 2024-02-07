/*!
 * @file        getSensor.ino
 * @brief       this demo is to get the emissivity calibration coefficient, and get measurement parameters, including IIR, FIR and the gain of the sensor amplifier
 * @copyright   Copyright (c) 2024 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      [qsjhyy](yihuan.huang@dfrobot.com), Rudy Ercek (ULB)
 * @version     V1.0
 * @date        2024-02-24
 * @url         https://github.com/DFRobot/DFRobot_MLX90614
 */
#include <DFRobot_MLX90614.h>

#define MLX90614_I2C_ADDR 0x5A   // mlx9614 default I2C communication address
DFRobot_MLX90614_I2C sensor(MLX90614_I2C_ADDR, &Wire);   // instantiate an object to drive the sensor

void setup()
{
  Serial.begin(115200);

  // initialize the sensor
  while( NO_ERR != sensor.begin() ){
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  Serial.println("Begin ok!");

  /**
   * get the current emissivity calibration coefficient,   
   * calibrationValue new calibration coefficient, [0, 1]
   */
  Serial.print("Emissitivity : ");
  Serial.println(sensor.getEmissivityCorrectionCoefficient(),6);

  /**
   * get the ConfigRegister1 value including measurement parameters i.e. IIR (Infinite Impulse Response Digital Filter), FIR (Finite Impulse Response Digital Filter) and the gain of the amplifier
   * see MLX90614 datasheet page 15 for more info
   */
  Serial.print("ConfigReg1 : ");
  Serial.println(sensor.getConfigRegister1(), HEX);
  
  /**
   * get the gain of the amplifier i.e. 1,3,9,12(.5),25,50 or 100
   */
  Serial.print("Gain of the sensor amplifier : ");
  Serial.println(sensor.getGainValue());
  
  /**
   * get the FIR length of the sensor
   */
  Serial.print("Sensor FIR length : ");
  Serial.println(sensor.getFIRLength());
 
  /**
   * get the IIR spike limit of the sensor in purcentage
   */
  Serial.print("Sensor IIR spike limit : ");
  Serial.print(sensor.getIIRSpikeLimit());
  Serial.println("%"); 
  
  /**
   * control the sensor sleep mode, must enter and exit the sleep mode once after the sensor is configured (equivalent to soft reset) to ensure the normal reading of the measured data
   * mode select to enter or exit sleep mode, it's enter sleep mode by default
   *      true put the sensor to sleep
   *      false wake up the sensor (automatically exit sleep mode after power down and restart)
   */
  sensor.enterSleepMode();
  delay(50);
  sensor.enterSleepMode(false);
  delay(200);
}

void loop()
{
  /**
   * get ambient temperature, unit is Celsius
   * return value range： -40.01 °C ~ 85 °C
   */
  float ambientTemp = sensor.getAmbientTempCelsius();

  /**
   * get temperature of object 1, unit is Celsius
   * return value range： 
   * @n  -70.01 °C ~ 270 °C(MLX90614ESF-DCI)
   * @n  -70.01 °C ~ 380 °C(MLX90614ESF-DCC)
   */
  float objectTemp = sensor.getObjectTempCelsius();    

  // print measured data in Celsius, unit is Celsius (°C)
  Serial.print("Ambient celsius : "); Serial.print(ambientTemp); Serial.println(" °C");
  Serial.print("Object celsius : ");  Serial.print(objectTemp);  Serial.println(" °C");

  // print measured data in Fahrenheit, unit is Fahrenheit (F)
  Serial.print("Ambient fahrenheit : "); Serial.print(ambientTemp*9/5 + 32); Serial.println(" F");
  Serial.print("Object fahrenheit : ");  Serial.print(objectTemp*9/5 + 32);  Serial.println(" F");
  
  // print temperature raw data (i.e. 50x the temperature in Kelvin)
  Serial.print("Ambient raw value : "); Serial.println(sensor.getAmbientTemp());
  Serial.print("Object raw value : "); Serial.println(sensor.getObjectTemp());
  

  Serial.println();
  delay(500);
}
