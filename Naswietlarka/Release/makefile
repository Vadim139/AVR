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
Naswietlarka.lss \

FLASH_IMAGE += \
Naswietlarka.hex \

EEPROM_IMAGE += \
Naswietlarka.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Naswietlarka.elf secondary-outputs

# Tool invocations
Naswietlarka.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Naswietlarka.map -mmcu=atmega8 -o"Naswietlarka.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Naswietlarka.lss: Naswietlarka.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Naswietlarka.elf  >"Naswietlarka.lss"
	@echo 'Finished building: $@'
	@echo ' '

Naswietlarka.hex: Naswietlarka.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Naswietlarka.elf  "Naswietlarka.hex"
	@echo 'Finished building: $@'
	@echo ' '

Naswietlarka.eep: Naswietlarka.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Naswietlarka.elf  "Naswietlarka.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Naswietlarka.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 Naswietlarka.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Naswietlarka.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
