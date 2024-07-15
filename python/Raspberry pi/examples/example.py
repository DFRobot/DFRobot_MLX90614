'''!
  @file example.py
  @brief this demo demonstrates how to put the sensor enter/exit sleep mode and get temperature data measured by sensor
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author [YeezB](roger961130@icloud.com)
  @version  V1.0
  @date  2024-07-15
  @url https://github.com/DFRobot/DFRobot_MLX90614
'''

from mlx90614 import MLX90614

thermometer_address = 0x5a

thermometer = MLX90614(thermometer_address)


while (1):
    print (thermometer.get_obj_temp()) 
    #print (thermometer.get_amb_temp())