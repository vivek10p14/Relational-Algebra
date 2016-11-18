################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/database_operations.cpp \
../src/evaluation.cpp \
../src/file_operations.cpp \
../src/infix_postfix.cpp \
../src/initialize.cpp \
../src/main.cpp \
../src/nested.cpp \
../src/product.cpp \
../src/project.cpp \
../src/rename.cpp \
../src/select.cpp \
../src/set_difference.cpp \
../src/string_modifications.cpp \
../src/syntax_checks.cpp \
../src/table_operations.cpp \
../src/terminal.cpp \
../src/union.cpp 

OBJS += \
./src/database_operations.o \
./src/evaluation.o \
./src/file_operations.o \
./src/infix_postfix.o \
./src/initialize.o \
./src/main.o \
./src/nested.o \
./src/product.o \
./src/project.o \
./src/rename.o \
./src/select.o \
./src/set_difference.o \
./src/string_modifications.o \
./src/syntax_checks.o \
./src/table_operations.o \
./src/terminal.o \
./src/union.o 

CPP_DEPS += \
./src/database_operations.d \
./src/evaluation.d \
./src/file_operations.d \
./src/infix_postfix.d \
./src/initialize.d \
./src/main.d \
./src/nested.d \
./src/product.d \
./src/project.d \
./src/rename.d \
./src/select.d \
./src/set_difference.d \
./src/string_modifications.d \
./src/syntax_checks.d \
./src/table_operations.d \
./src/terminal.d \
./src/union.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


