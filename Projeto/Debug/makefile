################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Projeto
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: Projeto.axf

# Tool invocations
Projeto.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\ISEL\5 semestre\SE\Trabalho\Workspace\HAL\Debug" -L"C:\ISEL\5 semestre\SE\Trabalho\Workspace\DRIVERS\Debug" -L"C:\ISEL\5 semestre\SE\Trabalho\Workspace\CMSIS_CORE_LPC17xx\Debug" -L"C:\ISEL\5 semestre\SE\Trabalho\Workspace\BH1750\Release" -Xlinker -Map="Projeto.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "Projeto_Debug.ld" -o "Projeto.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Projeto.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Projeto.axf"; # arm-none-eabi-objcopy -v -O binary "Projeto.axf" "Projeto.bin" ; # checksum -p LPC1769 -d "Projeto.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
