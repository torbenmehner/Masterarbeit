################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include protocol/bluetooth/lib/EFR32BG12P/GCC/subdir.mk
-include platform/emlib/src/subdir.mk
-include platform/emdrv/tempdrv/src/subdir.mk
-include platform/emdrv/sleep/src/subdir.mk
-include platform/emdrv/rtcdrv/src/subdir.mk
-include platform/emdrv/gpiointerrupt/src/subdir.mk
-include platform/Device/SiliconLabs/EFR32BG12P/Source/GCC/subdir.mk
-include platform/Device/SiliconLabs/EFR32BG12P/Source/subdir.mk
-include hardware/kit/common/drivers/subdir.mk
-include hardware/kit/common/bsp/subdir.mk
-include Sink/subdir.mk
-include Libs/FatFS/subdir.mk
-include Libs/subdir.mk
-include BMP388_Bosch/subdir.mk
-include BMP280_Bosch/subdir.mk
-include BMI160_Bosch/subdir.mk
-include BME680_Bosch/subdir.mk
-include AFE44x0/subdir.mk
-include ADS129x/subdir.mk
-include ADS1292/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: inEar4x_20_03_2018.axf

# Tool invocations
inEar4x_20_03_2018.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -T "C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\efr32bg12p432f1024gm48.ld" -Xlinker --gc-sections -Xlinker -Map="inEar4x_20_03_2018.map" -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o inEar4x_20_03_2018.axf -Wl,--start-group "./ADS1292/ads1292.o" "./ADS129x/ads129x.o" "./AFE44x0/AFE44x0.o" "./BME680_Bosch/bme680.o" "./BME680_Bosch/bme680_selftest.o" "./BMI160_Bosch/bmi160.o" "./BMP280_Bosch/bmp280.o" "./BMP280_Bosch/bmp280_support.o" "./BMP280_Bosch/bosch_support_FZI.o" "./BMP388_Bosch/bmp3.o" "./Libs/FatFS/diskio.o" "./Libs/FatFS/ff.o" "./Libs/FatFS/ffunicode.o" "./Libs/FatFS/microsd.o" "./Libs/FatFS/syscall.o" "./Libs/FreeRTOS_Stream_Buffer.o" "./Libs/i2cfunctions.o" "./Libs/ringbuffer.o" "./Sink/sdcard_common.o" "./Sink/sdcard_debug.o" "./Sink/sdcard_unisens.o" "./application_properties.o" "./gatt_db.o" "./init_app.o" "./init_board.o" "./init_mcu.o" "./main.o" "./pti.o" "./timer0.o" "./timer1.o" "./hardware/kit/common/bsp/bsp_stk.o" "./hardware/kit/common/drivers/i2cspm.o" "./hardware/kit/common/drivers/si7013.o" "./hardware/kit/common/drivers/tempsens.o" "./hardware/kit/common/drivers/udelay.o" "./platform/Device/SiliconLabs/EFR32BG12P/Source/GCC/startup_efr32bg12p.o" "./platform/Device/SiliconLabs/EFR32BG12P/Source/system_efr32bg12p.o" "./platform/emdrv/gpiointerrupt/src/gpiointerrupt.o" "./platform/emdrv/rtcdrv/src/rtcdriver.o" "./platform/emdrv/sleep/src/sleep.o" "./platform/emdrv/tempdrv/src/tempdrv.o" "./platform/emlib/src/em_cmu.o" "./platform/emlib/src/em_core.o" "./platform/emlib/src/em_cryotimer.o" "./platform/emlib/src/em_crypto.o" "./platform/emlib/src/em_emu.o" "./platform/emlib/src/em_gpio.o" "./platform/emlib/src/em_i2c.o" "./platform/emlib/src/em_letimer.o" "./platform/emlib/src/em_msc.o" "./platform/emlib/src/em_rmu.o" "./platform/emlib/src/em_rtcc.o" "./platform/emlib/src/em_system.o" "./platform/emlib/src/em_timer.o" "./platform/emlib/src/em_usart.o" "./src/obssel.o" "C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\lib\EFR32BG12P\GCC\binapploader.o" "C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\lib\EFR32BG12P\GCC\libmbedtls.a" "C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\lib\EFR32BG12P\GCC\libpsstore.a" "C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\platform\radio\rail_lib\autogen\librail_release\librail_efr32xg12_gcc_release.a" "C:\Users\diehl\SimplicityStudio\v4_workspace2\inEar4x_20_03_2018\protocol\bluetooth\lib\EFR32BG12P\GCC\libbluetooth.a" -lm -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: inEar4x_20_03_2018.hex'
	arm-none-eabi-objcopy -O ihex "inEar4x_20_03_2018.axf" "inEar4x_20_03_2018.hex"
	@echo ' '

	@echo 'Building bin file: inEar4x_20_03_2018.bin'
	arm-none-eabi-objcopy -O binary "inEar4x_20_03_2018.axf" "inEar4x_20_03_2018.bin"
	@echo ' '

	@echo 'Building s37 file: inEar4x_20_03_2018.s37'
	arm-none-eabi-objcopy -O srec "inEar4x_20_03_2018.axf" "inEar4x_20_03_2018.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "inEar4x_20_03_2018.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) inEar4x_20_03_2018.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
