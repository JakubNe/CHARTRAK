################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LOLA\ libs/AWG.c \
../LOLA\ libs/CHARTRAK.c \
../LOLA\ libs/LOLA.c \
../LOLA\ libs/OSC.c 

OBJS += \
./LOLA\ libs/AWG.o \
./LOLA\ libs/CHARTRAK.o \
./LOLA\ libs/LOLA.o \
./LOLA\ libs/OSC.o 

C_DEPS += \
./LOLA\ libs/AWG.d \
./LOLA\ libs/CHARTRAK.d \
./LOLA\ libs/LOLA.d \
./LOLA\ libs/OSC.d 


# Each subdirectory must supply rules for building sources it contributes
LOLA\ libs/AWG.o: ../LOLA\ libs/AWG.c LOLA\ libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/git/CHARTRAK/Software assembly" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/git/CHARTRAK/Software assembly/LOLA libs" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/firmware stuff" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/Board functions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"LOLA libs/AWG.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
LOLA\ libs/CHARTRAK.o: ../LOLA\ libs/CHARTRAK.c LOLA\ libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/git/CHARTRAK/Software assembly" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/git/CHARTRAK/Software assembly/LOLA libs" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/firmware stuff" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/Board functions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"LOLA libs/CHARTRAK.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
LOLA\ libs/LOLA.o: ../LOLA\ libs/LOLA.c LOLA\ libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/git/CHARTRAK/Software assembly" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/git/CHARTRAK/Software assembly/LOLA libs" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/firmware stuff" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/Board functions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"LOLA libs/LOLA.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
LOLA\ libs/OSC.o: ../LOLA\ libs/OSC.c LOLA\ libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/git/CHARTRAK/Software assembly" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/git/CHARTRAK/Software assembly/LOLA libs" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/firmware stuff" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/Board functions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"LOLA libs/OSC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-LOLA-20-libs

clean-LOLA-20-libs:
	-$(RM) ./LOLA\ libs/AWG.cyclo ./LOLA\ libs/AWG.d ./LOLA\ libs/AWG.o ./LOLA\ libs/AWG.su ./LOLA\ libs/CHARTRAK.cyclo ./LOLA\ libs/CHARTRAK.d ./LOLA\ libs/CHARTRAK.o ./LOLA\ libs/CHARTRAK.su ./LOLA\ libs/LOLA.cyclo ./LOLA\ libs/LOLA.d ./LOLA\ libs/LOLA.o ./LOLA\ libs/LOLA.su ./LOLA\ libs/OSC.cyclo ./LOLA\ libs/OSC.d ./LOLA\ libs/OSC.o ./LOLA\ libs/OSC.su

.PHONY: clean-LOLA-20-libs

