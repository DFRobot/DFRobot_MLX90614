/*!
* @file IR_Thermometer_Sensor_MLX90614.h
* @brief IR_Thermometer_Sensor_MLX90614.h detailed description for IR_Thermometer_Sensor_MLX90614.cpp 
*
*  IR_Thermometer_Sensor_MLX90614.h Define the device address, define the temperature register address, statement read temperature function and so on
* 
* @author jackli(Jack.li@dfrobot.com)
* @version  V0.1
* @date  2016-1-16
*/
#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"


#define MLX90614_IIC_ADDR 0x5A

#define MLX90614_TA 			0x06
#define MLX90614_TOBJ1 		0x07

class IR_Thermometer_Sensor_MLX90614  
{
	public:
  IR_Thermometer_Sensor_MLX90614(uint8_t Addr = MLX90614_IIC_ADDR);
  boolean begin();

  double GetObjectTemp_Celsius(void);
  double GetAmbientTemp_Celsius(void);
  double GetObjectTemp_Fahrenheit(void);
  double GetAmbientTemp_Fahrenheit(void);

 	private:
  float GetTemp(uint8_t Register);

  uint8_t DiviceAddress;
  uint16_t Get_Register(uint8_t Reg);
  void write16(uint8_t addr, uint16_t data);
};
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
