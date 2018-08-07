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
Zgrzewarka.lss \

FLASH_IMAGE += \
Zgrzewarka.hex \

EEPROM_IMAGE += \
Zgrzewarka.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Zgrzewarka.elf secondary-outputs

# Tool invocations
Zgrzewarka.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Zgrzewarka.map -mmcu=atmega8 -o "Zgrzewarka.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Zgrzewarka.lss: Zgrzewarka.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Zgrzewarka.elf  >"Zgrzewarka.lss"
	@echo 'Finished building: $@'
	@echo ' '

Zgrzewarka.hex: Zgrzewarka.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Zgrzewarka.elf  "Zgrzewarka.hex"
	@echo 'Finished building: $@'
	@echo ' '

Zgrzewarka.eep: Zgrzewarka.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Zgrzewarka.elf  "Zgrzewarka.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Zgrzewarka.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 Zgrzewarka.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Zgrzewarka.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
