################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/firmware\ stuff/license.c \
../libraries/firmware\ stuff/trim.c 

OBJS += \
./libraries/firmware\ stuff/license.o \
./libraries/firmware\ stuff/trim.o 

C_DEPS += \
./libraries/firmware\ stuff/license.d \
./libraries/firmware\ stuff/trim.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/firmware\ stuff/license.o: ../libraries/firmware\ stuff/license.c libraries/firmware\ stuff/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Admin/git/CHARTRAK/Software assembly/libraries" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"libraries/firmware stuff/license.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
libraries/firmware\ stuff/trim.o: ../libraries/firmware\ stuff/trim.c libraries/firmware\ stuff/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/Admin/git/CHARTRAK/Software assembly/libraries" -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"libraries/firmware stuff/trim.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libraries-2f-firmware-20-stuff

clean-libraries-2f-firmware-20-stuff:
	-$(RM) ./libraries/firmware\ stuff/license.cyclo ./libraries/firmware\ stuff/license.d ./libraries/firmware\ stuff/license.o ./libraries/firmware\ stuff/license.su ./libraries/firmware\ stuff/trim.cyclo ./libraries/firmware\ stuff/trim.d ./libraries/firmware\ stuff/trim.o ./libraries/firmware\ stuff/trim.su

.PHONY: clean-libraries-2f-firmware-20-stuff

