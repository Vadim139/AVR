################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Ster_temp.lss \

FLASH_IMAGE += \
Ster_temp.hex \

EEPROM_IMAGE += \
Ster_temp.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Ster_temp.elf secondary-outputs

# Tool invocations
Ster_temp.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Ster_temp.map -mmcu=atmega8 -o "Ster_temp.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Ster_temp.lss: Ster_temp.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Ster_temp.elf  >"Ster_temp.lss"
	@echo 'Finished building: $@'
	@echo ' '

Ster_temp.hex: Ster_temp.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Ster_temp.elf  "Ster_temp.hex"
	@echo 'Finished building: $@'
	@echo ' '

Ster_temp.eep: Ster_temp.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Ster_temp.elf  "Ster_temp.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Ster_temp.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t Ster_temp.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Ster_temp.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
