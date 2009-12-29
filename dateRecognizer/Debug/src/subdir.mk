################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DateFormat.cpp \
../src/HunDatefieldAnnotator.cpp 

OBJS += \
./src/DateFormat.o \
./src/HunDatefieldAnnotator.o 

CPP_DEPS += \
./src/DateFormat.d \
./src/HunDatefieldAnnotator.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/mee/workspaces/sefh/utils/include" -I"/home/mee/workspaces/sefh/indri/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


