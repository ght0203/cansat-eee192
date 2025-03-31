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
FINAL_IMAGE=${DISTDIR}/bme_280_spi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/bme_280_spi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=src/bme_280/bme280.c src/bme_280/sercom2_spi.c src/clock/clock.c src/delay_timer/delay_timer.c src/dmac/dmac_transmit.c src/usb_serial/sercom3_usart.c src/usb_serial/usb_serial.c src/main.c src/pms7003/pms7003.c src/pms7003/sercom1_usart.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/bme_280/bme280.o ${OBJECTDIR}/src/bme_280/sercom2_spi.o ${OBJECTDIR}/src/clock/clock.o ${OBJECTDIR}/src/delay_timer/delay_timer.o ${OBJECTDIR}/src/dmac/dmac_transmit.o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o ${OBJECTDIR}/src/usb_serial/usb_serial.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/pms7003/pms7003.o ${OBJECTDIR}/src/pms7003/sercom1_usart.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/bme_280/bme280.o.d ${OBJECTDIR}/src/bme_280/sercom2_spi.o.d ${OBJECTDIR}/src/clock/clock.o.d ${OBJECTDIR}/src/delay_timer/delay_timer.o.d ${OBJECTDIR}/src/dmac/dmac_transmit.o.d ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d ${OBJECTDIR}/src/usb_serial/usb_serial.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/pms7003/pms7003.o.d ${OBJECTDIR}/src/pms7003/sercom1_usart.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/bme_280/bme280.o ${OBJECTDIR}/src/bme_280/sercom2_spi.o ${OBJECTDIR}/src/clock/clock.o ${OBJECTDIR}/src/delay_timer/delay_timer.o ${OBJECTDIR}/src/dmac/dmac_transmit.o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o ${OBJECTDIR}/src/usb_serial/usb_serial.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/pms7003/pms7003.o ${OBJECTDIR}/src/pms7003/sercom1_usart.o

