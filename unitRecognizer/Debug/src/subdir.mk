################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/NumberFormats.cpp \
../src/UnitFieldAnnotator.cpp \
../src/UnitRecognizer.cpp 

OBJS += \
./src/NumberFormats.o \
./src/UnitFieldAnnotator.o \
./src/UnitRecognizer.o 

CPP_DEPS += \
./src/NumberFormats.d \
./src/UnitFieldAnnotator.d \
./src/UnitRecognizer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/oroszgy/workspace/ppke/hundri/utils/include" -I"/home/oroszgy/workspace/ppke/hundri/indri/contrib/lemur/include" -I"/home/oroszgy/workspace/ppke/hundri/indri/include" -I"/home/oroszgy/workspace/ppke/hundri/utils/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


