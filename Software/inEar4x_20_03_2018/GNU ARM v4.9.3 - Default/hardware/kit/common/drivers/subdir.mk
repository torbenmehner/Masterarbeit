################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/kit/common/drivers/i2cspm.c \
../hardware/kit/common/drivers/si7013.c \
../hardware/kit/common/drivers/tempsens.c \
../hardware/kit/common/drivers/udelay.c 

OBJS += \
./hardware/kit/common/drivers/i2cspm.o \
./hardware/kit/common/drivers/si7013.o \
./hardware/kit/common/drivers/tempsens.o \
./hardware/kit/common/drivers/udelay.o 

C_DEPS += \
./hardware/kit/common/drivers/i2cspm.d \
./hardware/kit/common/drivers/si7013.d \
./hardware/kit/common/drivers/tempsens.d \
./hardware/kit/common/drivers/udelay.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/kit/common/drivers/i2cspm.o: ../hardware/kit/common/drivers/i2cspm.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__STACK_SIZE=0x800' '-D__HEAP_SIZE=0xD00' '-DFEATURE_BOARD_DETECTED=1' '-DEFR32BG12P432F1024GM48=1' -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Include" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emlib\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\tempdrv\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\drivers" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emlib\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\CMSIS\Include" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\app\bluetooth\common\stack_bridge" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\halconfig" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\halconfig\inc\hal-config" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\radio\rail_lib\common" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\bsp" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\bootloader\api" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Source\GCC" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\common\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Source" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\sleep\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\sleep\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\uartdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\radio\rail_lib\chip\efr32" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\tempdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\bootloader" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\EFR32BG12_BRD4103A\config" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\rtcdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\rtcdrv\config" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/i2cspm.d" -MT"hardware/kit/common/drivers/i2cspm.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/si7013.o: ../hardware/kit/common/drivers/si7013.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__STACK_SIZE=0x800' '-D__HEAP_SIZE=0xD00' '-DFEATURE_BOARD_DETECTED=1' '-DEFR32BG12P432F1024GM48=1' -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Include" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emlib\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\tempdrv\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\drivers" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emlib\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\CMSIS\Include" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\app\bluetooth\common\stack_bridge" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\halconfig" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\halconfig\inc\hal-config" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\radio\rail_lib\common" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\bsp" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\bootloader\api" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Source\GCC" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\common\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Source" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\sleep\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\sleep\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\uartdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\radio\rail_lib\chip\efr32" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\tempdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\bootloader" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\EFR32BG12_BRD4103A\config" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\rtcdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\rtcdrv\config" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/si7013.d" -MT"hardware/kit/common/drivers/si7013.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/tempsens.o: ../hardware/kit/common/drivers/tempsens.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__STACK_SIZE=0x800' '-D__HEAP_SIZE=0xD00' '-DFEATURE_BOARD_DETECTED=1' '-DEFR32BG12P432F1024GM48=1' -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Include" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emlib\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\tempdrv\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\drivers" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emlib\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\CMSIS\Include" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\app\bluetooth\common\stack_bridge" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\halconfig" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\halconfig\inc\hal-config" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\radio\rail_lib\common" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\bsp" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\bootloader\api" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Source\GCC" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\common\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Source" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\sleep\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\sleep\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\uartdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\radio\rail_lib\chip\efr32" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\tempdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\bootloader" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\EFR32BG12_BRD4103A\config" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\rtcdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\rtcdrv\config" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/tempsens.d" -MT"hardware/kit/common/drivers/tempsens.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/udelay.o: ../hardware/kit/common/drivers/udelay.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__STACK_SIZE=0x800' '-D__HEAP_SIZE=0xD00' '-DFEATURE_BOARD_DETECTED=1' '-DEFR32BG12P432F1024GM48=1' -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Include" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emlib\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\tempdrv\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\drivers" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emlib\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\CMSIS\Include" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\app\bluetooth\common\stack_bridge" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\halconfig" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\halconfig\inc\hal-config" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\radio\rail_lib\common" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\common\bsp" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\bootloader\api" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Source\GCC" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\common\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\Device\SiliconLabs\EFR32BG12P\Source" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\sleep\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\sleep\src" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\uartdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\radio\rail_lib\chip\efr32" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\tempdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\bootloader" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\hardware\kit\EFR32BG12_BRD4103A\config" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\rtcdrv\inc" -I"C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\emdrv\rtcdrv\config" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/udelay.d" -MT"hardware/kit/common/drivers/udelay.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


