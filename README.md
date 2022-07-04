# DFRobot_MLX90614
* [中文版](./README_CN.md)

This is a Library for MLX90614, the function is to read temperature.
The MLX90614 is an Infra Red thermometer for non contact temperature measurements.
Both the IR sensitive thermopile detector chip and the signal conditioning ASSP are integrated in the same TO-39 can.
Thanks to its low noise amplifier, 17-bit ADC and powerful DSP unit, a high accuracy and resolution of the thermometer is achieved.

![产品实物图](./resources/images/mlx90614.png)


## Product Link (https://www.dfrobot.com/search-mlx90614.html)
    SKU：SEN0206/SEN0263


## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)


## Summary

* MLX90614 can read temperature.
* The library supports the I2C communication.
* The MLX90614 is a ready-to use low-cost non contact thermometer provided from Melexis with output data linearly dependent on the object temperature with high accuracy and extended resolution.
* The high thermal stability of the MLX90614-xCx make this part highly suited in applications where secondary heat sources can heat up the sensor. These sensors also have a very short stabilization time compared to other types of thermopile sensors, which is of importance if one needs an accurate measurement in conditions where the ambient temperature can change quickly. 
* The MLX90614 supports versatile customization to a very wide range of temperatures, power supplies and refresh rates.
* The user can program the internal object emissivity correction for objects with a low emissivity. An embedded error checking and correction mechanism provides high memory reliability.
* The sensors are housed in an industry standard TO39 package for both single- and dual-zone IR thermometers. The thermometer is available in automotive grade and can use two different packages for wider applications’ coverage.
* The low power consumption during operation and the low current draw during sleep mode make the thermometer ideally suited for handheld mobile applications.
* The digital sensor interface can be either a power-up-and-measure PWM or an enhanced access SMBus compatible protocol. Systems with more than 100 devices can be built with only two signal lines. Dual zone non contact temperature measurements are available via a single line (extended PWM).
* A build-in thermal relay function further extends the easy implementation of wide variety of freezing/boiling prevention and alert systems, as well as thermostats (no MCU is needed).


## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, 
then open the examples folder and run the demo in the folder.


## Methods

```C++

  /**
   * @fn begin
   * @brief initialization function
   * @return int type, indicates returning initialization status
   * @retval 0 NO_ERROR
   * @retval -1 ERR_DATA_BUS
   * @retval -2 ERR_IC_VERSION
   */
  virtual int begin(void);

  /**
   * @fn setEmissivityCorrectionCoefficient
   * @brief set the emissivity calibration coefficient, users need to calculate the ratio of the temperature measured before the sensor changes emissivity to the true temperature of the object,
   * @n     upload the ratio to the api as a parameter, and the deviation of the object absolute temperature measured by the sensor will be lower
   * @param calibrationValue new calibration coefficient, the ratio of the temperature measured before the sensor changes emissivity to the true temperature of the object, range: (0~1)
   * @return None
   */
  void setEmissivityCorrectionCoefficient(float calibrationValue);

  /**
   * @fn setMeasuredParameters
   * @brief set the measurement parameters, including IIR (Infinite Impulse Response Digital Filter) and FIR (Finite Impulse Response Digital Filter)
   * @details Filter noise (biased measurement data) to provide data accuracy, filter coefficients can be set as follows
   * @param IIRMode: eIIR100, eIIR80, eIIR67, eIIR57;
   * @param FIRMode: eFIR128, eFIR256, eFIR512, eFIR1024;
   * @return None
   */
  void setMeasuredParameters(eIIRMode_t IIRMode=eIIR100, eFIRMode_t FIRMode=eFIR1024);

  /**
   * @fn getAmbientTempCelsius
   * @brief get ambient temperature, unit is Celsius
   * @return return value range： -40.01 °C ~ 85 °C
   */
  float getAmbientTempCelsius(void);

  /**
   * @fn getObjectTempCelsius
   * @brief get temperature of object, unit is Celsius
   * @return return value range： 
   * @n  -70.01 °C ~ 270 °C(MLX90614ESF-DCI)
   * @n  -70.01 °C ~ 380 °C(MLX90614ESF-DCC)
   */
  float getObjectTempCelsius(void);

  /**
   * @fn enterSleepMode
   * @brief control the sensor sleep mode, must enter and exit the sleep mode once after the sensor is configured (equivalent to soft reset) to ensure the normal reading of the measured data
   * @param mode select to enter or exit sleep mode, it's enter sleep mode by default
   * @n            true put the sensor to sleep
   * @n            false wake up the sensor (automatically exit sleep mode after power down and restart)
   * @return None
  */
  void enterSleepMode(bool mode=true);

  /**
   * @fn setI2CAddress
   * @brief set I2C communication address, the setting takes effect after power down and restart
   * @param addr new I2C communication address 7bit, range: (0~127)
   * @return None
   */
  void setI2CAddress(uint8_t addr);

```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
Firebeetle ESP8266 |      √       |              |             | 
Firebeetle ESP32-E |      √       |              |             | 
FireBeetle M0      |      √       |              |             | 
micro:bit          |      √       |              |             | 


## History

- 2021/08/09 - Version 1.0.0 released.
- 2022/07/04 - Version 1.0.1 released.


## Credits

Written by qsjhyy(yihuan.huang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

