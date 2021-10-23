################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node_DualCore/Common/System/sys_debug.c 

OBJS += \
./Application/User/Common/System/sys_debug.o 

C_DEPS += \
./Application/User/Common/System/sys_debug.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Common/System/sys_debug.o: D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node_DualCore/Common/System/sys_debug.c Application/User/Common/System/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DSTM32WL55xx -DUSE_HAL_DRIVER -c -I../../../CM4/Core/Inc -I../../../CM4/LoRaWAN/App -I../../../CM4/LoRaWAN/Target -I../../../CM4/MbMux -I../../../Common/Board -I../../../Common/MbMux -I../../../Common/System -I../../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -I../../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../../../../../../../Utilities/trace/adv_trace -I../../../../../../../../Utilities/misc -I../../../../../../../../Utilities/sequencer -I../../../../../../../../Utilities/timer -I../../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Utilities -I../../../../../../../../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

