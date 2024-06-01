################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/AWG.c \
../libraries/CHARTRAK.c \
../libraries/LOLA.c \
../libraries/OSC.c \
../libraries/ProgRef.c \
../libraries/RS485.c \
../libraries/SCPI.c \
../libraries/TCA9555.c \
../libraries/calculate.c \
../libraries/license.c \
../libraries/trim.c 

OBJS += \
./libraries/AWG.o \
./libraries/CHARTRAK.o \
./libraries/LOLA.o \
./libraries/OSC.o \
./libraries/ProgRef.o \
./libraries/RS485.o \
./libraries/SCPI.o \
./libraries/TCA9555.o \
./libraries/calculate.o \
./libraries/license.o \
./libraries/trim.o 

C_DEPS += \
./libraries/AWG.d \
./libraries/CHARTRAK.d \
./libraries/LOLA.d \
./libraries/OSC.d \
./libraries/ProgRef.d \
./libraries/RS485.d \
./libraries/SCPI.d \
./libraries/TCA9555.d \
./libraries/calculate.d \
./libraries/license.d \
./libraries/trim.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/%.o libraries/%.su libraries/%.cyclo: ../libraries/%.c libraries/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"D:/dokumenty/STM32CubeIDE_1.13.1/CHARTRAK2v3_controllerRETARGETED/libraries" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libraries

clean-libraries:
	-$(RM) ./libraries/AWG.cyclo ./libraries/AWG.d ./libraries/AWG.o ./libraries/AWG.su ./libraries/CHARTRAK.cyclo ./libraries/CHARTRAK.d ./libraries/CHARTRAK.o ./libraries/CHARTRAK.su ./libraries/LOLA.cyclo ./libraries/LOLA.d ./libraries/LOLA.o ./libraries/LOLA.su ./libraries/OSC.cyclo ./libraries/OSC.d ./libraries/OSC.o ./libraries/OSC.su ./libraries/ProgRef.cyclo ./libraries/ProgRef.d ./libraries/ProgRef.o ./libraries/ProgRef.su ./libraries/RS485.cyclo ./libraries/RS485.d ./libraries/RS485.o ./libraries/RS485.su ./libraries/SCPI.cyclo ./libraries/SCPI.d ./libraries/SCPI.o ./libraries/SCPI.su ./libraries/TCA9555.cyclo ./libraries/TCA9555.d ./libraries/TCA9555.o ./libraries/TCA9555.su ./libraries/calculate.cyclo ./libraries/calculate.d ./libraries/calculate.o ./libraries/calculate.su ./libraries/license.cyclo ./libraries/license.d ./libraries/license.o ./libraries/license.su ./libraries/trim.cyclo ./libraries/trim.d ./libraries/trim.o ./libraries/trim.su

.PHONY: clean-libraries

