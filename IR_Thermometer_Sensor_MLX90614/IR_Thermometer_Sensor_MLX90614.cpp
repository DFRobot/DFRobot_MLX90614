/*!
* @file IR_Thermometer_Sensor_MLX90614.cpp
* @brief IR_Thermometer_Sensor_MLX90614.cpp Initialize the IIC,get the celsius temperature and fahrenheit temperature values,get the register values.
*
*  IR_Thermometer_Sensor_MLX90614.cpp Corresponds to a set of orthogonal codes for each motor and PWM. 
*                                     Implements timer 5 implementation of PWM, timer every 3.9 ¦Ìs (1/256 MS) into an interruption.
* 
* @author jackli(Jack.li@dfrobot.com)
* @version  V0.1
* @date  2016-1-16
*/
#include "IR_Thermometer_Sensor_MLX90614.h"

IR_Thermometer_Sensor_MLX90614::IR_Thermometer_Sensor_MLX90614(uint8_t IICAddr) {
  DiviceAddress = IICAddr;
}


boolean IR_Thermometer_Sensor_MLX90614::begin(void) {
  Wire.begin();
  return true;
}

double IR_Thermometer_Sensor_MLX90614::GetObjectTemp_Celsius(void) {
  return GetTemp(MLX90614_TOBJ1);//Get celsius temperature of the object 
}


double IR_Thermometer_Sensor_MLX90614::GetAmbientTemp_Celsius(void) {
  return GetTemp(MLX90614_TA);////Get celsius temperature of the ambient
}

double IR_Thermometer_Sensor_MLX90614::GetObjectTemp_Fahrenheit(void) {
  return (GetTemp(MLX90614_TOBJ1) * 9 / 5) + 32;//Get fahrenheit temperature of the object
}


double IR_Thermometer_Sensor_MLX90614::GetAmbientTemp_Fahrenheit(void) {
  return (GetTemp(MLX90614_TA) * 9 / 5) + 32;//Get fahrenheit temperature of the ambient
}

float IR_Thermometer_Sensor_MLX90614::GetTemp(uint8_t Register) {
  float temp;
	
  temp = Get_Register(Register)*0.02-273.15;//Temperature conversion
  return temp;
}

/*********************************************************************/

uint16_t IR_Thermometer_Sensor_MLX90614::Get_Register(uint8_t Reg) {
  uint16_t result;

  Wire.beginTransmission(DiviceAddress); //Start transmission to device 
  Wire.write(Reg); //Sends register address to read rom
  Wire.endTransmission(false); //End transmission
  
  Wire.requestFrom(DiviceAddress, (uint8_t)3);//Send data n-bytes read
  result = Wire.read(); //Receive DATA
  result |= Wire.read() << 8; //Receive DATA

  return result;
}
/******************************************************************************
  Copyright (C) <2016>  <jackli>
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  Contact: Jack.li@dfrobot.com
 ******************************************************************************/
 