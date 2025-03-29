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
FINAL_IMAGE=${DISTDIR}/cansat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/cansat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/clock/clock.c src/hc12/sercom5_usart.c src/hc12/hc12.c src/usb_serial/sercom3_usart.c src/usb_serial/usb_serial.c src/main.c src/delay_timer/delay_timer.c src/pm_sensor/sercom1_usart.c src/pm_sensor/pm_sensor.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/clock/clock.o ${OBJECTDIR}/src/hc12/sercom5_usart.o ${OBJECTDIR}/src/hc12/hc12.o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o ${OBJECTDIR}/src/usb_serial/usb_serial.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/delay_timer/delay_timer.o ${OBJECTDIR}/src/pm_sensor/sercom1_usart.o ${OBJECTDIR}/src/pm_sensor/pm_sensor.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/clock/clock.o.d ${OBJECTDIR}/src/hc12/sercom5_usart.o.d ${OBJECTDIR}/src/hc12/hc12.o.d ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d ${OBJECTDIR}/src/usb_serial/usb_serial.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/delay_timer/delay_timer.o.d ${OBJECTDIR}/src/pm_sensor/sercom1_usart.o.d ${OBJECTDIR}/src/pm_sensor/pm_sensor.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/clock/clock.o ${OBJECTDIR}/src/hc12/sercom5_usart.o ${OBJECTDIR}/src/hc12/hc12.o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o ${OBJECTDIR}/src/usb_serial/usb_serial.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/delay_timer/delay_timer.o ${OBJECTDIR}/src/pm_sensor/sercom1_usart.o ${OBJECTDIR}/src/pm_sensor/pm_sensor.o

