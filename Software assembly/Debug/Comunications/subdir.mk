################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Comunications/RS485.c 

OBJS += \
./Comunications/RS485.o 

C_DEPS += \
./Comunications/RS485.d 


# Each subdirectory must supply rules for building sources it contributes
Comunications/%.o Comunications/%.su Comunications/%.cyclo: ../Comunications/%.c Comunications/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/git/CHARTRAK/Software assembly" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/git/CHARTRAK/Software assembly/LOLA libs" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/firmware stuff" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/Board functions" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/Comunications" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Comunications

clean-Comunications:
	-$(RM) ./Comunications/RS485.cyclo ./Comunications/RS485.d ./Comunications/RS485.o ./Comunications/RS485.su

.PHONY: clean-Comunications

