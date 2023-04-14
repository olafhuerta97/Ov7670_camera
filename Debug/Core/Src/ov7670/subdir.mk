################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ov7670/ov7670.c 

OBJS += \
./Core/Src/ov7670/ov7670.o 

C_DEPS += \
./Core/Src/ov7670/ov7670.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/ov7670/%.o Core/Src/ov7670/%.su Core/Src/ov7670/%.cyclo: ../Core/Src/ov7670/%.c Core/Src/ov7670/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I"C:/Users/Olaf/STM32CubeIDE/workspace_1.9.0/Ov7670_camera/Core/Src/ov7670" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-ov7670

clean-Core-2f-Src-2f-ov7670:
	-$(RM) ./Core/Src/ov7670/ov7670.cyclo ./Core/Src/ov7670/ov7670.d ./Core/Src/ov7670/ov7670.o ./Core/Src/ov7670/ov7670.su

.PHONY: clean-Core-2f-Src-2f-ov7670

