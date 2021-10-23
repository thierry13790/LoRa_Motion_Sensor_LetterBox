################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/SubGHz_Phy/SubGHz_Phy_PingPong/SubGHz_Phy/App/app_subghz_phy.c \
D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/SubGHz_Phy/SubGHz_Phy_PingPong/SubGHz_Phy/App/subghz_phy_app.c 

OBJS += \
./Application/User/SubGHz_Phy/App/app_subghz_phy.o \
./Application/User/SubGHz_Phy/App/subghz_phy_app.o 

C_DEPS += \
./Application/User/SubGHz_Phy/App/app_subghz_phy.d \
./Application/User/SubGHz_Phy/App/subghz_phy_app.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/SubGHz_Phy/App/app_subghz_phy.o: D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/SubGHz_Phy/SubGHz_Phy_PingPong/SubGHz_Phy/App/app_subghz_phy.c Application/User/SubGHz_Phy/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../../Core/Inc -I../../SubGHz_Phy/App -I../../SubGHz_Phy/Target -I../../../../../../../Utilities/trace/adv_trace -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../../../../../../Utilities/misc -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/timer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/SubGHz_Phy/App/subghz_phy_app.o: D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/SubGHz_Phy/SubGHz_Phy_PingPong/SubGHz_Phy/App/subghz_phy_app.c Application/User/SubGHz_Phy/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../../Core/Inc -I../../SubGHz_Phy/App -I../../SubGHz_Phy/Target -I../../../../../../../Utilities/trace/adv_trace -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../../../../../../Utilities/misc -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/timer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

