
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

# This Makefile builds the companion files into a library called projectlib.
# The library is then linked with the main file.
# This is the only way to have multiple files in a project in sdcc.

# This Makefile is automatically called from he Makefile of the parent directory

#Name of this library:
LIBNAME=projectlib
LIBRARY=$(LIBNAME).lib


#Which files need to be used for this library:
# First two are from the ST library:
SOURCES=stm8s_gpio.c
SOURCES+=stm8s_tim1.c
SOURCES+=stm8s_clk.c
SOURCES+= tim1_tbase.c

RELS=$(SOURCES:.c=.rel)

SDCC=sdcc
SDLD=sdld
SDAR=sdar

PROCESSOR=stm8s103f3
DEBUGPROBE=stlinkv2

# Define tool path. Adjust to your setup:
LIBROOT=/home/onat/elektronik/ARM/stm8/STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver

INCLUDES=$(LIBROOT)/inc/
SOURCEDIR=$(LIBROOT)/src/

# Where source/header files will be searched in:
CFLAGSLIB= -I$(INCLUDES)
CFLAGSLIB+= -I.
CFLAGSLIB+= -I..
CFLAGSLIB+= -c

SDARFLAGS= -rc

# The macros are to keep the header files (which want to see a specific compiler and processor) happy.
MACROS= -D__CSMC__ -DSTM8S103
PROCTYPE= -lstm8 -mstm8

vpath %.c
vpath %.c $(SOURCEDIR)


all: $(LIBRARY)

$(LIBRARY) : $(SOURCES) # $(HEADERS)


%.lib : $(RELS)  
	$(SDAR) $(SDARFLAGS) $@ $(RELS)

%.rel: %.c
	$(SDCC) $(MACROS) $(PROCTYPE) $(CFLAGSLIB) $(LDFLAGS) $<

clean:
	rm -f $(RELS) $(RELS:.rel=.cdb) $(RELS:.rel=.map) $(RELS:.rel=.lst) $(RELS:.rel=.asm) $(RELS:.rel=.lk) $(RELS:.rel=.rst) $(RELS:.rel=.sym)

