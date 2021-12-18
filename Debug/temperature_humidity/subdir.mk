################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../temperature_humidity/hts.c 

OBJS += \
./temperature_humidity/hts.o 

C_DEPS += \
./temperature_humidity/hts.d 


# Each subdirectory must supply rules for building sources it contributes
temperature_humidity/%.o: ../temperature_humidity/%.c temperature_humidity/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303x8 -DDEBUG -DUSE_FULL_LL_DRIVER -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

