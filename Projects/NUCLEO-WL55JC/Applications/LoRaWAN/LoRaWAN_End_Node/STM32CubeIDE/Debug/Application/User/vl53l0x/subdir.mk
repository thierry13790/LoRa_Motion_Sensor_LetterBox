################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/vl53l0x/vl53l0x_api.c \
../Application/User/vl53l0x/vl53l0x_api_calibration.c \
../Application/User/vl53l0x/vl53l0x_api_core.c \
../Application/User/vl53l0x/vl53l0x_api_ranging.c \
../Application/User/vl53l0x/vl53l0x_api_strings.c \
../Application/User/vl53l0x/vl53l0x_platform_log.c \
../Application/User/vl53l0x/vl53l0x_tof.c 

OBJS += \
./Application/User/vl53l0x/vl53l0x_api.o \
./Application/User/vl53l0x/vl53l0x_api_calibration.o \
./Application/User/vl53l0x/vl53l0x_api_core.o \
./Application/User/vl53l0x/vl53l0x_api_ranging.o \
./Application/User/vl53l0x/vl53l0x_api_strings.o \
./Application/User/vl53l0x/vl53l0x_platform_log.o \
./Application/User/vl53l0x/vl53l0x_tof.o 

C_DEPS += \
./Application/User/vl53l0x/vl53l0x_api.d \
./Application/User/vl53l0x/vl53l0x_api_calibration.d \
./Application/User/vl53l0x/vl53l0x_api_core.d \
./Application/User/vl53l0x/vl53l0x_api_ranging.d \
./Application/User/vl53l0x/vl53l0x_api_strings.d \
./Application/User/vl53l0x/vl53l0x_platform_log.d \
./Application/User/vl53l0x/vl53l0x_tof.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/vl53l0x/%.o: ../Application/User/vl53l0x/%.c Application/User/vl53l0x/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DSTM32WL55xx -DUSE_HAL_DRIVER -c -I../../Core/Inc -I../../Core/vl53l0x -I../../LoRaWAN/App -I../../LoRaWAN/Target -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../../../../../../Utilities/trace/adv_trace -I../../../../../../../Utilities/misc -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/timer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Crypto -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac -I../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler -I../../../../../../../Middlewares/Third_Party/LoRaWAN/Utilities -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Drivers/STM32WLxx_HAL_Driver/Inc -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Utilities/trace/adv_trace -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Utilities/misc -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Utilities/sequencer -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Utilities/timer -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Utilities/lpm/tiny_lpm -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/SubGHz_Phy -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Drivers/CMSIS/Device/ST/STM32WLxx/Include -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/Crypto -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/Mac/Region -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/Mac -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/LmHandler -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Middlewares/Third_Party/LoRaWAN/Utilities -IC:/Users/thier/STM32Cube/Repository/STM32Cube_FW_WL_V1.1.0/Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

