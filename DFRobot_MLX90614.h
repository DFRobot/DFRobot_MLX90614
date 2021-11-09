/*!
 * @file  DFRobot_MLX90614.h
 * @brief  DFRobot_MLX90614.h detailed description for DFRobot_MLX90614.cpp
 * @details  DFRobot_MLX90614.h Define the device address, define the temperature register address,
 * @n        statement read temperature function and so on.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2021-07-29
 * @url  https://github.com/DFRobot/DFRobot_MLX90614
 */
#ifndef __DFROBOT_MLX90614_H__
#define __DFROBOT_MLX90614_H__

#include <Arduino.h>
#include <Wire.h>

// #define ENABLE_DBG   //!< open this macro and you can see the details of the program
#ifdef ENABLE_DBG
  #define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
  #define DBG(...)
#endif

#define MLX90614_ID_NUMBER_1C 0x3802   ///< mlx9614 ID number(reg: MLX90614_ID_NUMBER)

#define MLX90614_TA       0x06   ///< the register address stores the measured ambient temperature
#define MLX90614_TOBJ1    0x07   ///< the register address stores the measured temperature of object 1
#define MLX90614_TOBJ2    0x08   ///< the register address stores the measured temperature of object 2

/* these addresses are in EEPROM, read requires to(| 0x20) */
#define MLX90614_TO_MAX         ( 0x00 | 0x20 )   ///< The addresses Tomax, Tomin and Ta range are for customer dependent object and ambient temperature ranges
#define MLX90614_TO_MIN         ( 0x01 | 0x20 )
#define MLX90614_PWMCTRL        ( 0x02 | 0x20 )   ///< The address PWMCTRL consists of control bits for configuring the PWM/SDA pin as follows
#define MLX90614_TA_RANGE       ( 0x03 | 0x20 )
#define MLX90614_EMISSIVITY     ( 0x04 | 0x20 )   ///< The address Emissivity contains the object emissivity (factory default 1.0 = 0xFFFF)
#define MLX90614_CONFIG_REG1    ( 0x05 | 0x20 )   ///< The address ConfigRegister1 consists of control bits for configuring the analog and digital parts
#define MLX90614_SMBUS_ADDR     ( 0x0E | 0x20 )   ///< SMBus address (LSByte only)
#define MLX90614_ID_NUMBER      ( 0x1C | 0x20 )   ///< ID number

#define MLX90614_FLAGS            0xF0   ///< Read Flags
#define MLX90614_SLEEP_MODE       0xFF   ///< Enter SLEEP mode
#define MLX90614_SLEEP_MODE_PEC   0xE8   ///< Enter SLEEP mode PEC

class DFRobot_MLX90614
{
public:
  #define NO_ERR             0     ///< No error
  #define ERR_DATA_BUS      (-1)   ///< data bus error
  #define ERR_IC_VERSION    (-2)   ///< the chip version not match

  /**
   * @enum eIIRMode_t
   * @brief IIR filter mode
   */
  typedef enum
  {
    eIIR50 = 0,
    eIIR25,
    eIIR17,
    eIIR13,
    eIIR100,
    eIIR80,
    eIIR67,
    eIIR57,
  }eIIRMode_t;

  /**
   * @enum eFIRMode_t
   * @brief FIR filter mode
   */
  typedef enum
  {
    eFIR8 = 0,
    eFIR16,
    eFIR32,
    eFIR64,
    eFIR128,
    eFIR256,
    eFIR512,
    eFIR1024,
  }eFIRMode_t;

public:
  /**
   * @fn DFRobot_MLX90614
   * @brief constructor
   * @return None
   */
  DFRobot_MLX90614();

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
   * @param IIRMode: eIIR100, eIIR80, eIIR67, eIIR57;
   * @param FIRMode: eFIR128, eFIR256, eFIR512, eFIR1024;
   * @return None
   */
  void setMeasuredParameters(eIIRMode_t IIRMode=eIIR100, eFIRMode_t FIRMode=eFIR1024);

