/*!
 * @file  DFRobot_MLX90614.cpp
 * @brief  DFRobot_MLX90614.cpp Initialize the I2C,
 * @n      get the celsius temperature and fahrenheit temperature values,get the register values.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2021-07-29
 * @url  https://github.com/DFRobot/DFRobot_MLX90614
 */
#include "DFRobot_MLX90614.h"

DFRobot_MLX90614::DFRobot_MLX90614()
{
}


int DFRobot_MLX90614::begin(void)
{
  uint8_t idBuf[3];
  if(0 == readReg(MLX90614_ID_NUMBER, idBuf)){   // Judge whether the data bus is successful
    DBG("ERR_DATA_BUS");
    return ERR_DATA_BUS;
  }

  DBG("real sensor id=");DBG((uint16_t)idBuf[0] | (uint16_t)(idBuf[1] << 8), HEX);
  DBG(idBuf[2], HEX);
  if( 0 == ( (uint16_t)idBuf[0] | (uint16_t)( idBuf[1] << 8 ) ) ){   // Judge whether the chip version matches
    DBG("ERR_IC_VERSION");
    return ERR_IC_VERSION;
  }

  delay(200);
  DBG("begin ok!");
  return NO_ERR;
}

void DFRobot_MLX90614::setEmissivityCorrectionCoefficient(float calibrationValue) {
  uint16_t emissivity = round( 65535 * calibrationValue);
  DBG(emissivity, HEX);
  uint8_t buf[2] = {0};
  writeReg(MLX90614_EMISSIVITY, buf);
  delay(10);

  buf[0] = (emissivity & 0x00FF);
  buf[1] = ( (emissivity & 0xFF00) >> 8 );
  writeReg(MLX90614_EMISSIVITY, buf);
  delay(10);
}

void DFRobot_MLX90614::setMeasuredParameters(eIIRMode_t IIRMode, eFIRMode_t FIRMode) {
  uint8_t buf[2] = {0};
  readReg(MLX90614_CONFIG_REG1, buf);
  delay(10);

  buf[0] &= 0xF8;
  buf[1] &= 0xF8;
  writeReg(MLX90614_CONFIG_REG1, buf);
  delay(10);

  buf[0] |= IIRMode;
  buf[1] |= FIRMode;
  writeReg(MLX90614_CONFIG_REG1, buf);
  delay(10);
}

float DFRobot_MLX90614::getAmbientTempCelsius(void) {
  uint8_t buf[2];
  readReg(MLX90614_TA, buf);
  float temp = ((uint16_t)buf[0] | (uint16_t)(buf[1] << 8)) * 0.02 - 273.15;

  return temp;   // Get celsius temperature of the ambient
}

float DFRobot_MLX90614::getObjectTempCelsius(void) {
  uint8_t buf[2];
  readReg(MLX90614_TOBJ1, buf);
  // DBG((buf[0] | buf[1] << 8), HEX);
  float temp = ((uint16_t)buf[0] | (uint16_t)(buf[1] << 8)) * 0.02 - 273.15;

  return temp;   // Get celsius temperature of the object 
}

float DFRobot_MLX90614::getObject2TempCelsius(void) {
  uint8_t buf[2];
  readReg(MLX90614_TOBJ2, buf);
  // DBG((buf[0] | buf[1] << 8), HEX);
  float temp = ((uint16_t)buf[0] | (uint16_t)(buf[1] << 8)) * 0.02 - 273.15;

  return temp;   // Get celsius temperature of the object 
}

uint8_t DFRobot_MLX90614::readModuleFlags(void) {
  uint8_t flagBuf[3], ret = 0;
  readReg(MLX90614_FLAGS, flagBuf);

  if( flagBuf[0] & (1 << 3) ){
    ret |= 1;
    DBG("Not implemented.");
  }

  if( !(flagBuf[0] & (1 << 4) ) ){
    ret |= (1<<1);
    DBG("INIT - POR initialization routine is still ongoing. Low active.");
  }

  if( flagBuf[0] & (1 << 5) ){
    ret |= (1<<2);
    DBG("EE_DEAD - EEPROM double error has occurred. High active.");
  }

  if( flagBuf[0] & (1 << 7) ){
    ret |= (1<<3);
    DBG("EEBUSY - the previous write/erase EEPROM access is still in progress. High active.");
  }

  return ret;
}

/************ Initialization of I2C interfaces reading and writing ***********/

