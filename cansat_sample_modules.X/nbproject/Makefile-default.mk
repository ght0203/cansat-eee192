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
SOURCEFILES_QUOTED_IF_SPACED=src/bme_280/bme280.c src/bme_280/sercom2_spi.c src/clock/clock.c src/delay_timer/delay_timer.c src/dmac/dmac_transmit.c src/hc12/hc12.c src/hc12/sercom5_usart.c src/neo6m/neo6m.c src/neo6m/sercom0_usart.c src/pms7003/pms7003.c src/pms7003/sercom1_usart.c src/usb_serial/sercom3_usart.c src/usb_serial/usb_serial.c src/main.c src/scd41/scd41.c src/scd41/sercom4_i2c_master.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/bme_280/bme280.o ${OBJECTDIR}/src/bme_280/sercom2_spi.o ${OBJECTDIR}/src/clock/clock.o ${OBJECTDIR}/src/delay_timer/delay_timer.o ${OBJECTDIR}/src/dmac/dmac_transmit.o ${OBJECTDIR}/src/hc12/hc12.o ${OBJECTDIR}/src/hc12/sercom5_usart.o ${OBJECTDIR}/src/neo6m/neo6m.o ${OBJECTDIR}/src/neo6m/sercom0_usart.o ${OBJECTDIR}/src/pms7003/pms7003.o ${OBJECTDIR}/src/pms7003/sercom1_usart.o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o ${OBJECTDIR}/src/usb_serial/usb_serial.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/scd41/scd41.o ${OBJECTDIR}/src/scd41/sercom4_i2c_master.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/bme_280/bme280.o.d ${OBJECTDIR}/src/bme_280/sercom2_spi.o.d ${OBJECTDIR}/src/clock/clock.o.d ${OBJECTDIR}/src/delay_timer/delay_timer.o.d ${OBJECTDIR}/src/dmac/dmac_transmit.o.d ${OBJECTDIR}/src/hc12/hc12.o.d ${OBJECTDIR}/src/hc12/sercom5_usart.o.d ${OBJECTDIR}/src/neo6m/neo6m.o.d ${OBJECTDIR}/src/neo6m/sercom0_usart.o.d ${OBJECTDIR}/src/pms7003/pms7003.o.d ${OBJECTDIR}/src/pms7003/sercom1_usart.o.d ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d ${OBJECTDIR}/src/usb_serial/usb_serial.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/scd41/scd41.o.d ${OBJECTDIR}/src/scd41/sercom4_i2c_master.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/bme_280/bme280.o ${OBJECTDIR}/src/bme_280/sercom2_spi.o ${OBJECTDIR}/src/clock/clock.o ${OBJECTDIR}/src/delay_timer/delay_timer.o ${OBJECTDIR}/src/dmac/dmac_transmit.o ${OBJECTDIR}/src/hc12/hc12.o ${OBJECTDIR}/src/hc12/sercom5_usart.o ${OBJECTDIR}/src/neo6m/neo6m.o ${OBJECTDIR}/src/neo6m/sercom0_usart.o ${OBJECTDIR}/src/pms7003/pms7003.o ${OBJECTDIR}/src/pms7003/sercom1_usart.o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o ${OBJECTDIR}/src/usb_serial/usb_serial.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/scd41/scd41.o ${OBJECTDIR}/src/scd41/sercom4_i2c_master.o

