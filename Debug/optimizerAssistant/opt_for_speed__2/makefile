################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Inits.obj" \
"./OrbitOLEDInterface.obj" \
"./PID_controller.obj" \
"./PWM_rotors.obj" \
"./alt_ADC.obj" \
"./buttons.obj" \
"./circBufT.obj" \
"./control_system.obj" \
"./draw_display.obj" \
"./helicopter_project.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./uartstdio.obj" \
"./yaw_functions.obj" \
"./lib_OrbitOled/ChrFont0.obj" \
"./lib_OrbitOled/FillPat.obj" \
"./lib_OrbitOled/OrbitOled.obj" \
"./lib_OrbitOled/OrbitOledChar.obj" \
"./lib_OrbitOled/OrbitOledGrph.obj" \
"./lib_OrbitOled/delay.obj" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"C:/ti/TivaWare_C_Series-2.1.3.156/driverlib/ccs/Debug/driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include lib_OrbitOled/subdir_vars.mk
-include subdir_rules.mk
-include lib_OrbitOled/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
HeliProject.out \

EXE_OUTPUTS__QUOTED += \
"HeliProject.out" \

BIN_OUTPUTS += \
HeliProject.hex \

BIN_OUTPUTS__QUOTED += \
"HeliProject.hex" \


# All Target
all: HeliProject.out

# Tool invocations
HeliProject.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --opt_for_speed=2 -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --diag_wrap=off --diag_warning=225 --display_error_number --abi=eabi -z -m"HeliProject.map" --stack_size=1024 --heap_size=1024 -i"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/lib" -i"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/include" --reread_libs --diag_wrap=off --warn_sections --display_error_number --xml_link_info="HeliProject_linkInfo.xml" --rom_model -o "HeliProject.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

HeliProject.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv6/tools/compiler/arm_15.12.3.LTS/bin/armhex"  -o "HeliProject.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "Inits.d" "OrbitOLEDInterface.d" "PID_controller.d" "PWM_rotors.d" "alt_ADC.d" "buttons.d" "circBufT.d" "control_system.d" "draw_display.d" "helicopter_project.d" "tm4c123gh6pm_startup_ccs.d" "uartstdio.d" "yaw_functions.d" "lib_OrbitOled\ChrFont0.d" "lib_OrbitOled\FillPat.d" "lib_OrbitOled\OrbitOled.d" "lib_OrbitOled\OrbitOledChar.d" "lib_OrbitOled\OrbitOledGrph.d" "lib_OrbitOled\delay.d" 
	-$(RM) "Inits.obj" "OrbitOLEDInterface.obj" "PID_controller.obj" "PWM_rotors.obj" "alt_ADC.obj" "buttons.obj" "circBufT.obj" "control_system.obj" "draw_display.obj" "helicopter_project.obj" "tm4c123gh6pm_startup_ccs.obj" "uartstdio.obj" "yaw_functions.obj" "lib_OrbitOled\ChrFont0.obj" "lib_OrbitOled\FillPat.obj" "lib_OrbitOled\OrbitOled.obj" "lib_OrbitOled\OrbitOledChar.obj" "lib_OrbitOled\OrbitOledGrph.obj" "lib_OrbitOled\delay.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

