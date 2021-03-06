#
# @file Makefile
# @brief Makefile to build project1
#
# @author Girish Narayanswamy
# @date February 3 2018
# @version 1.0
#
# Usage:
#
# $ make
# Builds project for HOST (linux) platform
# Generates all .o .d .map .elf files
#
# $ make build PLATFORM=<HOST,BBB,KL25Z>
# Builds project for HOST, BBB, or KL25Z platform
# Generates all .o .d .map .elf files
#
# $ make compile-all PLATFORM=<HOST,BBB,KL25Z>
# Compiles project source code for HOST, BBB, or KL25Z platform
# Generates all .o .d files
#
# make unit_tests PLATFORM=HOST
# makes unit_test.elf file to run all unit tests for
# memory conversion and circbuf implementations
#
# $ make clean
# Removes all generate files
# Removes all .o .d .asm .i .elf .asm files
#
# $ make %.i
# Generates preprocessed output of a c-implementation file
# Generates .i files
#
# $ make %.asm
# Generates assembly output of a c-implementation file
# Generates .i files
#
# $ make %.o
# Generates object output of a c-implementation file
# Generates .o files
#

#Additional makefile with a list of all source code files
include sources.mk

#data processing file
TARGET = project3
GENFLAGS = -Wall -Werror -g -O3 -std=c99

#Various platforms to build for: KL25Z, BBB, HOST (default)
#For KL25Z mcu
ifeq ($(PLATFORM),KL25Z)

#Architecture Specific Flags
CPU = cortex-m0plus
ARCH = armv6-m
FPABI = soft
ARCHFLAGS = -mcpu=$(CPU) -mthumb -march=$(ARCH) -mfloat-abi=$(FPABI) -mfpu=fpv4-sp-d16 --specs=nosys.specs

LINKERFILE = ../platform/MKL25Z128xxx4_flash.ld

TARGETUSE = -DKL25ZUSE
CMNDLNBLD = -DKL25ZCMNDLNBLD
COMPILER = arm-none-eabi-gcc
INCLUDES = -I../include/CMSIS -I../include/kl25z -I../platform
LDFLAGS = -T$(LINKERFILE)

#For Beagle Bone Black
else ifeq ($(PLATFORM),BBB)

TARGETUSE = -DBBBUSE
CMNDLNBLD = -DBBBCMNDLNBLD
VERBOSEOUT = -DVERBOSE
COMPILER = arm-linux-gnueabi-gcc
INCLUDES = -I../include/CMSIS
LDFLAGS = -static

STACKUSAGE = -fstack-usage

#For host platform (linux computer), default case
else

#Platform Specific Flags
TARGETUSE = -DHOSTUSE
CMNDLNBLD = -DHOSTCMNDLNBLD
VERBOSEOUT = -DVERBOSE
COMPILER = gcc
#INCLUDES = -I../include/CMSIS -I../include/kl25z -I../platform

endif

#Compile Defines
INCLUDES +=-I../include/common
CC = $(COMPILER)
CFLAGS = $(INCLUDES) $(GENFLAGS) $(ARCHFLAGS) $(STACKUSAGE)
CPPFLAGS = -DPROJECT3 $(VERBOSEOUT) $(TARGETUSE) $(CMNDLNBLD) $(INCLUDES)
LDFLAGS += -Wl,-Map=$(TARGET).map

#Generate object variable from implementation .c and .S files
OBJS := $(SOURCES:.c=.o)
OBJS := $(OBJS:.S=.o)

#Generate object variables from implementation .c for unit tested files
UTOBJS := $(UNITTESTSOURCES:.c=.o)

.PHONY: HEXbuild
HEXbuild: $(TARGET).elf
	objcopy -O ihex $(TARGET).elf $(TARGET).hex

.PHONY: build
build: $(TARGET).elf
	size $(TARGET).elf $(OBJS)

.PHONY: compile-all
compile-all: $(OBJS)

.PHONY: unittests
unit_tests: $(UTOBJS)
	$(CC) $(UTOBJS) $(CFLAGS) -lcmocka -o $@.elf

$(TARGET).elf: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

%.i : %.c
	$(CC) $(CPPFLAGS) -E $< -o $@

%.asm : %.c
	$(CC) $(CFLAGS) -S $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -M $< -o $*.d

%.o : %.S
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o *.i *.elf *.asm *.map *.d *.hex *.su
