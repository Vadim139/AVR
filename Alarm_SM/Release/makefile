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
Alarm_SM.lss \

FLASH_IMAGE += \
Alarm_SM.hex \

EEPROM_IMAGE += \
Alarm_SM.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Alarm_SM.elf secondary-outputs

# Tool invocations
Alarm_SM.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Alarm_SM.map -mmcu=atmega644p -o "Alarm_SM.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Alarm_SM.lss: Alarm_SM.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Alarm_SM.elf  >"Alarm_SM.lss"
	@echo 'Finished building: $@'
	@echo ' '

Alarm_SM.hex: Alarm_SM.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Alarm_SM.elf  "Alarm_SM.hex"
	@echo 'Finished building: $@'
	@echo ' '

Alarm_SM.eep: Alarm_SM.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Alarm_SM.elf  "Alarm_SM.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Alarm_SM.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t Alarm_SM.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Alarm_SM.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
