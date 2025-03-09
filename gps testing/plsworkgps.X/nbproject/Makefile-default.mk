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
FINAL_IMAGE=${DISTDIR}/plsworkgps.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/plsworkgps.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../../eee192_GPS/src/config/default/peripheral/nvic/plib_nvic.c ../../../eee192_GPS/src/config/default/peripheral/port/plib_port.c ../../../eee192_GPS/src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c ../../../eee192_GPS/src/config/default/stdio/xc32_monitor.c ../../../eee192_GPS/src/config/default/interrupts.c ../../../eee192_GPS/src/config/default/initialization.c ../../../eee192_GPS/src/config/default/exceptions.c ../../../eee192_GPS/src/config/default/startup_xc32.c ../../../eee192_GPS/src/config/default/libc_syscalls.c ../../../eee192_GPS/src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/144076565/plib_nvic.o ${OBJECTDIR}/_ext/144129716/plib_port.o ${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o ${OBJECTDIR}/_ext/338985975/xc32_monitor.o ${OBJECTDIR}/_ext/2042171279/interrupts.o ${OBJECTDIR}/_ext/2042171279/initialization.o ${OBJECTDIR}/_ext/2042171279/exceptions.o ${OBJECTDIR}/_ext/2042171279/startup_xc32.o ${OBJECTDIR}/_ext/2042171279/libc_syscalls.o ${OBJECTDIR}/_ext/538839980/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/144076565/plib_nvic.o.d ${OBJECTDIR}/_ext/144129716/plib_port.o.d ${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o.d ${OBJECTDIR}/_ext/338985975/xc32_monitor.o.d ${OBJECTDIR}/_ext/2042171279/interrupts.o.d ${OBJECTDIR}/_ext/2042171279/initialization.o.d ${OBJECTDIR}/_ext/2042171279/exceptions.o.d ${OBJECTDIR}/_ext/2042171279/startup_xc32.o.d ${OBJECTDIR}/_ext/2042171279/libc_syscalls.o.d ${OBJECTDIR}/_ext/538839980/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/144076565/plib_nvic.o ${OBJECTDIR}/_ext/144129716/plib_port.o ${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o ${OBJECTDIR}/_ext/338985975/xc32_monitor.o ${OBJECTDIR}/_ext/2042171279/interrupts.o ${OBJECTDIR}/_ext/2042171279/initialization.o ${OBJECTDIR}/_ext/2042171279/exceptions.o ${OBJECTDIR}/_ext/2042171279/startup_xc32.o ${OBJECTDIR}/_ext/2042171279/libc_syscalls.o ${OBJECTDIR}/_ext/538839980/main.o

# Source Files
SOURCEFILES=../../../eee192_GPS/src/config/default/peripheral/nvic/plib_nvic.c ../../../eee192_GPS/src/config/default/peripheral/port/plib_port.c ../../../eee192_GPS/src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c ../../../eee192_GPS/src/config/default/stdio/xc32_monitor.c ../../../eee192_GPS/src/config/default/interrupts.c ../../../eee192_GPS/src/config/default/initialization.c ../../../eee192_GPS/src/config/default/exceptions.c ../../../eee192_GPS/src/config/default/startup_xc32.c ../../../eee192_GPS/src/config/default/libc_syscalls.c ../../../eee192_GPS/src/main.c

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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/plsworkgps.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32CM5164LS00048
MP_LINKER_FILE_OPTION=,--script="..\..\..\eee192_GPS\src\config\default\PIC32CM5164LS00048.ld"
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
${OBJECTDIR}/_ext/144076565/plib_nvic.o: ../../../eee192_GPS/src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/98c9aa02524826fd551b54cfb77d091f599a0748 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/144076565" 
	@${RM} ${OBJECTDIR}/_ext/144076565/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/144076565/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/144076565/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/144076565/plib_nvic.o ../../../eee192_GPS/src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/144129716/plib_port.o: ../../../eee192_GPS/src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/89abe61b4882025454128202afe8154888074a41 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/144129716" 
	@${RM} ${OBJECTDIR}/_ext/144129716/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/144129716/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/144129716/plib_port.o.d" -o ${OBJECTDIR}/_ext/144129716/plib_port.o ../../../eee192_GPS/src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o: ../../../eee192_GPS/src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c  .generated_files/flags/default/56448834df19015f4ba0f97de212f54aa5135bf5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1447701558" 
	@${RM} ${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o.d" -o ${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o ../../../eee192_GPS/src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/338985975/xc32_monitor.o: ../../../eee192_GPS/src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/e2d108df8a04e4b5d54d16d01e79c64c60659a13 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/338985975" 
	@${RM} ${OBJECTDIR}/_ext/338985975/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/338985975/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/338985975/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/338985975/xc32_monitor.o ../../../eee192_GPS/src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2042171279/interrupts.o: ../../../eee192_GPS/src/config/default/interrupts.c  .generated_files/flags/default/9e636b4836fc2c827fa47225b5c9e27441e1107c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2042171279" 
	@${RM} ${OBJECTDIR}/_ext/2042171279/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/2042171279/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2042171279/interrupts.o.d" -o ${OBJECTDIR}/_ext/2042171279/interrupts.o ../../../eee192_GPS/src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2042171279/initialization.o: ../../../eee192_GPS/src/config/default/initialization.c  .generated_files/flags/default/92e80e651a63b421e16978efe43bcde88151640 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2042171279" 
	@${RM} ${OBJECTDIR}/_ext/2042171279/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/2042171279/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2042171279/initialization.o.d" -o ${OBJECTDIR}/_ext/2042171279/initialization.o ../../../eee192_GPS/src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2042171279/exceptions.o: ../../../eee192_GPS/src/config/default/exceptions.c  .generated_files/flags/default/97855973caf2ccd6b4405f75dc2f304263e03072 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2042171279" 
	@${RM} ${OBJECTDIR}/_ext/2042171279/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/2042171279/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2042171279/exceptions.o.d" -o ${OBJECTDIR}/_ext/2042171279/exceptions.o ../../../eee192_GPS/src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2042171279/startup_xc32.o: ../../../eee192_GPS/src/config/default/startup_xc32.c  .generated_files/flags/default/a285a284a2b180d42726ff23352c9c426e9c3626 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2042171279" 
	@${RM} ${OBJECTDIR}/_ext/2042171279/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2042171279/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2042171279/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/2042171279/startup_xc32.o ../../../eee192_GPS/src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2042171279/libc_syscalls.o: ../../../eee192_GPS/src/config/default/libc_syscalls.c  .generated_files/flags/default/9ecd0dc22bcdb23054fc26ba3853fa5c3cd3a956 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2042171279" 
	@${RM} ${OBJECTDIR}/_ext/2042171279/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/2042171279/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2042171279/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/2042171279/libc_syscalls.o ../../../eee192_GPS/src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/538839980/main.o: ../../../eee192_GPS/src/main.c  .generated_files/flags/default/8c276b1093c7dc56ddf99b795c6f3fec68304daf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/538839980" 
	@${RM} ${OBJECTDIR}/_ext/538839980/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/538839980/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/538839980/main.o.d" -o ${OBJECTDIR}/_ext/538839980/main.o ../../../eee192_GPS/src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/144076565/plib_nvic.o: ../../../eee192_GPS/src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/83d87ce4b7f9309583b1f18e99c68bb1fb0494f7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/144076565" 
	@${RM} ${OBJECTDIR}/_ext/144076565/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/144076565/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/144076565/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/144076565/plib_nvic.o ../../../eee192_GPS/src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/144129716/plib_port.o: ../../../eee192_GPS/src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/f024efb5ff6fc9156d9656c61f59da63bf826b0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/144129716" 
	@${RM} ${OBJECTDIR}/_ext/144129716/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/144129716/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/144129716/plib_port.o.d" -o ${OBJECTDIR}/_ext/144129716/plib_port.o ../../../eee192_GPS/src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o: ../../../eee192_GPS/src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c  .generated_files/flags/default/6e5ec780547a96931081302467a7baacba3031d8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1447701558" 
	@${RM} ${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o.d" -o ${OBJECTDIR}/_ext/1447701558/plib_sercom3_usart.o ../../../eee192_GPS/src/config/default/peripheral/sercom/usart/plib_sercom3_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/338985975/xc32_monitor.o: ../../../eee192_GPS/src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/e8d9ae6a05263644404ae0b040b2f5cf49f788a1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/338985975" 
	@${RM} ${OBJECTDIR}/_ext/338985975/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/338985975/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/338985975/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/338985975/xc32_monitor.o ../../../eee192_GPS/src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2042171279/interrupts.o: ../../../eee192_GPS/src/config/default/interrupts.c  .generated_files/flags/default/4fc94e30599244b161d159e36b5549099a4b9591 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2042171279" 
	@${RM} ${OBJECTDIR}/_ext/2042171279/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/2042171279/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2042171279/interrupts.o.d" -o ${OBJECTDIR}/_ext/2042171279/interrupts.o ../../../eee192_GPS/src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2042171279/initialization.o: ../../../eee192_GPS/src/config/default/initialization.c  .generated_files/flags/default/413df0cb1a5d18d5172658adb4bf466a73d21561 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2042171279" 
	@${RM} ${OBJECTDIR}/_ext/2042171279/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/2042171279/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2042171279/initialization.o.d" -o ${OBJECTDIR}/_ext/2042171279/initialization.o ../../../eee192_GPS/src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2042171279/exceptions.o: ../../../eee192_GPS/src/config/default/exceptions.c  .generated_files/flags/default/a72abca85d5088856f8058963d943ea89c7be488 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2042171279" 
	@${RM} ${OBJECTDIR}/_ext/2042171279/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/2042171279/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2042171279/exceptions.o.d" -o ${OBJECTDIR}/_ext/2042171279/exceptions.o ../../../eee192_GPS/src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2042171279/startup_xc32.o: ../../../eee192_GPS/src/config/default/startup_xc32.c  .generated_files/flags/default/79719e05ad50c8ba978d0712624efdeeeecd4ae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2042171279" 
	@${RM} ${OBJECTDIR}/_ext/2042171279/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2042171279/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2042171279/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/2042171279/startup_xc32.o ../../../eee192_GPS/src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/2042171279/libc_syscalls.o: ../../../eee192_GPS/src/config/default/libc_syscalls.c  .generated_files/flags/default/f354b247fc24cfc23b0d3737de8e362a0d48e08 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2042171279" 
	@${RM} ${OBJECTDIR}/_ext/2042171279/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/2042171279/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2042171279/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/2042171279/libc_syscalls.o ../../../eee192_GPS/src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/538839980/main.o: ../../../eee192_GPS/src/main.c  .generated_files/flags/default/4a7234ca38bcac0fb1a0b17ffcb41d7dd1855bdf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/538839980" 
	@${RM} ${OBJECTDIR}/_ext/538839980/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/538839980/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/PIC32CM5164LS00048_DFP" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/538839980/main.o.d" -o ${OBJECTDIR}/_ext/538839980/main.o ../../../eee192_GPS/src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM-LS00" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/plsworkgps.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../../eee192_GPS/src/config/default/PIC32CM5164LS00048.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/plsworkgps.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=512,--gc-sections,-L"./",-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-DAS_SIZE=0x40000,-DBOOTPROT_SIZE=0x0,-DNONSECURE,-DRS_SIZE=0x8000,--memorysummary,${DISTDIR}/memoryfile.xml,-l:plsworkgps_secure_sg_veneer.lib -mdfp="${DFP_DIR}/PIC32CM-LS00"
	
else
${DISTDIR}/plsworkgps.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../../eee192_GPS/src/config/default/PIC32CM5164LS00048.ld ../../../eee192_GPS/plsworkgps.X/..\\..\\eee192_GPS_secure\\plsworkgps_secure.X/dist/default/production/plsworkgps_secure.X.production.hex
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/plsworkgps.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,-L"./",-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",-DAS_SIZE=0x40000,-DBOOTPROT_SIZE=0x0,-DNONSECURE,-DRS_SIZE=0x8000,--memorysummary,${DISTDIR}/memoryfile.xml,-l:plsworkgps_secure_sg_veneer.lib -mdfp="${DFP_DIR}/PIC32CM-LS00"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/plsworkgps.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
	@echo "Creating unified hex file"
	@"C:/Program Files/Microchip/MPLABX/v6.20/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.20/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/plsworkgps.X.${IMAGE_TYPE}.hex ../../../eee192_GPS/plsworkgps.X/..\..\eee192_GPS_secure\plsworkgps_secure.X/dist/default/production/plsworkgps_secure.X.production.hex -odist/${CND_CONF}/production/plsworkgps.X.production.unified.hex

endif


# Subprojects
.build-subprojects:
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
	cd ../../../eee192_GPS/plsworkgps.X/../../eee192_GPS_secure/plsworkgps_secure.X && ${MAKE}  -f Makefile CONF=default TYPE_IMAGE=DEBUG_RUN
else
	cd ../../../eee192_GPS/plsworkgps.X/../../eee192_GPS_secure/plsworkgps_secure.X && ${MAKE}  -f Makefile CONF=default
endif


# Subprojects
.clean-subprojects:
	cd ../../../eee192_GPS/plsworkgps.X/../../eee192_GPS_secure/plsworkgps_secure.X && rm -rf "build/default" "dist/default"

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
