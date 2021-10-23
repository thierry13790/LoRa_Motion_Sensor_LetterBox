################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node/Core/Src/system_stm32wlxx.c 

OBJS += \
./Drivers/CMSIS/system_stm32wlxx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32wlxx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32wlxx.o: D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node/Core/Src/system_stm32wlxx.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -D_DEBUG -DCORE_CM4 -DSTM32WL55xx -DUSE_HAL_DRIVER -c -I../../Core/Inc -I../../Core/BSP_Ext_Sensors -I../../Core/vl53l0x -I../../LoRaWAN/App -I../../LoRaWAN/Target -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../../../../../../Utilities/trace/adv_trace -I../../../../../../../Utilities/misc -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/timer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Crypto -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac -I../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Utilities -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Drivers/STM32WLxx_HAL_Driver/Inc -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Utilities/trace/adv_trace -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Utilities/misc -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Utilities/sequencer -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Utilities/timer -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Utilities/lpm/tiny_lpm -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/SubGHz_Phy -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Drivers/CMSIS/Device/ST/STM32WLxx/Include -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/Crypto -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/Mac/Region -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/Mac -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/LmHandler -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/Utilities -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

