#
# File:     %M%	SCCS: %I% - %G%
# Author:   Matt Stemen
#
# Created:  12/05/1992
# Edited:   
#
# The use, disclosure, reproduction, modification, transfer, or
# transmittal of this work for any purpose in any form or by any
# means without the written permission of United Parcel Services
# is strictly prohibited.
#
# Confidential, Unpublished Property of United Parcel Services.
# Use and Distribution Limited Solely to Authorized Personnel.
#
# Copyright (c) 1992, United Parcel Service of America, Inc.
# All Rights Reserved.
#
# Purpose:
#    Build phonetool.
#
.KEEP_STATE :

OPENWINHOME:sh = echo ${OPENWINHOME:-/usr/openwin}

.INIT :
	@echo "Copyright (c) 1992 by Roadnet Technologies, Inc."
	@echo "Copyright (c) 1992 by United Parcel Service of America."
	@echo "All rights reserved."
	@echo ""

SCCSGETFLAGS=	-s

LINTS = llib-llibaudio.ln
#CC = gcc
# CC=    /home/dbi0/toolset/licensed/C/acc 
CC= cc
CFLAGS=		-I/usr/openwin/include  -I$(OPENWINHOME)/share/include -I. -DMAIN
LD=		$(CC) -L$(OPENWINHOME)/lib # 
LDLIBS=	-L$(OPENWINHOME)/lib -lxview -lolgx -lX11 -lX -lm 

EXE=        seek

OBJECTS=    seekmain.o seekcreate.o seekxview.o sort.o grade.o

install :=	CFLAGS += -fast
install :=	LDFLAGS += -s

debug   :=	CFLAGS += -g -DDEBUG
debug   :=	LDFLAGS += -g

all debug install : $(EXE)

$(EXE) : $(OBJECTS)
	 $(LD) $(LDFLAGS) -o a.out $(OBJECTS) $(LDLIBS)
	mv a.out $(EXE)

clean :
	rm -f *.o ,* core
	sccs clean

immaculate :
	rm -f *.a $(TASKEXE)
	make clean
