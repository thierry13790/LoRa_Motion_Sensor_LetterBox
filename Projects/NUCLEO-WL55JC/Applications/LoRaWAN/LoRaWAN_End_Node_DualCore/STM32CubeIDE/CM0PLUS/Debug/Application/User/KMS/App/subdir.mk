################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node_DualCore/CM0PLUS/KMS/App/app_kms.c 

OBJS += \
./Application/User/KMS/App/app_kms.o 

C_DEPS += \
./Application/User/KMS/App/app_kms.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/KMS/App/app_kms.o: D:/dev/Homekit_LetterBox/en.stm32cubewl_v1-1-0_v1.1.0/STM32Cube_FW_WL_V1.1.0/Projects/NUCLEO-WL55JC/Applications/LoRaWAN/LoRaWAN_End_Node_DualCore/CM0PLUS/KMS/App/app_kms.c Application/User/KMS/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DCORE_CM0PLUS -DKMS_ENABLED -DUSE_HAL_DRIVER -DSTM32WL55xx '-DMBEDTLS_CONFIG_FILE="mbedtls_config.h"' -c -I../../../CM0PLUS/Core/Inc -I../../../CM0PLUS/KMS/App -I../../../CM0PLUS/LoRaWAN/App -I../../../CM0PLUS/LoRaWAN/Target -I../../../CM0PLUS/MbMux -I../../../Common/Board -I../../../Common/MbMux -I../../../Common/System -I../../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -I../../../../../../../../Utilities/trace/adv_trace -I../../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../../../../../../../../Utilities/misc -I../../../../../../../../Utilities/sequencer -I../../../../../../../../Utilities/timer -I../../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler/Packages -I../../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../../Middlewares/ST/STM32_Key_Management_Services/Core -I../../../../../../../../Middlewares/ST/STM32_Key_Management_Services/Modules -I../../../../../../../../Middlewares/ST/STM32_Key_Management_Services/Interface -I../../../../../../../../Middlewares/ST/STM32_Key_Management_Services/Interface/CryptoApi -I../../../../../../../../Middlewares/ST/STM32_Key_Management_Services/Interface/CryptoApi/HAL -I../../../../../../../../Middlewares/ST/STM32_Key_Management_Services/Interface/CryptoApi/MBED -I../../../../../../../../Middlewares/ST/STM32_Key_Management_Services/Interface/CryptoApi/ST -I../../../../../../../../Middlewares/ST/STM32_Key_Management_Services/niKMS -I../../../../../../../../Middlewares/Third_Party/mbed-crypto/include -I../../../../../../../../Middlewares/Third_Party/mbed-crypto/include/mbedtls -I../../../../../../../../Middlewares/Third_Party/mbed-crypto/include/psa -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Crypto -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac/Region -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Mac -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/LmHandler -I../../../../../../../../Middlewares/Third_Party/LoRaWAN/Utilities -I../../../../../../../../Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

