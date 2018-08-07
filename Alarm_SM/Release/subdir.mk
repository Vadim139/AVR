################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DS18B20.c \
../I2C_slave.c \
../MFRC522.c \
../RS485.c \
../lcd_drv.c \
../main.c \
../pgmspace.c \
../uart.c \
../variables.c 

OBJS += \
./DS18B20.o \
./I2C_slave.o \
./MFRC522.o \
./RS485.o \
./lcd_drv.o \
./main.o \
./pgmspace.o \
./uart.o \
./variables.o 

C_DEPS += \
./DS18B20.d \
./I2C_slave.d \
./MFRC522.d \
./RS485.d \
./lcd_drv.d \
./main.d \
./pgmspace.d \
./uart.d \
./variables.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