# Source Files
SOURCEFILES=src/bme_280/bme280.c src/bme_280/sercom2_spi.c src/clock/clock.c src/delay_timer/delay_timer.c src/dmac/dmac_transmit.c src/hc12/hc12.c src/hc12/sercom5_usart.c src/neo6m/neo6m.c src/neo6m/sercom0_usart.c src/pms7003/pms7003.c src/pms7003/sercom1_usart.c src/usb_serial/sercom3_usart.c src/usb_serial/usb_serial.c src/main.c src/scd41/scd41.c src/scd41/sercom4_i2c_master.c

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
${OBJECTDIR}/src/bme_280/bme280.o: src/bme_280/bme280.c  .generated_files/flags/default/1d1b37a871b874b7c9dbeecd48f77b18b0d1b5f9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/bme280.o.d" -o ${OBJECTDIR}/src/bme_280/bme280.o src/bme_280/bme280.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/bme_280/sercom2_spi.o: src/bme_280/sercom2_spi.c  .generated_files/flags/default/46e3bb5fe556853b4c1c67b2e0be3e28eb5663a2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/sercom2_spi.o.d" -o ${OBJECTDIR}/src/bme_280/sercom2_spi.o src/bme_280/sercom2_spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/clock/clock.o: src/clock/clock.c  .generated_files/flags/default/e35c7f65439d112d33071202f4c6b6a7c53a9e04 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/clock" 
	@${RM} ${OBJECTDIR}/src/clock/clock.o.d 
	@${RM} ${OBJECTDIR}/src/clock/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/clock/clock.o.d" -o ${OBJECTDIR}/src/clock/clock.o src/clock/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/delay_timer/delay_timer.o: src/delay_timer/delay_timer.c  .generated_files/flags/default/17f82cf2aa6df8dd9f824388fda44ee8ba06d47c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/delay_timer" 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o.d 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/delay_timer/delay_timer.o.d" -o ${OBJECTDIR}/src/delay_timer/delay_timer.o src/delay_timer/delay_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/dmac/dmac_transmit.o: src/dmac/dmac_transmit.c  .generated_files/flags/default/70b9c7df3d728ca8e9c9435bd38d75cbd9d00129 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/dmac" 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o.d 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/dmac/dmac_transmit.o.d" -o ${OBJECTDIR}/src/dmac/dmac_transmit.o src/dmac/dmac_transmit.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/hc12.o: src/hc12/hc12.c  .generated_files/flags/default/65b05751955c750ad49cc797ef676df8a1e8ce40 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/hc12.o.d" -o ${OBJECTDIR}/src/hc12/hc12.o src/hc12/hc12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/sercom5_usart.o: src/hc12/sercom5_usart.c  .generated_files/flags/default/2afe8893ae2757181a5d2deae20195b4f0c2031e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/sercom5_usart.o.d" -o ${OBJECTDIR}/src/hc12/sercom5_usart.o src/hc12/sercom5_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/neo6m/neo6m.o: src/neo6m/neo6m.c  .generated_files/flags/default/689d1a4119b5c1928d6d5821035b4bead045b7ef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/neo6m" 
	@${RM} ${OBJECTDIR}/src/neo6m/neo6m.o.d 
	@${RM} ${OBJECTDIR}/src/neo6m/neo6m.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/neo6m/neo6m.o.d" -o ${OBJECTDIR}/src/neo6m/neo6m.o src/neo6m/neo6m.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/neo6m/sercom0_usart.o: src/neo6m/sercom0_usart.c  .generated_files/flags/default/2bc886ba14d4073274454e1d12e5f3da344e0640 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/neo6m" 
	@${RM} ${OBJECTDIR}/src/neo6m/sercom0_usart.o.d 
	@${RM} ${OBJECTDIR}/src/neo6m/sercom0_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/neo6m/sercom0_usart.o.d" -o ${OBJECTDIR}/src/neo6m/sercom0_usart.o src/neo6m/sercom0_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/pms7003.o: src/pms7003/pms7003.c  .generated_files/flags/default/3a735abc62a1c47f260cf007775d845c8c4d9dc8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/pms7003.o.d" -o ${OBJECTDIR}/src/pms7003/pms7003.o src/pms7003/pms7003.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/sercom1_usart.o: src/pms7003/sercom1_usart.c  .generated_files/flags/default/a9f13e8571f7b908ff92c3a8c14c58ce78ebea86 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/sercom1_usart.o.d" -o ${OBJECTDIR}/src/pms7003/sercom1_usart.o src/pms7003/sercom1_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/sercom3_usart.o: src/usb_serial/sercom3_usart.c  .generated_files/flags/default/93badeb10450150445d3f5709268b950be041916 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d" -o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o src/usb_serial/sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/usb_serial.o: src/usb_serial/usb_serial.c  .generated_files/flags/default/f9e5598d8064f0482a9023b924d6f184f3e25f81 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/usb_serial.o.d" -o ${OBJECTDIR}/src/usb_serial/usb_serial.o src/usb_serial/usb_serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/4fcbc6b9e66f3884d7158ae4e2508c74dd144df8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/scd41/scd41.o: src/scd41/scd41.c  .generated_files/flags/default/b415672e2e609ced0dc117dcc64ec143b4be6e44 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/scd41" 
	@${RM} ${OBJECTDIR}/src/scd41/scd41.o.d 
	@${RM} ${OBJECTDIR}/src/scd41/scd41.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/scd41/scd41.o.d" -o ${OBJECTDIR}/src/scd41/scd41.o src/scd41/scd41.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/scd41/sercom4_i2c_master.o: src/scd41/sercom4_i2c_master.c  .generated_files/flags/default/28abae387e20566c350ade42fc91c34caac64146 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/scd41" 
	@${RM} ${OBJECTDIR}/src/scd41/sercom4_i2c_master.o.d 
	@${RM} ${OBJECTDIR}/src/scd41/sercom4_i2c_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/scd41/sercom4_i2c_master.o.d" -o ${OBJECTDIR}/src/scd41/sercom4_i2c_master.o src/scd41/sercom4_i2c_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/src/bme_280/bme280.o: src/bme_280/bme280.c  .generated_files/flags/default/4405828658d441ef2e2bc7984e01b4f8a24ed2fa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/bme280.o.d" -o ${OBJECTDIR}/src/bme_280/bme280.o src/bme_280/bme280.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/bme_280/sercom2_spi.o: src/bme_280/sercom2_spi.c  .generated_files/flags/default/b8de69ad18ab1d73796f7625cd84dc7f8e72f301 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/sercom2_spi.o.d" -o ${OBJECTDIR}/src/bme_280/sercom2_spi.o src/bme_280/sercom2_spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/clock/clock.o: src/clock/clock.c  .generated_files/flags/default/7bb7b4cb0018d46c40b69f65512b1ac12cf1a60a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/clock" 
	@${RM} ${OBJECTDIR}/src/clock/clock.o.d 
	@${RM} ${OBJECTDIR}/src/clock/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/clock/clock.o.d" -o ${OBJECTDIR}/src/clock/clock.o src/clock/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/delay_timer/delay_timer.o: src/delay_timer/delay_timer.c  .generated_files/flags/default/9f7d14ccc7154fb98bfef4332144e580f1e37ecd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/delay_timer" 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o.d 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/delay_timer/delay_timer.o.d" -o ${OBJECTDIR}/src/delay_timer/delay_timer.o src/delay_timer/delay_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/dmac/dmac_transmit.o: src/dmac/dmac_transmit.c  .generated_files/flags/default/754835eb183b0b40c5630096137040356b6cfef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/dmac" 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o.d 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/dmac/dmac_transmit.o.d" -o ${OBJECTDIR}/src/dmac/dmac_transmit.o src/dmac/dmac_transmit.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/hc12.o: src/hc12/hc12.c  .generated_files/flags/default/d5a9bc21dcf15d738da7fa17ff3e5645f07e3d83 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/hc12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/hc12.o.d" -o ${OBJECTDIR}/src/hc12/hc12.o src/hc12/hc12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/hc12/sercom5_usart.o: src/hc12/sercom5_usart.c  .generated_files/flags/default/9d8b07bfdd8d2cf19c3f7910c6bc66216eec0cc0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/hc12" 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o.d 
	@${RM} ${OBJECTDIR}/src/hc12/sercom5_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/hc12/sercom5_usart.o.d" -o ${OBJECTDIR}/src/hc12/sercom5_usart.o src/hc12/sercom5_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/neo6m/neo6m.o: src/neo6m/neo6m.c  .generated_files/flags/default/8a1a0cedadbafdcce6cb041c3fe264d32c381f00 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/neo6m" 
	@${RM} ${OBJECTDIR}/src/neo6m/neo6m.o.d 
	@${RM} ${OBJECTDIR}/src/neo6m/neo6m.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/neo6m/neo6m.o.d" -o ${OBJECTDIR}/src/neo6m/neo6m.o src/neo6m/neo6m.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/neo6m/sercom0_usart.o: src/neo6m/sercom0_usart.c  .generated_files/flags/default/fdd08affc2ecba244f56c4db4a547159cd65337a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/neo6m" 
	@${RM} ${OBJECTDIR}/src/neo6m/sercom0_usart.o.d 
	@${RM} ${OBJECTDIR}/src/neo6m/sercom0_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/neo6m/sercom0_usart.o.d" -o ${OBJECTDIR}/src/neo6m/sercom0_usart.o src/neo6m/sercom0_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/pms7003.o: src/pms7003/pms7003.c  .generated_files/flags/default/2a6175383f528446ff5a114f84c27bcf6fe4ee23 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/pms7003.o.d" -o ${OBJECTDIR}/src/pms7003/pms7003.o src/pms7003/pms7003.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/sercom1_usart.o: src/pms7003/sercom1_usart.c  .generated_files/flags/default/3e7f6e5a65f73a468c3e032199d99a81f56c0f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/sercom1_usart.o.d" -o ${OBJECTDIR}/src/pms7003/sercom1_usart.o src/pms7003/sercom1_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/sercom3_usart.o: src/usb_serial/sercom3_usart.c  .generated_files/flags/default/35640c46583488edfcfc6bfebe3b61e9e26dbfb8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d" -o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o src/usb_serial/sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/usb_serial.o: src/usb_serial/usb_serial.c  .generated_files/flags/default/328f49a7a0caa92a305d2a0028fe048a4312df88 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/usb_serial.o.d" -o ${OBJECTDIR}/src/usb_serial/usb_serial.o src/usb_serial/usb_serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/cfd397f6eb12ba50928cd01559d9584b5c3a8620 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/scd41/scd41.o: src/scd41/scd41.c  .generated_files/flags/default/bee71b880b377cf1ea534d34048827dd82391bbc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/scd41" 
	@${RM} ${OBJECTDIR}/src/scd41/scd41.o.d 
	@${RM} ${OBJECTDIR}/src/scd41/scd41.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/scd41/scd41.o.d" -o ${OBJECTDIR}/src/scd41/scd41.o src/scd41/scd41.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/scd41/sercom4_i2c_master.o: src/scd41/sercom4_i2c_master.c  .generated_files/flags/default/8b6cfd90def9d21f2e19087d841b1e849fa87a82 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/scd41" 
	@${RM} ${OBJECTDIR}/src/scd41/sercom4_i2c_master.o.d 
	@${RM} ${OBJECTDIR}/src/scd41/sercom4_i2c_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -MP -MMD -MF "${OBJECTDIR}/src/scd41/sercom4_i2c_master.o.d" -o ${OBJECTDIR}/src/scd41/sercom4_i2c_master.o src/scd41/sercom4_i2c_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
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
