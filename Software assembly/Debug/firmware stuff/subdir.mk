################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../firmware\ stuff/license.c \
../firmware\ stuff/trim.c 

OBJS += \
./firmware\ stuff/license.o \
./firmware\ stuff/trim.o 

C_DEPS += \
./firmware\ stuff/license.d \
./firmware\ stuff/trim.d 


# Each subdirectory must supply rules for building sources it contributes
firmware\ stuff/license.o: ../firmware\ stuff/license.c firmware\ stuff/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/git/CHARTRAK/Software assembly" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/git/CHARTRAK/Software assembly/LOLA libs" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/firmware stuff" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/Board functions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"firmware stuff/license.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
firmware\ stuff/trim.o: ../firmware\ stuff/trim.c firmware\ stuff/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"C:/Users/Admin/git/CHARTRAK/Software assembly" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/git/CHARTRAK/Software assembly/LOLA libs" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/firmware stuff" -I"C:/Users/Admin/git/CHARTRAK/Software assembly/Board functions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"firmware stuff/trim.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-firmware-20-stuff

clean-firmware-20-stuff:
	-$(RM) ./firmware\ stuff/license.cyclo ./firmware\ stuff/license.d ./firmware\ stuff/license.o ./firmware\ stuff/license.su ./firmware\ stuff/trim.cyclo ./firmware\ stuff/trim.d ./firmware\ stuff/trim.o ./firmware\ stuff/trim.su

.PHONY: clean-firmware-20-stuff

