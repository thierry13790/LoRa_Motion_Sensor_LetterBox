# LoRa_Motion_Sensor_LetterBox

This project allow to manage a ST STM32WL55 chip able to manage a time of flight sensor which detect motion and send data over LoRa network. There TTN network is enabled but any LoRa network can be use. 

![latest tag](https://img.shields.io/github/v/tag/STMicroelectronics/STM32CubeWL.svg?color=brightgreen)

## Boards use in this project
  * STM32WL 
    * [NUCLEO-WL55JC](https://www.st.com/en/evaluation-tools/nucleo-wl55jc.html)

  * ST VL53L0X Time of Flight Sensor monted on a AZ Delivery board : https://www.az-delivery.de/en/products/vl53l0x-time-of-flight-tof-laser-abstandssensor

NB : please set your LoRa credential inside this file : se-identity_to_be_filled _with_your_credentials.h located inside 
LoRa_Motion_Sensor_LetterBox\Projects\NUCLEO-WL55JC\Applications\LoRaWAN\LoRaWAN_End_Node\LoRaWAN\App
and rename the file : se-identity inside same directory
