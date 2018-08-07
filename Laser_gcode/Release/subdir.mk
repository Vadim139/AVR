################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../coolant_control.c \
../eeprom.c \
../gcode.c \
../jog.c \
../limits.c \
../main.c \
../motion_control.c \
../nuts_bolts.c \
../planner.c \
../print.c \
../probe.c \
../protocol.c \
../report.c \
../serial.c \
../settings.c \
../spindle_control.c \
../stepper.c \
../system.c 

OBJS += \
./coolant_control.o \
./eeprom.o \
./gcode.o \
./jog.o \
./limits.o \
./main.o \
./motion_control.o \
./nuts_bolts.o \
./planner.o \
./print.o \
./probe.o \
./protocol.o \
./report.o \
./serial.o \
./settings.o \
./spindle_control.o \
./stepper.o \
./system.o 

C_DEPS += \
./coolant_control.d \
./eeprom.d \
./gcode.d \
./jog.d \
./limits.d \
./main.d \
./motion_control.d \
./nuts_bolts.d \
./planner.d \
./print.d \
./probe.d \
./protocol.d \
./report.d \
./serial.d \
./settings.d \
./spindle_control.d \
./stepper.d \
./system.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