DFRobot_MLX90614_I2C::DFRobot_MLX90614_I2C(uint8_t i2cAddr, TwoWire *pWire)
{
  _deviceAddr = i2cAddr;
  _pWire = pWire;
}

int DFRobot_MLX90614_I2C::begin(void)
{
  // _pWire->begin();   // Wire.h（I2C）library function initialize wire library

  enterSleepMode(false);
  delay(50);

  return DFRobot_MLX90614::begin();   // Use the initialization function of the parent class
}

void DFRobot_MLX90614_I2C::enterSleepMode(bool mode)
{
  if(mode){
    // sleep command, refer to the chip datasheet
    _pWire->beginTransmission(_deviceAddr);
    _pWire->write(MLX90614_SLEEP_MODE);
    _pWire->write(MLX90614_SLEEP_MODE_PEC);
    _pWire->endTransmission();

    DBG("enter sleep mode");
  }else{
    #if defined(ESP32)
      _pWire->~TwoWire();
    #elif !defined(ESP8266)
      _pWire->end();
    #endif

    // wake up command, refer to the chip datasheet
    pinMode(SDA, OUTPUT);
    pinMode(SCL, OUTPUT);
    digitalWrite(SCL, LOW);
    digitalWrite(SDA, HIGH);
    delay(50);
    digitalWrite(SCL, HIGH);
    digitalWrite(SDA, LOW);
    delay(50);

    _pWire->begin();   // Wire.h（I2C）library function initialize wire library

    #ifdef ESP8266
      digitalWrite(SCL, LOW);
    #endif

    _pWire->beginTransmission(_deviceAddr);
    _pWire->endTransmission();
    DBG("exit sleep mode");
  }
  delay(200);
}

void DFRobot_MLX90614_I2C::setI2CAddress(uint8_t addr)
{
  uint8_t buf[2] = {0};
  writeReg(MLX90614_SMBUS_ADDR, buf);
  delay(10);
  buf[0] = addr;
  writeReg(MLX90614_SMBUS_ADDR, buf);
  delay(10);
}

unsigned char DFRobot_MLX90614_I2C::crc8Polyomial107(unsigned char *ptr, size_t len)
{
  unsigned char i; 
  unsigned char crc=0x00;   // calculated initial crc value

  while(len--){
    // DBG("*ptr, HEX");
    // DBG(*ptr, HEX);

    // first xor with the data to be calculated every time, point to the next data after completing the calculation
    crc ^= *ptr++;

    for (i=8; i>0; i--){
      // the following calculation is the same as calculating a byte crc
      if (crc & 0x80){
        crc = (crc << 1) ^ 0x07;
      }
      else{
        crc = (crc << 1);
      }
    }
  }
  // DBG(crc, HEX);

  return (crc); 
}

void DFRobot_MLX90614_I2C::writeReg(uint8_t reg, const void* pBuf)
{
  if(pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  unsigned char crc_write[5] = {(uint8_t)(_deviceAddr << 1), reg, _pBuf[0], _pBuf[1], '\0'};   // the array prepared for calculating the check code

  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(reg);

  for(size_t i = 0; i < 2; i++){
    _pWire->write(_pBuf[i]);
  }
  _pWire->write(crc8Polyomial107(crc_write, 4));
  _pWire->endTransmission();
}

size_t DFRobot_MLX90614_I2C::readReg(uint8_t reg, void* pBuf)
{
  size_t count = 0;
  if(NULL == pBuf){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t*)pBuf;

  _pWire->beginTransmission(_deviceAddr);
  _pWire -> write(reg);
  if(0 != _pWire->endTransmission(false)){
    // Used Wire.endTransmission() to end a slave transmission started by beginTransmission() and arranged by write().
    DBG("endTransmission ERROR!!");
  }else{
    // Master device requests size bytes from slave device, which can be accepted by master device with read() or available()
    _pWire->requestFrom( _deviceAddr, (uint8_t)3 );

    while (_pWire->available()){
      _pBuf[count++] = _pWire->read();   // Use read() to receive and put into buf
      // DBG(_pBuf[count-1], HEX);
    }
    _pWire->endTransmission();

    // the array prepared for calculating the check code
    unsigned char crc_read[6] = {(uint8_t)(_deviceAddr << 1), reg, (uint8_t)((_deviceAddr << 1) | 1), _pBuf[0], _pBuf[1], '\0'};

    if(_pBuf[2] != crc8Polyomial107(crc_read, 5)){
      count = 0;
      DBG("crc8Polyomial107 ERROR!!");
      DBG(_pBuf[2], HEX);
    }
  }

  return count;
}
