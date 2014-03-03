################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Cisu.cpp \
../src/Exp.cpp \
../src/SLR.cpp \
../src/Yucu.cpp 

OBJS += \
./src/Cisu.o \
./src/Exp.o \
./src/SLR.o \
./src/Yucu.o 

CPP_DEPS += \
./src/Cisu.d \
./src/Exp.d \
./src/SLR.d \
./src/Yucu.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


