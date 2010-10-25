################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Configuration.cpp \
../src/StringConverter.cpp \
../src/Unit.cpp \
../src/xmlParser.cpp 

OBJS += \
./src/Configuration.o \
./src/StringConverter.o \
./src/Unit.o \
./src/xmlParser.o 

CPP_DEPS += \
./src/Configuration.d \
./src/StringConverter.d \
./src/Unit.d \
./src/xmlParser.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


