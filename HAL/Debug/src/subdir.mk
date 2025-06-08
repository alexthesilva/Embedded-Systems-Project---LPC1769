################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fgpio.c \
../src/flash.c \
../src/rtchall.c \
../src/spi.c \
../src/timers.c 

C_DEPS += \
./src/fgpio.d \
./src/flash.d \
./src/rtchall.d \
./src/spi.d \
./src/timers.d 

OBJS += \
./src/fgpio.o \
./src/flash.o \
./src/rtchall.o \
./src/spi.o \
./src/timers.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__REDLIB__ -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -I"C:\ISEL\5 semestre\SE\Trabalho\Workspace\HAL\inc" -I"C:\ISEL\5 semestre\SE\Trabalho\Workspace\CMSIS_CORE_LPC17xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/fgpio.d ./src/fgpio.o ./src/flash.d ./src/flash.o ./src/rtchall.d ./src/rtchall.o ./src/spi.d ./src/spi.o ./src/timers.d ./src/timers.o

.PHONY: clean-src

