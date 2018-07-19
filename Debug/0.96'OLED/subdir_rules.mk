################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
0.96'OLED/OLED.obj: ../0.96'OLED/OLED.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/Project_Program/Ccs/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="F:/ProjectFile/ccs/Four_axes_2018" --include_path="F:/ProjectFile/ccs/Four_axes_2018/VisualScopeOutput" --include_path="F:/ProjectFile/ccs/Four_axes_2018/MavLink_Receive" --include_path="F:/ProjectFile/ccs/Four_axes_2018/Filter" --include_path="F:/ProjectFile/ccs/Four_axes_2018/Pid" --include_path="F:/ProjectFile/ccs/Four_axes_2018/sonar" --include_path="F:/ProjectFile/ccs/Four_axes_2018/Beep" --include_path="F:/ProjectFile/ccs/Four_axes_2018/colorful_LED" --include_path="F:/ProjectFile/ccs/Four_axes_2018/key" --include_path="F:/ProjectFile/ccs/Four_axes_2018/Pwm" --include_path="F:/ProjectFile/ccs/Four_axes_2018/Timer" --include_path="F:/ProjectFile/ccs/Four_axes_2018/uart" --include_path="F:/ProjectFile/ccs/Four_axes_2018/delay" --include_path="D:/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/Project_Program/Ccs/ccsv8/tools/compiler/ti-cgt-arm_18.1.2.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="0.96'OLED/OLED.d_raw" --obj_directory="0.96'OLED" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


