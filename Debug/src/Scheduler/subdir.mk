################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Scheduler/Sched.c \
../src/Scheduler/Sched_Functions_Implementation.c \
../src/Scheduler/Sched_cfg.c 

OBJS += \
./src/Scheduler/Sched.o \
./src/Scheduler/Sched_Functions_Implementation.o \
./src/Scheduler/Sched_cfg.o 

C_DEPS += \
./src/Scheduler/Sched.d \
./src/Scheduler/Sched_Functions_Implementation.d \
./src/Scheduler/Sched_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
src/Scheduler/%.o: ../src/Scheduler/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


