################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board\ functions/ProgRef.c \
../Board\ functions/RS485.c \
../Board\ functions/TCA9555.c 

OBJS += \
./Board\ functions/ProgRef.o \
./Board\ functions/RS485.o \
./Board\ functions/TCA9555.o 

C_DEPS += \
./Board\ functions/ProgRef.d \
./Board\ functions/RS485.d \
./Board\ functions/TCA9555.d 


# Each subdirectory must supply rules for building sources it contributes
Board\ functions/ProgRef.o: ../Board\ functions/ProgRef.c Board\ functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/git/CHARTRAK/Software assembly" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Board functions/ProgRef.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Board\ functions/RS485.o: ../Board\ functions/RS485.c Board\ functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/git/CHARTRAK/Software assembly" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Board functions/RS485.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Board\ functions/TCA9555.o: ../Board\ functions/TCA9555.c Board\ functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/git/CHARTRAK/Software assembly" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Board functions/TCA9555.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Board-20-functions

clean-Board-20-functions:
	-$(RM) ./Board\ functions/ProgRef.cyclo ./Board\ functions/ProgRef.d ./Board\ functions/ProgRef.o ./Board\ functions/ProgRef.su ./Board\ functions/RS485.cyclo ./Board\ functions/RS485.d ./Board\ functions/RS485.o ./Board\ functions/RS485.su ./Board\ functions/TCA9555.cyclo ./Board\ functions/TCA9555.d ./Board\ functions/TCA9555.o ./Board\ functions/TCA9555.su

.PHONY: clean-Board-20-functions

