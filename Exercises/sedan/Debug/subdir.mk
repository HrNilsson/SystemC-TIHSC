################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Body.cpp \
../Cylinder.cpp \
../Engine.cpp \
../Exhaust.cpp \
../FuelMix.cpp \
../Wheel.cpp \
../main.cpp \
../sedan.cpp 

OBJS += \
./Body.o \
./Cylinder.o \
./Engine.o \
./Exhaust.o \
./FuelMix.o \
./Wheel.o \
./main.o \
./sedan.o 

CPP_DEPS += \
./Body.d \
./Cylinder.d \
./Engine.d \
./Exhaust.d \
./FuelMix.d \
./Wheel.d \
./main.d \
./sedan.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I/home/tihsc/systemc-2.2.0/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


