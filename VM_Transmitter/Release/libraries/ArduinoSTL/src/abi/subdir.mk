################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\libraries\ArduinoSTL\1.1.0\src\abi\abi.cpp 

LINK_OBJ += \
.\libraries\ArduinoSTL\src\abi\abi.cpp.o 

CPP_DEPS += \
.\libraries\ArduinoSTL\src\abi\abi.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries\ArduinoSTL\src\abi\abi.cpp.o: C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\libraries\ArduinoSTL\1.1.0\src\abi\abi.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\eclipse\cpp-oxygen\eclipse\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10802 -DARDUINO_AVR_DUEMILANOVE -DARDUINO_ARCH_AVR   -I"C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\cores\arduino" -I"C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\variants\standard" -I"C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\SPI" -I"C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\SPI\src" -I"C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\libraries\RF24\1.3.1" -I"C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\libraries\RF24\1.3.1\utility" -I"C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\libraries\ArduinoSTL\1.1.0" -I"C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\libraries\ArduinoSTL\1.1.0\src" -I"C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\EEPROM" -I"C:\eclipse\cpp-oxygen\eclipse\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\EEPROM\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


