################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node_DualCore/CM4/LoRaWAN/App/CayenneLpp.c \
D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node_DualCore/CM4/LoRaWAN/App/app_lorawan.c \
D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node_DualCore/CM4/LoRaWAN/App/lora_app.c 

OBJS += \
./Application/User/LoRaWAN/App/CayenneLpp.o \
./Application/User/LoRaWAN/App/app_lorawan.o \
./Application/User/LoRaWAN/App/lora_app.o 

C_DEPS += \
./Application/User/LoRaWAN/App/CayenneLpp.d \
./Application/User/LoRaWAN/App/app_lorawan.d \
./Application/User/LoRaWAN/App/lora_app.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/LoRaWAN/App/CayenneLpp.o: D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node_DualCore/CM4/LoRaWAN/App/CayenneLpp.c Application/User/LoRaWAN/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DSTM32WL55xx -DUSE_HAL_DRIVER -c -I../../../CM4/Core/Inc -I../../../CM4/LoRaWAN/App -I../../../CM4/LoRaWAN/Target -I../../../CM4/MbMux -I../../../Common/Board -I../../../Common/MbMux -I../../../Common/System -I../../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -I../../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../../../../../../../Utilities/trace/adv_trace -I../../../../../../../../Utilities/misc -I../../../../../../../../Utilities/sequencer -I../../../../../../../../Utilities/timer -I../../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Utilities -I../../../../../../../../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/LoRaWAN/App/app_lorawan.o: D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node_DualCore/CM4/LoRaWAN/App/app_lorawan.c Application/User/LoRaWAN/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DSTM32WL55xx -DUSE_HAL_DRIVER -c -I../../../CM4/Core/Inc -I../../../CM4/LoRaWAN/App -I../../../CM4/LoRaWAN/Target -I../../../CM4/MbMux -I../../../Common/Board -I../../../Common/MbMux -I../../../Common/System -I../../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -I../../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../../../../../../../Utilities/trace/adv_trace -I../../../../../../../../Utilities/misc -I../../../../../../../../Utilities/sequencer -I../../../../../../../../Utilities/timer -I../../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Utilities -I../../../../../../../../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/LoRaWAN/App/lora_app.o: D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node_DualCore/CM4/LoRaWAN/App/lora_app.c Application/User/LoRaWAN/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DSTM32WL55xx -DUSE_HAL_DRIVER -c -I../../../CM4/Core/Inc -I../../../CM4/LoRaWAN/App -I../../../CM4/LoRaWAN/Target -I../../../CM4/MbMux -I../../../Common/Board -I../../../Common/MbMux -I../../../Common/System -I../../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -I../../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../../../../../../../Utilities/trace/adv_trace -I../../../../../../../../Utilities/misc -I../../../../../../../../Utilities/sequencer -I../../../../../../../../Utilities/timer -I../../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Utilities -I../../../../../../../../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

