################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

C_DEPS += \
./utilities/fsl_debug_console.d 

OBJS += \
./utilities/fsl_debug_console.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=1 -I"C:\Users\Shashank C\Downloads\PES_Assignment_4-main\PES_Assignment_4-main\board" -I"C:\Users\Shashank C\Downloads\PES_Assignment_4-main\PES_Assignment_4-main\source" -I"C:\Users\Shashank C\Downloads\PES_Assignment_4-main\PES_Assignment_4-main" -I"C:\Users\Shashank C\Downloads\PES_Assignment_4-main\PES_Assignment_4-main\drivers" -I"C:\Users\Shashank C\Downloads\PES_Assignment_4-main\PES_Assignment_4-main\CMSIS" -I"C:\Users\Shashank C\Downloads\PES_Assignment_4-main\PES_Assignment_4-main\utilities" -I"C:\Users\Shashank C\Downloads\PES_Assignment_4-main\PES_Assignment_4-main\startup" -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o

.PHONY: clean-utilities

