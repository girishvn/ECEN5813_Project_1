#
# @file conversion.c
# @brief Additional make file used by Makefile with src information
#
# This make file contains a list of the additional source files needed depending on the patform
#
# @author Girish Narayanswamy
# @date February 3 2018
# @version 1.0
#
#

SOURCES = main.c \
	circbuf.c \
	conversion.c \
	data.c \
	debug.c \
	project2.c \
	memory.c \

ifeq ($(PLATFORM),KL25Z)
SOURCES += arch_arm32.c \
	GPIO.c \
	system_MKL25Z4.c \
	startup_MKL25Z4.S \
	uart.c
endif

ifeq ($(PLATFORM),HOST)
UNITTESTSOURCES = unit_tests.c \
	memory.c \
	circbuf.c \
	conversion.c
endif
