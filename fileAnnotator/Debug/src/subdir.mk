################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FieldAnnotator.cpp \
../src/Main.cpp 

OBJS += \
./src/FieldAnnotator.o \
./src/Main.o 

CPP_DEPS += \
./src/FieldAnnotator.d \
./src/Main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/mee/workspaces/sefh/sefh/dateRecognizer/include" -I"/home/mee/workspaces/sefh/sefh/utils/include" -I"/home/mee/workspaces/sefh/sefh/unitRecognizer/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


