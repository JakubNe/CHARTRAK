################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/Board\ functions/ProgRef.c \
../libraries/Board\ functions/RS485.c \
../libraries/Board\ functions/TCA9555.c 

OBJS += \
./libraries/Board\ functions/ProgRef.o \
./libraries/Board\ functions/RS485.o \
./libraries/Board\ functions/TCA9555.o 

C_DEPS += \
./libraries/Board\ functions/ProgRef.d \
./libraries/Board\ functions/RS485.d \
./libraries/Board\ functions/TCA9555.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/Board\ functions/ProgRef.o: ../libraries/Board\ functions/ProgRef.c libraries/Board\ functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Admin/git/CHARTRAK/Software assembly/libraries" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"libraries/Board functions/ProgRef.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
libraries/Board\ functions/RS485.o: ../libraries/Board\ functions/RS485.c libraries/Board\ functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Admin/git/CHARTRAK/Software assembly/libraries" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"libraries/Board functions/RS485.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
libraries/Board\ functions/TCA9555.o: ../libraries/Board\ functions/TCA9555.c libraries/Board\ functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Admin/git/CHARTRAK/Software assembly/libraries" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"libraries/Board functions/TCA9555.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libraries-2f-Board-20-functions

clean-libraries-2f-Board-20-functions:
	-$(RM) ./libraries/Board\ functions/ProgRef.cyclo ./libraries/Board\ functions/ProgRef.d ./libraries/Board\ functions/ProgRef.o ./libraries/Board\ functions/ProgRef.su ./libraries/Board\ functions/RS485.cyclo ./libraries/Board\ functions/RS485.d ./libraries/Board\ functions/RS485.o ./libraries/Board\ functions/RS485.su ./libraries/Board\ functions/TCA9555.cyclo ./libraries/Board\ functions/TCA9555.d ./libraries/Board\ functions/TCA9555.o ./libraries/Board\ functions/TCA9555.su

.PHONY: clean-libraries-2f-Board-20-functions

