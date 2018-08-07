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
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
wyswietlacz_z_licznikiem.lss \

FLASH_IMAGE += \
wyswietlacz_z_licznikiem.hex \

EEPROM_IMAGE += \
wyswietlacz_z_licznikiem.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: wyswietlacz_z_licznikiem.elf secondary-outputs

# Tool invocations
wyswietlacz_z_licznikiem.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,wyswietlacz_z_licznikiem.map -mmcu=atmega8 -o"wyswietlacz_z_licznikiem.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

wyswietlacz_z_licznikiem.lss: wyswietlacz_z_licznikiem.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S wyswietlacz_z_licznikiem.elf  >"wyswietlacz_z_licznikiem.lss"
	@echo 'Finished building: $@'
	@echo ' '

wyswietlacz_z_licznikiem.hex: wyswietlacz_z_licznikiem.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex wyswietlacz_z_licznikiem.elf  "wyswietlacz_z_licznikiem.hex"
	@echo 'Finished building: $@'
	@echo ' '

wyswietlacz_z_licznikiem.eep: wyswietlacz_z_licznikiem.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex wyswietlacz_z_licznikiem.elf  "wyswietlacz_z_licznikiem.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: wyswietlacz_z_licznikiem.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 wyswietlacz_z_licznikiem.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) wyswietlacz_z_licznikiem.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
