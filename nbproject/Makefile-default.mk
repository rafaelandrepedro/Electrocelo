#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/MC50UNI.V.0.2.3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/MC50UNI.V.0.2.3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=mcc_generated_files/eusart1.c mcc_generated_files/drivers/i2c_simple_master.c mcc_generated_files/examples/i2c1_master_example.c mcc_generated_files/adcc.c mcc_generated_files/device_config.c mcc_generated_files/i2c1_master.c mcc_generated_files/int.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/tmr0.c mcc_generated_files/tmr1.c mcc_generated_files/tmr2.c controlCurrent_MC50.c controlMemory_MC50.c inputs_MC50.c keeloqDecrypt_MC50.c main_MC50.c outputs_MC50.c sm_ControlGate_MC50.c sm_ControlLearning_MC50.c sm_Main_MC50.c sm_MenuConfiguration_MC50.c sm_common_MC50.c eusartpackage.c eusartparser.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/mcc_generated_files/eusart1.p1 ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1 ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1 ${OBJECTDIR}/mcc_generated_files/adcc.p1 ${OBJECTDIR}/mcc_generated_files/device_config.p1 ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1 ${OBJECTDIR}/mcc_generated_files/int.p1 ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 ${OBJECTDIR}/mcc_generated_files/mcc.p1 ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 ${OBJECTDIR}/mcc_generated_files/tmr0.p1 ${OBJECTDIR}/mcc_generated_files/tmr1.p1 ${OBJECTDIR}/mcc_generated_files/tmr2.p1 ${OBJECTDIR}/controlCurrent_MC50.p1 ${OBJECTDIR}/controlMemory_MC50.p1 ${OBJECTDIR}/inputs_MC50.p1 ${OBJECTDIR}/keeloqDecrypt_MC50.p1 ${OBJECTDIR}/main_MC50.p1 ${OBJECTDIR}/outputs_MC50.p1 ${OBJECTDIR}/sm_ControlGate_MC50.p1 ${OBJECTDIR}/sm_ControlLearning_MC50.p1 ${OBJECTDIR}/sm_Main_MC50.p1 ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1 ${OBJECTDIR}/sm_common_MC50.p1 ${OBJECTDIR}/eusartpackage.p1 ${OBJECTDIR}/eusartparser.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/mcc_generated_files/eusart1.p1.d ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1.d ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1.d ${OBJECTDIR}/mcc_generated_files/adcc.p1.d ${OBJECTDIR}/mcc_generated_files/device_config.p1.d ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1.d ${OBJECTDIR}/mcc_generated_files/int.p1.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d ${OBJECTDIR}/mcc_generated_files/mcc.p1.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d ${OBJECTDIR}/controlCurrent_MC50.p1.d ${OBJECTDIR}/controlMemory_MC50.p1.d ${OBJECTDIR}/inputs_MC50.p1.d ${OBJECTDIR}/keeloqDecrypt_MC50.p1.d ${OBJECTDIR}/main_MC50.p1.d ${OBJECTDIR}/outputs_MC50.p1.d ${OBJECTDIR}/sm_ControlGate_MC50.p1.d ${OBJECTDIR}/sm_ControlLearning_MC50.p1.d ${OBJECTDIR}/sm_Main_MC50.p1.d ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1.d ${OBJECTDIR}/sm_common_MC50.p1.d ${OBJECTDIR}/eusartpackage.p1.d ${OBJECTDIR}/eusartparser.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/mcc_generated_files/eusart1.p1 ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1 ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1 ${OBJECTDIR}/mcc_generated_files/adcc.p1 ${OBJECTDIR}/mcc_generated_files/device_config.p1 ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1 ${OBJECTDIR}/mcc_generated_files/int.p1 ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 ${OBJECTDIR}/mcc_generated_files/mcc.p1 ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 ${OBJECTDIR}/mcc_generated_files/tmr0.p1 ${OBJECTDIR}/mcc_generated_files/tmr1.p1 ${OBJECTDIR}/mcc_generated_files/tmr2.p1 ${OBJECTDIR}/controlCurrent_MC50.p1 ${OBJECTDIR}/controlMemory_MC50.p1 ${OBJECTDIR}/inputs_MC50.p1 ${OBJECTDIR}/keeloqDecrypt_MC50.p1 ${OBJECTDIR}/main_MC50.p1 ${OBJECTDIR}/outputs_MC50.p1 ${OBJECTDIR}/sm_ControlGate_MC50.p1 ${OBJECTDIR}/sm_ControlLearning_MC50.p1 ${OBJECTDIR}/sm_Main_MC50.p1 ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1 ${OBJECTDIR}/sm_common_MC50.p1 ${OBJECTDIR}/eusartpackage.p1 ${OBJECTDIR}/eusartparser.p1