# Source Files
SOURCEFILES=src/clock/clock.c src/hc12/sercom5_usart.c src/hc12/hc12.c src/usb_serial/sercom3_usart.c src/usb_serial/usb_serial.c src/main.c src/delay_timer/delay_timer.c src/pm_sensor/sercom1_usart.c src/pm_sensor/pm_sensor.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${CMSIS_DIR}/CMSIS/Core/Include"



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/cansat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32CM5164LS00048
MP_LINKER_FILE_OPTION=
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
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/clock/clock.o: src/clock/clock.c  .generated_files/flags/default/ac5bdab27135bbb7e47dfaa131d11ec0afa1be20 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/clock" 
	@${RM} ${OBJECTDIR}/src/clock/clock.o.d 
	@${RM} ${OBJECTDIR}/src/clock/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/clock/clock.o.d" -o ${OBJECTDIR}/src/clock/clock.o src/clock/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/sercom5_usart.o: src/hc12/sercom5_usart.c  .generated_files/flags/default/f166e1d58765c64e7876231be801af854f729f5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/sercom5_usart.o.d" -o ${OBJECTDIR}/src/hc12/sercom5_usart.o src/hc12/sercom5_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/hc12.o: src/hc12/hc12.c  .generated_files/flags/default/9acbeb19abbf02827d589f0d9f7b6dc2536c7da3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/hc12.o.d" -o ${OBJECTDIR}/src/hc12/hc12.o src/hc12/hc12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/sercom3_usart.o: src/usb_serial/sercom3_usart.c  .generated_files/flags/default/a52d879d3f962b32952777c729df6bf64f642dd6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d" -o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o src/usb_serial/sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/usb_serial.o: src/usb_serial/usb_serial.c  .generated_files/flags/default/48c000e0471bcfe20e332debf1f97da0a0eb91d1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/usb_serial.o.d" -o ${OBJECTDIR}/src/usb_serial/usb_serial.o src/usb_serial/usb_serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/df966ba86e83c041cfa53c555def73e2c4147d2a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/delay_timer/delay_timer.o: src/delay_timer/delay_timer.c  .generated_files/flags/default/8c62ba20122819064f125fc05e326e7b222228ec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/delay_timer" 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o.d 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/delay_timer/delay_timer.o.d" -o ${OBJECTDIR}/src/delay_timer/delay_timer.o src/delay_timer/delay_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pm_sensor/sercom1_usart.o: src/pm_sensor/sercom1_usart.c  .generated_files/flags/default/5aecf8735782b74e5f1476e0aae2f2d9cdf04cfc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pm_sensor" 
	@${RM} ${OBJECTDIR}/src/pm_sensor/sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/src/pm_sensor/sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pm_sensor/sercom1_usart.o.d" -o ${OBJECTDIR}/src/pm_sensor/sercom1_usart.o src/pm_sensor/sercom1_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pm_sensor/pm_sensor.o: src/pm_sensor/pm_sensor.c  .generated_files/flags/default/bd120e7c5173d73113edbc05eb2ae604dfd173e0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pm_sensor" 
	@${RM} ${OBJECTDIR}/src/pm_sensor/pm_sensor.o.d 
	@${RM} ${OBJECTDIR}/src/pm_sensor/pm_sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pm_sensor/pm_sensor.o.d" -o ${OBJECTDIR}/src/pm_sensor/pm_sensor.o src/pm_sensor/pm_sensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/src/clock/clock.o: src/clock/clock.c  .generated_files/flags/default/702c2524233f42a3d913845fb1ce2e763df062ef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/clock" 
	@${RM} ${OBJECTDIR}/src/clock/clock.o.d 
	@${RM} ${OBJECTDIR}/src/clock/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/clock/clock.o.d" -o ${OBJECTDIR}/src/clock/clock.o src/clock/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/sercom5_usart.o: src/hc12/sercom5_usart.c  .generated_files/flags/default/82feb7a95631c0972162d8adb8f93cfcec1ccb1b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/sercom5_usart.o.d" -o ${OBJECTDIR}/src/hc12/sercom5_usart.o src/hc12/sercom5_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/hc12.o: src/hc12/hc12.c  .generated_files/flags/default/d86f57ffef64babe4a9570998796168f43580fbf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/hc12.o.d" -o ${OBJECTDIR}/src/hc12/hc12.o src/hc12/hc12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/sercom3_usart.o: src/usb_serial/sercom3_usart.c  .generated_files/flags/default/132b341436fbcd8da7635df1b5651e41cdcd079 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d" -o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o src/usb_serial/sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/usb_serial.o: src/usb_serial/usb_serial.c  .generated_files/flags/default/f8b702a18e79ae079ec327c963711c7e216f631f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/usb_serial.o.d" -o ${OBJECTDIR}/src/usb_serial/usb_serial.o src/usb_serial/usb_serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/b93ce439023de8bef45e62b5caa7e61a7f49c3de .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/delay_timer/delay_timer.o: src/delay_timer/delay_timer.c  .generated_files/flags/default/418d51faf2ce7fe2e04b742931011bf64ddaa06e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/delay_timer" 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o.d 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/delay_timer/delay_timer.o.d" -o ${OBJECTDIR}/src/delay_timer/delay_timer.o src/delay_timer/delay_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pm_sensor/sercom1_usart.o: src/pm_sensor/sercom1_usart.c  .generated_files/flags/default/ec1baf033d65415f020efbb0286889d6a7fae5c3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pm_sensor" 
	@${RM} ${OBJECTDIR}/src/pm_sensor/sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/src/pm_sensor/sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pm_sensor/sercom1_usart.o.d" -o ${OBJECTDIR}/src/pm_sensor/sercom1_usart.o src/pm_sensor/sercom1_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pm_sensor/pm_sensor.o: src/pm_sensor/pm_sensor.c  .generated_files/flags/default/498571e947418157bba5e76cd756103153ee6c6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pm_sensor" 
	@${RM} ${OBJECTDIR}/src/pm_sensor/pm_sensor.o.d 
	@${RM} ${OBJECTDIR}/src/pm_sensor/pm_sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pm_sensor/pm_sensor.o.d" -o ${OBJECTDIR}/src/pm_sensor/pm_sensor.o src/pm_sensor/pm_sensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/cansat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/cansat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=8000,--defsym=_min_stack_size=8000,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/PIC32CM-LS00"
	
else
${DISTDIR}/cansat.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/cansat.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=8000,--defsym=_min_stack_size=8000,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/PIC32CM-LS00"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/cansat.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
