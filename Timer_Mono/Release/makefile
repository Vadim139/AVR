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
Timer_Mono.lss \

FLASH_IMAGE += \
Timer_Mono.hex \

EEPROM_IMAGE += \
Timer_Mono.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Timer_Mono.elf secondary-outputs

# Tool invocations
Timer_Mono.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Timer_Mono.map -mmcu=attiny45 -o "Timer_Mono.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Timer_Mono.lss: Timer_Mono.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Timer_Mono.elf  >"Timer_Mono.lss"
	@echo 'Finished building: $@'
	@echo ' '

Timer_Mono.hex: Timer_Mono.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Timer_Mono.elf  "Timer_Mono.hex"
	@echo 'Finished building: $@'
	@echo ' '

Timer_Mono.eep: Timer_Mono.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Timer_Mono.elf  "Timer_Mono.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Timer_Mono.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t Timer_Mono.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Timer_Mono.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
