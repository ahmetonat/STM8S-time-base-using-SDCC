
#********************************************************************
# * Copyright 2018 Ahmet Onat
# * This program is distributed under the terms of the 
# * GNU General Public License
# *
# * This file is part of SDCC_TIM1_Tbase
# *
# * SDCC_TIM1_Tbase free software: you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation, either version 3 of the License, or
# * (at your option) any later version.
# *
# * SDCC_TIM1_Tbase is distributed in the hope that it will be useful,
# * but WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
# * You should have received a copy of the GNU General Public License
# * along with SDCC_StmPeriphLib.  If not, see <http://www.gnu.org/licenses/>.
# *
# *********************************************************************

#This is the name of the main file, and output ihx:
OBJECT=main
HEXFILE=$(OBJECT).ihx
SRCFILE=$(OBJECT).c

#The library built specifically for this project is defined:
LIBFILE=projectlib.lib
LIBFILEPATH= ./libs


SDCC=sdcc
SDLD=sdld
PROCESSOR=stm8s103f3
DEBUGPROBE=stlinkv2

# Define tool path. Adjust to your setup:
LIBROOT=/home/onat/elektronik/ARM/stm8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver
INCLUDES=$(LIBROOT)/inc/
DRIVERS=$(LIBROOT)/src/

vpath %.c
vpath %.c $(DRIVERS)

# Where source/header files will be searched in:
CFLAGS= -I$(INCLUDES)
CFLAGS+= -I.
CFLAGS+= -Ilibs

#The macros are to keep the header files (which want to see a specific compiler and processor) happy.
MACROS= -D__CSMC__ -DSTM8S103
PROCTYPE= -lstm8 -mstm8
OUTPUTTYPE=--out-fmt-ihx

#.PHONY: all clean flash

#all: $(HEXFILE)
$(HEXFILE): $(LIBFILEPATH)/$(LIBFILE) $(SRCFILE)

clean:
	rm -f $(OBJECT).cdb $(OBJECT).map $(OBJECT).lk $(OBJECT).rst $(OBJECT).rel $(OBJECT).sym $(OBJECT).lst $(OBJECT).asm
	make clean -C $(LIBFILEPATH)

flash: $(HEXFILE)
	stm8flash -c$(DEBUGPROBE) -p$(PROCESSOR) -w $(HEXFILE)

%.ihx: %.c
	$(SDCC) $(MACROS) $(PROCTYPE) $(CFLAGS) $(LDFLAGS) $< $(LIBFILE) -L $(LIBFILEPATH)

# SDCC allows compilation of only 1 source file at a time.
# However, it allows linking in previously generated library files.
# The required library for this project is prepared from the standard
#  libraries by the Makefile in the $(LIBFILEPATH) directory.
# If it has not yet been compiled, call the Makefile in the libs directory also:
$(LIBFILEPATH)/$(LIBFILE):
	make -C $(LIBFILEPATH)
