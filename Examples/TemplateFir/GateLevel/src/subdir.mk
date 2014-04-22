################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SynFirGate.cpp \
../src/Top.cpp \
../src/main.cpp 

OBJS += \
./src/SynFirGate.o \
./src/Top.o \
./src/main.o 

CPP_DEPS += \
./src/SynFirGate.d \
./src/Top.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -DSC_GATELEVEL -DSC_ARCHITECTURE -I"$(SYSTEMC)\..\include" -I"C:\Programmer\SystemCrafter\SystemCrafter SC\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


