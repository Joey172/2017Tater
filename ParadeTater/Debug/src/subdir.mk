################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Drive.cpp \
../src/MyRobot.cpp \
../src/Shooter.cpp \
../src/TrapezoidalMove.cpp \
../src/UserInterface.cpp 

OBJS += \
./src/Drive.o \
./src/MyRobot.o \
./src/Shooter.o \
./src/TrapezoidalMove.o \
./src/UserInterface.o 

CPP_DEPS += \
./src/Drive.d \
./src/MyRobot.d \
./src/Shooter.d \
./src/TrapezoidalMove.d \
./src/UserInterface.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/colin/git/2017Tater/ParadeTater/src" -I"/home/colin/wpilib/cpp/current/include" -I"/home/colin/wpilib/user/cpp/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