# Source Files
SOURCEFILES=mcc_generated_files/eusart1.c mcc_generated_files/drivers/i2c_simple_master.c mcc_generated_files/examples/i2c1_master_example.c mcc_generated_files/adcc.c mcc_generated_files/device_config.c mcc_generated_files/i2c1_master.c mcc_generated_files/int.c mcc_generated_files/interrupt_manager.c mcc_generated_files/mcc.c mcc_generated_files/pin_manager.c mcc_generated_files/tmr0.c mcc_generated_files/tmr1.c mcc_generated_files/tmr2.c controlCurrent_MC50.c controlMemory_MC50.c inputs_MC50.c keeloqDecrypt_MC50.c main_MC50.c outputs_MC50.c sm_ControlGate_MC50.c sm_ControlLearning_MC50.c sm_Main_MC50.c sm_MenuConfiguration_MC50.c sm_common_MC50.c eusartpackage.c eusartparser.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/MC50UNI.V.0.2.3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F46K40
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/mcc_generated_files/eusart1.p1: mcc_generated_files/eusart1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/eusart1.p1 mcc_generated_files/eusart1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/eusart1.d ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1: mcc_generated_files/drivers/i2c_simple_master.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/drivers" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1 mcc_generated_files/drivers/i2c_simple_master.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.d ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1: mcc_generated_files/examples/i2c1_master_example.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/examples" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1 mcc_generated_files/examples/i2c1_master_example.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.d ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/adcc.p1: mcc_generated_files/adcc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/adcc.p1 mcc_generated_files/adcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/adcc.d ${OBJECTDIR}/mcc_generated_files/adcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/adcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/device_config.p1: mcc_generated_files/device_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/device_config.p1 mcc_generated_files/device_config.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/device_config.d ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/i2c1_master.p1: mcc_generated_files/i2c1_master.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1 mcc_generated_files/i2c1_master.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/i2c1_master.d ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/int.p1: mcc_generated_files/int.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/int.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/int.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/int.p1 mcc_generated_files/int.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/int.d ${OBJECTDIR}/mcc_generated_files/int.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/int.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 mcc_generated_files/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/mcc.p1: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/mcc.p1 mcc_generated_files/mcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/mcc.d ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.p1: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 mcc_generated_files/pin_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pin_manager.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr0.p1: mcc_generated_files/tmr0.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr0.p1 mcc_generated_files/tmr0.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr0.d ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr1.p1: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr1.p1 mcc_generated_files/tmr1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr2.p1: mcc_generated_files/tmr2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr2.p1 mcc_generated_files/tmr2.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr2.d ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/controlCurrent_MC50.p1: controlCurrent_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/controlCurrent_MC50.p1.d 
	@${RM} ${OBJECTDIR}/controlCurrent_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/controlCurrent_MC50.p1 controlCurrent_MC50.c 
	@-${MV} ${OBJECTDIR}/controlCurrent_MC50.d ${OBJECTDIR}/controlCurrent_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/controlCurrent_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/controlMemory_MC50.p1: controlMemory_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/controlMemory_MC50.p1.d 
	@${RM} ${OBJECTDIR}/controlMemory_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/controlMemory_MC50.p1 controlMemory_MC50.c 
	@-${MV} ${OBJECTDIR}/controlMemory_MC50.d ${OBJECTDIR}/controlMemory_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/controlMemory_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/inputs_MC50.p1: inputs_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/inputs_MC50.p1.d 
	@${RM} ${OBJECTDIR}/inputs_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/inputs_MC50.p1 inputs_MC50.c 
	@-${MV} ${OBJECTDIR}/inputs_MC50.d ${OBJECTDIR}/inputs_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/inputs_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/keeloqDecrypt_MC50.p1: keeloqDecrypt_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/keeloqDecrypt_MC50.p1.d 
	@${RM} ${OBJECTDIR}/keeloqDecrypt_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/keeloqDecrypt_MC50.p1 keeloqDecrypt_MC50.c 
	@-${MV} ${OBJECTDIR}/keeloqDecrypt_MC50.d ${OBJECTDIR}/keeloqDecrypt_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/keeloqDecrypt_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main_MC50.p1: main_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_MC50.p1.d 
	@${RM} ${OBJECTDIR}/main_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main_MC50.p1 main_MC50.c 
	@-${MV} ${OBJECTDIR}/main_MC50.d ${OBJECTDIR}/main_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/outputs_MC50.p1: outputs_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/outputs_MC50.p1.d 
	@${RM} ${OBJECTDIR}/outputs_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/outputs_MC50.p1 outputs_MC50.c 
	@-${MV} ${OBJECTDIR}/outputs_MC50.d ${OBJECTDIR}/outputs_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/outputs_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sm_ControlGate_MC50.p1: sm_ControlGate_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sm_ControlGate_MC50.p1.d 
	@${RM} ${OBJECTDIR}/sm_ControlGate_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sm_ControlGate_MC50.p1 sm_ControlGate_MC50.c 
	@-${MV} ${OBJECTDIR}/sm_ControlGate_MC50.d ${OBJECTDIR}/sm_ControlGate_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sm_ControlGate_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sm_ControlLearning_MC50.p1: sm_ControlLearning_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sm_ControlLearning_MC50.p1.d 
	@${RM} ${OBJECTDIR}/sm_ControlLearning_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sm_ControlLearning_MC50.p1 sm_ControlLearning_MC50.c 
	@-${MV} ${OBJECTDIR}/sm_ControlLearning_MC50.d ${OBJECTDIR}/sm_ControlLearning_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sm_ControlLearning_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sm_Main_MC50.p1: sm_Main_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sm_Main_MC50.p1.d 
	@${RM} ${OBJECTDIR}/sm_Main_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sm_Main_MC50.p1 sm_Main_MC50.c 
	@-${MV} ${OBJECTDIR}/sm_Main_MC50.d ${OBJECTDIR}/sm_Main_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sm_Main_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sm_MenuConfiguration_MC50.p1: sm_MenuConfiguration_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1.d 
	@${RM} ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1 sm_MenuConfiguration_MC50.c 
	@-${MV} ${OBJECTDIR}/sm_MenuConfiguration_MC50.d ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sm_common_MC50.p1: sm_common_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sm_common_MC50.p1.d 
	@${RM} ${OBJECTDIR}/sm_common_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sm_common_MC50.p1 sm_common_MC50.c 
	@-${MV} ${OBJECTDIR}/sm_common_MC50.d ${OBJECTDIR}/sm_common_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sm_common_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/eusartpackage.p1: eusartpackage.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eusartpackage.p1.d 
	@${RM} ${OBJECTDIR}/eusartpackage.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/eusartpackage.p1 eusartpackage.c 
	@-${MV} ${OBJECTDIR}/eusartpackage.d ${OBJECTDIR}/eusartpackage.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/eusartpackage.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/eusartparser.p1: eusartparser.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eusartparser.p1.d 
	@${RM} ${OBJECTDIR}/eusartparser.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=pickit4    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/eusartparser.p1 eusartparser.c 
	@-${MV} ${OBJECTDIR}/eusartparser.d ${OBJECTDIR}/eusartparser.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/eusartparser.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/mcc_generated_files/eusart1.p1: mcc_generated_files/eusart1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/eusart1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/eusart1.p1 mcc_generated_files/eusart1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/eusart1.d ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/eusart1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1: mcc_generated_files/drivers/i2c_simple_master.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/drivers" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1 mcc_generated_files/drivers/i2c_simple_master.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.d ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/drivers/i2c_simple_master.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1: mcc_generated_files/examples/i2c1_master_example.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files/examples" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1 mcc_generated_files/examples/i2c1_master_example.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.d ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/examples/i2c1_master_example.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/adcc.p1: mcc_generated_files/adcc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/adcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/adcc.p1 mcc_generated_files/adcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/adcc.d ${OBJECTDIR}/mcc_generated_files/adcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/adcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/device_config.p1: mcc_generated_files/device_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/device_config.p1 mcc_generated_files/device_config.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/device_config.d ${OBJECTDIR}/mcc_generated_files/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/i2c1_master.p1: mcc_generated_files/i2c1_master.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1 mcc_generated_files/i2c1_master.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/i2c1_master.d ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/i2c1_master.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/int.p1: mcc_generated_files/int.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/int.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/int.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/int.p1 mcc_generated_files/int.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/int.d ${OBJECTDIR}/mcc_generated_files/int.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/int.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1: mcc_generated_files/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1 mcc_generated_files/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.d ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/mcc.p1: mcc_generated_files/mcc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/mcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/mcc.p1 mcc_generated_files/mcc.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/mcc.d ${OBJECTDIR}/mcc_generated_files/mcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/mcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/pin_manager.p1: mcc_generated_files/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/pin_manager.p1 mcc_generated_files/pin_manager.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/pin_manager.d ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr0.p1: mcc_generated_files/tmr0.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr0.p1 mcc_generated_files/tmr0.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr0.d ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr1.p1: mcc_generated_files/tmr1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr1.p1 mcc_generated_files/tmr1.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr1.d ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/mcc_generated_files/tmr2.p1: mcc_generated_files/tmr2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/mcc_generated_files" 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${RM} ${OBJECTDIR}/mcc_generated_files/tmr2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/mcc_generated_files/tmr2.p1 mcc_generated_files/tmr2.c 
	@-${MV} ${OBJECTDIR}/mcc_generated_files/tmr2.d ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/mcc_generated_files/tmr2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/controlCurrent_MC50.p1: controlCurrent_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/controlCurrent_MC50.p1.d 
	@${RM} ${OBJECTDIR}/controlCurrent_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/controlCurrent_MC50.p1 controlCurrent_MC50.c 
	@-${MV} ${OBJECTDIR}/controlCurrent_MC50.d ${OBJECTDIR}/controlCurrent_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/controlCurrent_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/controlMemory_MC50.p1: controlMemory_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/controlMemory_MC50.p1.d 
	@${RM} ${OBJECTDIR}/controlMemory_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/controlMemory_MC50.p1 controlMemory_MC50.c 
	@-${MV} ${OBJECTDIR}/controlMemory_MC50.d ${OBJECTDIR}/controlMemory_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/controlMemory_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/inputs_MC50.p1: inputs_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/inputs_MC50.p1.d 
	@${RM} ${OBJECTDIR}/inputs_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/inputs_MC50.p1 inputs_MC50.c 
	@-${MV} ${OBJECTDIR}/inputs_MC50.d ${OBJECTDIR}/inputs_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/inputs_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/keeloqDecrypt_MC50.p1: keeloqDecrypt_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/keeloqDecrypt_MC50.p1.d 
	@${RM} ${OBJECTDIR}/keeloqDecrypt_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/keeloqDecrypt_MC50.p1 keeloqDecrypt_MC50.c 
	@-${MV} ${OBJECTDIR}/keeloqDecrypt_MC50.d ${OBJECTDIR}/keeloqDecrypt_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/keeloqDecrypt_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main_MC50.p1: main_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_MC50.p1.d 
	@${RM} ${OBJECTDIR}/main_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/main_MC50.p1 main_MC50.c 
	@-${MV} ${OBJECTDIR}/main_MC50.d ${OBJECTDIR}/main_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/outputs_MC50.p1: outputs_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/outputs_MC50.p1.d 
	@${RM} ${OBJECTDIR}/outputs_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/outputs_MC50.p1 outputs_MC50.c 
	@-${MV} ${OBJECTDIR}/outputs_MC50.d ${OBJECTDIR}/outputs_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/outputs_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sm_ControlGate_MC50.p1: sm_ControlGate_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sm_ControlGate_MC50.p1.d 
	@${RM} ${OBJECTDIR}/sm_ControlGate_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sm_ControlGate_MC50.p1 sm_ControlGate_MC50.c 
	@-${MV} ${OBJECTDIR}/sm_ControlGate_MC50.d ${OBJECTDIR}/sm_ControlGate_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sm_ControlGate_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sm_ControlLearning_MC50.p1: sm_ControlLearning_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sm_ControlLearning_MC50.p1.d 
	@${RM} ${OBJECTDIR}/sm_ControlLearning_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sm_ControlLearning_MC50.p1 sm_ControlLearning_MC50.c 
	@-${MV} ${OBJECTDIR}/sm_ControlLearning_MC50.d ${OBJECTDIR}/sm_ControlLearning_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sm_ControlLearning_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sm_Main_MC50.p1: sm_Main_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sm_Main_MC50.p1.d 
	@${RM} ${OBJECTDIR}/sm_Main_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sm_Main_MC50.p1 sm_Main_MC50.c 
	@-${MV} ${OBJECTDIR}/sm_Main_MC50.d ${OBJECTDIR}/sm_Main_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sm_Main_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sm_MenuConfiguration_MC50.p1: sm_MenuConfiguration_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1.d 
	@${RM} ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1 sm_MenuConfiguration_MC50.c 
	@-${MV} ${OBJECTDIR}/sm_MenuConfiguration_MC50.d ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sm_MenuConfiguration_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sm_common_MC50.p1: sm_common_MC50.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/sm_common_MC50.p1.d 
	@${RM} ${OBJECTDIR}/sm_common_MC50.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sm_common_MC50.p1 sm_common_MC50.c 
	@-${MV} ${OBJECTDIR}/sm_common_MC50.d ${OBJECTDIR}/sm_common_MC50.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sm_common_MC50.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/eusartpackage.p1: eusartpackage.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eusartpackage.p1.d 
	@${RM} ${OBJECTDIR}/eusartpackage.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/eusartpackage.p1 eusartpackage.c 
	@-${MV} ${OBJECTDIR}/eusartpackage.d ${OBJECTDIR}/eusartpackage.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/eusartpackage.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/eusartparser.p1: eusartparser.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/eusartparser.p1.d 
	@${RM} ${OBJECTDIR}/eusartparser.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/eusartparser.p1 eusartparser.c 
	@-${MV} ${OBJECTDIR}/eusartparser.d ${OBJECTDIR}/eusartparser.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/eusartparser.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/MC50UNI.V.0.2.3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/MC50UNI.V.0.2.3.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=pickit4  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/MC50UNI.V.0.2.3.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/MC50UNI.V.0.2.3.X.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/MC50UNI.V.0.2.3.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/MC50UNI.V.0.2.3.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1    -fno-short-double -fno-short-float -memi=wordwrite -Os -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/MC50UNI.V.0.2.3.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
