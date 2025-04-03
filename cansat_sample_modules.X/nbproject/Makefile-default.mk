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
FINAL_IMAGE=${DISTDIR}/cansat_sample_modules.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/cansat_sample_modules.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=src/bme_280/bme280.c src/bme_280/sercom2_spi.c src/clock/clock.c src/delay_timer/delay_timer.c src/dmac/dmac_transmit.c src/hc12/hc12.c src/hc12/sercom5_usart.c src/pms7003/pms7003.c src/pms7003/sercom1_usart.c src/usb_serial/sercom3_usart.c src/usb_serial/usb_serial.c src/main.c src/neo6m/neo6m.c src/neo6m/sercom0_usart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/bme_280/bme280.o ${OBJECTDIR}/src/bme_280/sercom2_spi.o ${OBJECTDIR}/src/clock/clock.o ${OBJECTDIR}/src/delay_timer/delay_timer.o ${OBJECTDIR}/src/dmac/dmac_transmit.o ${OBJECTDIR}/src/hc12/hc12.o ${OBJECTDIR}/src/hc12/sercom5_usart.o ${OBJECTDIR}/src/pms7003/pms7003.o ${OBJECTDIR}/src/pms7003/sercom1_usart.o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o ${OBJECTDIR}/src/usb_serial/usb_serial.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/neo6m/neo6m.o ${OBJECTDIR}/src/neo6m/sercom0_usart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/bme_280/bme280.o.d ${OBJECTDIR}/src/bme_280/sercom2_spi.o.d ${OBJECTDIR}/src/clock/clock.o.d ${OBJECTDIR}/src/delay_timer/delay_timer.o.d ${OBJECTDIR}/src/dmac/dmac_transmit.o.d ${OBJECTDIR}/src/hc12/hc12.o.d ${OBJECTDIR}/src/hc12/sercom5_usart.o.d ${OBJECTDIR}/src/pms7003/pms7003.o.d ${OBJECTDIR}/src/pms7003/sercom1_usart.o.d ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d ${OBJECTDIR}/src/usb_serial/usb_serial.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/neo6m/neo6m.o.d ${OBJECTDIR}/src/neo6m/sercom0_usart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/bme_280/bme280.o ${OBJECTDIR}/src/bme_280/sercom2_spi.o ${OBJECTDIR}/src/clock/clock.o ${OBJECTDIR}/src/delay_timer/delay_timer.o ${OBJECTDIR}/src/dmac/dmac_transmit.o ${OBJECTDIR}/src/hc12/hc12.o ${OBJECTDIR}/src/hc12/sercom5_usart.o ${OBJECTDIR}/src/pms7003/pms7003.o ${OBJECTDIR}/src/pms7003/sercom1_usart.o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o ${OBJECTDIR}/src/usb_serial/usb_serial.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/neo6m/neo6m.o ${OBJECTDIR}/src/neo6m/sercom0_usart.o

