################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CMSIS/system_MKL25Z4.c 

C_DEPS += \
./CMSIS/system_MKL25Z4.d 

OBJS += \
./CMSIS/system_MKL25Z4.o 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/%.o: ../CMSIS/%.c CMSIS/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -DSDK_DEBUGCONSOLE=1 -I"C:\Users\Shashank C\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PES_Assignment_4\board" -I"C:\Users\Shashank C\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PES_Assignment_4\source" -I"C:\Users\Shashank C\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PES_Assignment_4" -I"C:\Users\Shashank C\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PES_Assignment_4\drivers" -I"C:\Users\Shashank C\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PES_Assignment_4\CMSIS" -I"C:\Users\Shashank C\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PES_Assignment_4\utilities" -I"C:\Users\Shashank C\Documents\MCUXpressoIDE_11.6.0_8187\workspace\PES_Assignment_4\startup" -O0 -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-CMSIS

clean-CMSIS:
	-$(RM) ./CMSIS/system_MKL25Z4.d ./CMSIS/system_MKL25Z4.o

.PHONY: clean-CMSIS