  /**
   * @fn getAmbientTempCelsius
   * @brief get ambient temperature, unit is Celsius
   * @return return value range： -40 C ~ 85 C
   */
  float getAmbientTempCelsius(void);

  /**
   * @fn getObjectTempCelsius
   * @brief get temperature of object 1, unit is Celsius
   * @return return value range： -40 C ~ 85 C
   */
  float getObjectTempCelsius(void);

protected:
/***************** register read/write ports ******************************/

  /**
   * @fn getObject2TempCelsius
   * @brief get temperature of object 2, unit is Celsius
   * @return return value range： -40 C ~ 85 C
   */
  float getObject2TempCelsius(void);

  /**
   * @fn readModuleFlags
   * @brief read the sensor flags
   * @return four flags
   */
  uint8_t readModuleFlags(void);

  /**
   * @fn writeReg
   * @brief write register function, design it as a pure virtual function, implement the function body through a derived class
   * @param reg  register address 8bits
   * @param pBuf to write data storage and buffer
   * @return None
   */
  virtual void writeReg(uint8_t reg, const void* pBuf)=0;

  /**
   * @fn readReg
   * @brief read register function, design it as a pure virtual function, implement the function body through a derived class
   * @param reg  register address 8bits
   * @param pBuf to read data storage and buffer
   * @return return read length, returning 0 means read failure
   */
  virtual size_t readReg(uint8_t reg, void* pBuf)=0;

};

/***************** initialization and read/write of IIC interface ******************************/

class DFRobot_MLX90614_IIC:public DFRobot_MLX90614
{
public:
  /**
   * @fn DFRobot_MLX90614_IIC
   * @brief constructor, set sensor IIC communication address according to SDO pin wiring
   * @param iicAddr mlx9614 IIC communication address
   * @param pWire Wire object is defined in Wire.h, so just use &Wire and the methods in Wire can be pointed to and used
   * @return None
   */
  DFRobot_MLX90614_IIC(uint8_t iicAddr=0x5A, TwoWire *pWire = &Wire);

  /**
   * @fn begin
   * @brief subclass initialization function
   * @return returning 0 indicates initialization succeeds, returning other values indicates initialization fails
   */
  virtual int begin(void);

  /**
   * @fn enterSleepMode
   * @brief control the sensor sleep mode, must enter and exit the sleep mode once after the sensor is configured (equivalent to soft reset) to ensure the normal reading of the measured data
   * @param mode select to enter or exit sleep mode, it’s enter sleep mode by default
   * @n            true put the sensor to sleep
   * @n            false wake up the sensor (automatically exit sleep mode after power down and restart)
   * @return None
  */
  void enterSleepMode(bool mode=true);

  /**
   * @fn setIICAddress
   * @brief set IIC communication address, the setting takes effect after power down and restart
   * @param addr new IIC communication address 7bit, range: (0~127)
   * @return None
   */
  void setIICAddress(uint8_t addr);

protected:

  /**
   * @fn crc8Polyomial107
   * @brief calculate crc8 (polynomial corresponds to 0x107) check code (PEC)
   * @param ptr correspondingly calculate the data pointer of check code
   * @param len correspondingly calculate the data length of check code
   * @return char type, return the calculated crc check code
   */
  unsigned char crc8Polyomial107(unsigned char *ptr, size_t len);

  /**
   * @fn writeReg
   * @brief write register values through IIC bus
   * @param reg  register address 8bits
   * @param pBuf to write data storage and buffer
   * @return None
   */
  virtual void writeReg(uint8_t reg, const void* pBuf);

  /**
   * @fn readReg
   * @brief read register values through IIC bus
   * @param reg  register address 8bits
   * @param pBuf to read data storage and buffer
   * @return return read length, returning 0 means read failure
   */
  virtual size_t readReg(uint8_t reg, void* pBuf);

private:
  TwoWire *_pWire;   // pointer to IIC communication method
  uint8_t _deviceAddr;   // IIC communication device address
};

#endif
