# DFRobot_BME68x

* [中文版](./README_CN.md)

This is a Library for MLX90614, the function is to read temperature.
The MLX90614 is an Infra Red thermometer for non contact temperature measurements.
Both the IR sensitive thermopile detector chip and the signal conditioning ASSP are integrated in the same TO-39 can.
Thanks to its low noise amplifier, 17-bit ADC and powerful DSP unit, a high accuracy and resolution of the thermometer is achieved.

![产品效果图](../../resources/images/mmlx90614.png) 



## Product Link(https://www.dfrobot.com)
    SKU: SEN0206/sen0263

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

1. Download this library to Raspberry Pi with the following command:<br>
```python
sudo git clone https://github.com/DFRobot/DFRobot_MLX90614
```
2. Run example code，to execuate a demo code，please input the following command line in command line:<br>
```python
python example.py 
```

## Methods

```python

```

## Compatibility

| Board         |  Work Well    | Work Wrong   | Untested    | Remarks
| ------------ | :--: | :----: | :----: | :--: |
| RaspberryPi2 |      |        |   √    |      |
| RaspberryPi3 |  √     |        |      |      |
| RaspberryPi4 |  √   |        |        |      |

* Python 版本

| Python  |  Work Well    | Work Wrong   | Untested    | Remarks
| ------- | :--: | :----: | :----: | ---- |
| Python2 |  √   |        |        |      |
| Python3 |  √   |        |        |      |

## History

- 2024/07/15 - Version 1.0.0 released.

## Credits

Written by [YeezB](roger961130@icloud.com)