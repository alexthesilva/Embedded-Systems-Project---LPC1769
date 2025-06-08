################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/display.c \
../src/eeprom.c \
../src/encoder.c \
../src/led.c \
../src/pir.c \
../src/rtc.c 

C_DEPS += \
./src/display.d \
./src/eeprom.d \
./src/encoder.d \
./src/led.d \
./src/pir.d \
./src/rtc.d 

OBJS += \
./src/display.o \
./src/eeprom.o \
./src/encoder.o \
./src/led.o \
./src/pir.o \
./src/rtc.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__REDLIB__ -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -I"C:\ISEL\5 semestre\SE\Trabalho\Workspace\DRIVERS\inc" -I"C:\ISEL\5 semestre\SE\Trabalho\Workspace\HAL\inc" -I"C:\ISEL\5 semestre\SE\Trabalho\Workspace\CMSIS_CORE_LPC17xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/display.d ./src/display.o ./src/eeprom.d ./src/eeprom.o ./src/encoder.d ./src/encoder.o ./src/led.d ./src/led.o ./src/pir.d ./src/pir.o ./src/rtc.d ./src/rtc.o

.PHONY: clean-src

