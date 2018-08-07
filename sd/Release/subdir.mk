################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SPI.c \
../diskio.c \
../ff.c \
../lcd.c \
../lcd_drv.c \
../main.c \
../sdcard.c \
../spisd.c 

OBJS += \
./SPI.o \
./diskio.o \
./ff.o \
./lcd.o \
./lcd_drv.o \
./main.o \
./sdcard.o \
./spisd.o 

C_DEPS += \
./SPI.d \
./diskio.d \
./ff.d \
./lcd.d \
./lcd_drv.d \
./main.d \
./sdcard.d \
./spisd.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


