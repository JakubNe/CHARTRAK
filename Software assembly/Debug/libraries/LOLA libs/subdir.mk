################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/LOLA\ libs/AWG.c \
../libraries/LOLA\ libs/CHARTRAK.c \
../libraries/LOLA\ libs/LOLA.c \
../libraries/LOLA\ libs/OSC.c 

OBJS += \
./libraries/LOLA\ libs/AWG.o \
./libraries/LOLA\ libs/CHARTRAK.o \
./libraries/LOLA\ libs/LOLA.o \
./libraries/LOLA\ libs/OSC.o 

C_DEPS += \
./libraries/LOLA\ libs/AWG.d \
./libraries/LOLA\ libs/CHARTRAK.d \
./libraries/LOLA\ libs/LOLA.d \
./libraries/LOLA\ libs/OSC.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/LOLA\ libs/AWG.o: ../libraries/LOLA\ libs/AWG.c libraries/LOLA\ libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Admin/git/CHARTRAK/Software assembly/libraries" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"libraries/LOLA libs/AWG.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
libraries/LOLA\ libs/CHARTRAK.o: ../libraries/LOLA\ libs/CHARTRAK.c libraries/LOLA\ libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Admin/git/CHARTRAK/Software assembly/libraries" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"libraries/LOLA libs/CHARTRAK.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
libraries/LOLA\ libs/LOLA.o: ../libraries/LOLA\ libs/LOLA.c libraries/LOLA\ libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Admin/git/CHARTRAK/Software assembly/libraries" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"libraries/LOLA libs/LOLA.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
libraries/LOLA\ libs/OSC.o: ../libraries/LOLA\ libs/OSC.c libraries/LOLA\ libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Admin/git/CHARTRAK/Software assembly/libraries" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"libraries/LOLA libs/OSC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libraries-2f-LOLA-20-libs

clean-libraries-2f-LOLA-20-libs:
	-$(RM) ./libraries/LOLA\ libs/AWG.cyclo ./libraries/LOLA\ libs/AWG.d ./libraries/LOLA\ libs/AWG.o ./libraries/LOLA\ libs/AWG.su ./libraries/LOLA\ libs/CHARTRAK.cyclo ./libraries/LOLA\ libs/CHARTRAK.d ./libraries/LOLA\ libs/CHARTRAK.o ./libraries/LOLA\ libs/CHARTRAK.su ./libraries/LOLA\ libs/LOLA.cyclo ./libraries/LOLA\ libs/LOLA.d ./libraries/LOLA\ libs/LOLA.o ./libraries/LOLA\ libs/LOLA.su ./libraries/LOLA\ libs/OSC.cyclo ./libraries/LOLA\ libs/OSC.d ./libraries/LOLA\ libs/OSC.o ./libraries/LOLA\ libs/OSC.su

.PHONY: clean-libraries-2f-LOLA-20-libs