# Source Files
SOURCEFILES=src/bme_280/bme280.c src/bme_280/sercom2_spi.c src/clock/clock.c src/delay_timer/delay_timer.c src/dmac/dmac_transmit.c src/usb_serial/sercom3_usart.c src/usb_serial/usb_serial.c src/main.c src/pms7003/pms7003.c src/pms7003/sercom1_usart.c

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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/bme_280_spi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/src/bme_280/bme280.o: src/bme_280/bme280.c  .generated_files/flags/default/1d0239411e9da43a937c8361867d49966b31bbf1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/bme280.o.d" -o ${OBJECTDIR}/src/bme_280/bme280.o src/bme_280/bme280.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/bme_280/sercom2_spi.o: src/bme_280/sercom2_spi.c  .generated_files/flags/default/fc2cbc07555dc45f05d355feacb47dbf4857c11f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/sercom2_spi.o.d" -o ${OBJECTDIR}/src/bme_280/sercom2_spi.o src/bme_280/sercom2_spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/clock/clock.o: src/clock/clock.c  .generated_files/flags/default/d6ca85c8eedb22b58da72902e8f9ea1d6f879a13 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/clock" 
	@${RM} ${OBJECTDIR}/src/clock/clock.o.d 
	@${RM} ${OBJECTDIR}/src/clock/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/clock/clock.o.d" -o ${OBJECTDIR}/src/clock/clock.o src/clock/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/delay_timer/delay_timer.o: src/delay_timer/delay_timer.c  .generated_files/flags/default/2c7cc57ed9955783b9fa404343d3b40f2dd749f4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/delay_timer" 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o.d 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/delay_timer/delay_timer.o.d" -o ${OBJECTDIR}/src/delay_timer/delay_timer.o src/delay_timer/delay_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/dmac/dmac_transmit.o: src/dmac/dmac_transmit.c  .generated_files/flags/default/812de85096667fc5d80069bf8821bb022b34a154 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/dmac" 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o.d 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/dmac/dmac_transmit.o.d" -o ${OBJECTDIR}/src/dmac/dmac_transmit.o src/dmac/dmac_transmit.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/sercom3_usart.o: src/usb_serial/sercom3_usart.c  .generated_files/flags/default/9d7285898e75f2f018b64e2ae5b7dac72a85fcca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d" -o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o src/usb_serial/sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/usb_serial.o: src/usb_serial/usb_serial.c  .generated_files/flags/default/177ef5c4dd5a601628e8c0b79919019214681d6f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/usb_serial.o.d" -o ${OBJECTDIR}/src/usb_serial/usb_serial.o src/usb_serial/usb_serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/ba429363a8c697dd24a5c8e9b0074a4bc645e8a8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/pms7003.o: src/pms7003/pms7003.c  .generated_files/flags/default/e776bf062f5fca317a70557f61e142ea24adaba9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/pms7003.o.d" -o ${OBJECTDIR}/src/pms7003/pms7003.o src/pms7003/pms7003.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/sercom1_usart.o: src/pms7003/sercom1_usart.c  .generated_files/flags/default/3e17db942e7fb8efd1af56b1f50248b20ac6686 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/sercom1_usart.o.d" -o ${OBJECTDIR}/src/pms7003/sercom1_usart.o src/pms7003/sercom1_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/src/bme_280/bme280.o: src/bme_280/bme280.c  .generated_files/flags/default/510aa2b0a5d2955a2086720a243f89775ec37ca1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/bme280.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/bme280.o.d" -o ${OBJECTDIR}/src/bme_280/bme280.o src/bme_280/bme280.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/bme_280/sercom2_spi.o: src/bme_280/sercom2_spi.c  .generated_files/flags/default/3dda3afcbc84873e355a59db0fbaabe1fd274e8b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/bme_280" 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o.d 
	@${RM} ${OBJECTDIR}/src/bme_280/sercom2_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/bme_280/sercom2_spi.o.d" -o ${OBJECTDIR}/src/bme_280/sercom2_spi.o src/bme_280/sercom2_spi.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/clock/clock.o: src/clock/clock.c  .generated_files/flags/default/9424b7d048bc8732cc503b49f11fcd0a7787102f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/clock" 
	@${RM} ${OBJECTDIR}/src/clock/clock.o.d 
	@${RM} ${OBJECTDIR}/src/clock/clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/clock/clock.o.d" -o ${OBJECTDIR}/src/clock/clock.o src/clock/clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/delay_timer/delay_timer.o: src/delay_timer/delay_timer.c  .generated_files/flags/default/55c6a4fd3daed9aa04fdc28f090ddc31e416fa76 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/delay_timer" 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o.d 
	@${RM} ${OBJECTDIR}/src/delay_timer/delay_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/delay_timer/delay_timer.o.d" -o ${OBJECTDIR}/src/delay_timer/delay_timer.o src/delay_timer/delay_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/dmac/dmac_transmit.o: src/dmac/dmac_transmit.c  .generated_files/flags/default/dad4ddaf7fef1834bef10b4646e71c3b345a9158 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/dmac" 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o.d 
	@${RM} ${OBJECTDIR}/src/dmac/dmac_transmit.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/dmac/dmac_transmit.o.d" -o ${OBJECTDIR}/src/dmac/dmac_transmit.o src/dmac/dmac_transmit.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/sercom3_usart.o: src/usb_serial/sercom3_usart.c  .generated_files/flags/default/d947d6d43a223595df22ed41b42eed0d5908b018 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/sercom3_usart.o.d" -o ${OBJECTDIR}/src/usb_serial/sercom3_usart.o src/usb_serial/sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/usb_serial/usb_serial.o: src/usb_serial/usb_serial.c  .generated_files/flags/default/716b9852bab994b7269d880d0a9851aa277bc8f9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/usb_serial" 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o.d 
	@${RM} ${OBJECTDIR}/src/usb_serial/usb_serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/usb_serial/usb_serial.o.d" -o ${OBJECTDIR}/src/usb_serial/usb_serial.o src/usb_serial/usb_serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/232c0ba777067fe0d2656abdd2f18f489438d161 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/main.o.d" -o ${OBJECTDIR}/src/main.o src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/pms7003.o: src/pms7003/pms7003.c  .generated_files/flags/default/7b3419c125b2c84e61df42fcfb2655a93c730aab .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/pms7003.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/pms7003.o.d" -o ${OBJECTDIR}/src/pms7003/pms7003.o src/pms7003/pms7003.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/src/pms7003/sercom1_usart.o: src/pms7003/sercom1_usart.c  .generated_files/flags/default/94a1a682e67dfab8dc2ce574ea0ef7a3589ead11 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src/pms7003" 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/src/pms7003/sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O0 -fno-common -MP -MMD -MF "${OBJECTDIR}/src/pms7003/sercom1_usart.o.d" -o ${OBJECTDIR}/src/pms7003/sercom1_usart.o src/pms7003/sercom1_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/bme_280_spi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/bme_280_spi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/PIC32CM-LS00"
	
else
${DISTDIR}/bme_280_spi.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/bme_280_spi.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/PIC32CM-LS00"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/bme_280_spi.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