# Source Files
SOURCEFILES=src/bme_280/bme280.c src/bme_280/sercom2_spi.c src/clock/clock.c src/delay_timer/delay_timer.c src/dmac/dmac_transmit.c src/hc12/hc12.c src/hc12/sercom5_usart.c src/pms7003/pms7003.c src/pms7003/sercom1_usart.c src/usb_serial/sercom3_usart.c src/usb_serial/usb_serial.c src/main.c src/neo6m/neo6m.c src/neo6m/sercom0_usart.c

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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/cansat_sample_modules.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/src/bme_280/bme280.o: src/bme_280/bme280.c  .generated_files/flags/default/77f4dfbf366d26422121d52e30ed8fa4034556fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/bme280.o.d" -o ${OBJECTDIR}/src/bme_280/bme280.o src/bme_280/bme280.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/bme_280/sercom2_spi.o: src/bme_280/sercom2_spi.c  .generated_files/flags/default/8720f83ef0cd7de56a177a16d4ef795aa4746e31 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/sercom2_spi.o.d" -o ${OBJECTDIR}/src/bme_280/sercom2_spi.o src/bme_280/sercom2_spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/clock/clock.o: src/clock/clock.c  .generated_files/flags/default/db7ecdc7c4f8b291492ae16f7f64a795f431cb1f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/clock" 
	@${RM} ${OBJECTDIR}/src/clock/clock.o.d 
	@${RM} ${OBJECTDIR}/src/clock/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/clock/clock.o.d" -o ${OBJECTDIR}/src/clock/clock.o src/clock/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/delay_timer/delay_timer.o: src/delay_timer/delay_timer.c  .generated_files/flags/default/5f80563e787b792085551037ce2fe5447f5fd8e4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/delay_timer" 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o.d 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/delay_timer/delay_timer.o.d" -o ${OBJECTDIR}/src/delay_timer/delay_timer.o src/delay_timer/delay_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/dmac/dmac_transmit.o: src/dmac/dmac_transmit.c  .generated_files/flags/default/69134848fcb9880122f7cbcb1e268f2f79caa256 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/dmac" 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o.d 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/dmac/dmac_transmit.o.d" -o ${OBJECTDIR}/src/dmac/dmac_transmit.o src/dmac/dmac_transmit.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/hc12.o: src/hc12/hc12.c  .generated_files/flags/default/5efe6c5556cb6dfa2bb0ee94f94fd3a85a2ee12c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/hc12.o.d" -o ${OBJECTDIR}/src/hc12/hc12.o src/hc12/hc12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/sercom5_usart.o: src/hc12/sercom5_usart.c  .generated_files/flags/default/c6f0141ddd84fe761c3617767a7fa17eb01e706a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/sercom5_usart.o.d" -o ${OBJECTDIR}/src/hc12/sercom5_usart.o src/hc12/sercom5_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/pms7003.o: src/pms7003/pms7003.c  .generated_files/flags/default/44ddc1a587abaa7ca60bada758023321532cb602 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/pms7003.o.d" -o ${OBJECTDIR}/src/pms7003/pms7003.o src/pms7003/pms7003.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/sercom1_usart.o: src/pms7003/sercom1_usart.c  .generated_files/flags/default/5784dbdbe46778f04483b5576b61e62045391ee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/sercom1_usart.o.d" -o ${OBJECTDIR}/src/pms7003/sercom1_usart.o src/pms7003/sercom1_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/sercom3_usart.o: src/usb_serial/sercom3_usart.c  .generated_files/flags/default/4135cc4e6bff2cce85135e5dbe179d3506f7f9e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d" -o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o src/usb_serial/sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/usb_serial.o: src/usb_serial/usb_serial.c  .generated_files/flags/default/aed820fc3f390164f4ed804ed2f4360bc9eccd6e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/usb_serial.o.d" -o ${OBJECTDIR}/src/usb_serial/usb_serial.o src/usb_serial/usb_serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/33f813021fec7368300e6e2a53f9704c8f0baf75 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/neo6m/neo6m.o: src/neo6m/neo6m.c  .generated_files/flags/default/b3f7956d890238c8232bf4ec0a46cd7f7a62bd94 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/neo6m" 
	@${RM} ${OBJECTDIR}/src/neo6m/neo6m.o.d 
	@${RM} ${OBJECTDIR}/src/neo6m/neo6m.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/neo6m/neo6m.o.d" -o ${OBJECTDIR}/src/neo6m/neo6m.o src/neo6m/neo6m.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/neo6m/sercom0_usart.o: src/neo6m/sercom0_usart.c  .generated_files/flags/default/ff11a886ae8474a570401d3416dd78914744f797 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/neo6m" 
	@${RM} ${OBJECTDIR}/src/neo6m/sercom0_usart.o.d 
	@${RM} ${OBJECTDIR}/src/neo6m/sercom0_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/neo6m/sercom0_usart.o.d" -o ${OBJECTDIR}/src/neo6m/sercom0_usart.o src/neo6m/sercom0_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/src/bme_280/bme280.o: src/bme_280/bme280.c  .generated_files/flags/default/2cdfb181b520b560e772f004988e17a87aba2359 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/bme280.o.d" -o ${OBJECTDIR}/src/bme_280/bme280.o src/bme_280/bme280.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/bme_280/sercom2_spi.o: src/bme_280/sercom2_spi.c  .generated_files/flags/default/915c64199d6aa1a719c157566ecde5d9df7fa72 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/sercom2_spi.o.d" -o ${OBJECTDIR}/src/bme_280/sercom2_spi.o src/bme_280/sercom2_spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/clock/clock.o: src/clock/clock.c  .generated_files/flags/default/7ea28c15301c94319141289cdb12b57a1567f115 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/clock" 
	@${RM} ${OBJECTDIR}/src/clock/clock.o.d 
	@${RM} ${OBJECTDIR}/src/clock/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/clock/clock.o.d" -o ${OBJECTDIR}/src/clock/clock.o src/clock/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/delay_timer/delay_timer.o: src/delay_timer/delay_timer.c  .generated_files/flags/default/3db52337a18292c39520be6e1543bf62f671af39 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/delay_timer" 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o.d 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/delay_timer/delay_timer.o.d" -o ${OBJECTDIR}/src/delay_timer/delay_timer.o src/delay_timer/delay_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/dmac/dmac_transmit.o: src/dmac/dmac_transmit.c  .generated_files/flags/default/ae5d21990c5dfffc50302496747d801b7674501 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/dmac" 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o.d 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/dmac/dmac_transmit.o.d" -o ${OBJECTDIR}/src/dmac/dmac_transmit.o src/dmac/dmac_transmit.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/hc12.o: src/hc12/hc12.c  .generated_files/flags/default/f476604121ac7fcaa67849e2fe1e17f0c74f39ce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/hc12.o.d" -o ${OBJECTDIR}/src/hc12/hc12.o src/hc12/hc12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/sercom5_usart.o: src/hc12/sercom5_usart.c  .generated_files/flags/default/7a5ff4d26af7aab3546b66958350181cc2ff196c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/sercom5_usart.o.d" -o ${OBJECTDIR}/src/hc12/sercom5_usart.o src/hc12/sercom5_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/pms7003.o: src/pms7003/pms7003.c  .generated_files/flags/default/2220b362a904b084615fc04c3b399103e9497a0b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/pms7003.o.d" -o ${OBJECTDIR}/src/pms7003/pms7003.o src/pms7003/pms7003.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/sercom1_usart.o: src/pms7003/sercom1_usart.c  .generated_files/flags/default/af63b88f40c2626a5664664c49662f5fff78c6f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/sercom1_usart.o.d" -o ${OBJECTDIR}/src/pms7003/sercom1_usart.o src/pms7003/sercom1_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/sercom3_usart.o: src/usb_serial/sercom3_usart.c  .generated_files/flags/default/fcb2ba1e247b8e24987ad116c61d45beeb6e7774 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d" -o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o src/usb_serial/sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/usb_serial.o: src/usb_serial/usb_serial.c  .generated_files/flags/default/cb5370b94892d68cb5512554067873557fa9e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/usb_serial.o.d" -o ${OBJECTDIR}/src/usb_serial/usb_serial.o src/usb_serial/usb_serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/8446a8748a8ab59fbb83caa2eeb3be6a68eac2a9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/neo6m/neo6m.o: src/neo6m/neo6m.c  .generated_files/flags/default/47d0308c8f65ff44498aef5c245fda4b3ecf2b69 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/neo6m" 
	@${RM} ${OBJECTDIR}/src/neo6m/neo6m.o.d 
	@${RM} ${OBJECTDIR}/src/neo6m/neo6m.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/neo6m/neo6m.o.d" -o ${OBJECTDIR}/src/neo6m/neo6m.o src/neo6m/neo6m.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/neo6m/sercom0_usart.o: src/neo6m/sercom0_usart.c  .generated_files/flags/default/208d2dd43af30fb5b31d79c89e5b562b26702391 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/neo6m" 
	@${RM} ${OBJECTDIR}/src/neo6m/sercom0_usart.o.d 
	@${RM} ${OBJECTDIR}/src/neo6m/sercom0_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/neo6m/sercom0_usart.o.d" -o ${OBJECTDIR}/src/neo6m/sercom0_usart.o src/neo6m/sercom0_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/cansat_sample_modules.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/cansat_sample_modules.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/PIC32CM-LS00"
	
else
${DISTDIR}/cansat_sample_modules.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/cansat_sample_modules.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/PIC32CM-LS00"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/cansat_sample_modules.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
