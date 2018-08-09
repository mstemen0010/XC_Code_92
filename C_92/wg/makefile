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

.INIT :
	@echo "Copyright (c) 1992 by Roadnet Technologies, Inc."
	@echo "Copyright (c) 1992 by United Parcel Service of America."
	@echo "All rights reserved."
	@echo ""

SCCSGETFLAGS=	-s

OPENWINHOME=    /usr/openwin/

CC=		cc 
CFLAGS=		-I/usr/openwin/include -L/opt/SUNWspro/SC4.0/lib -L/usr/openwin/lib
LD=		$(CC) -L$(OPENWINHOME)/lib
LDLIBS=		-lxview -lolgx -ltt -lX




EXE=		wg

OBJECTS=    wgmain.o wgcreateall.o wgxview.o soundex.o genfunct.o

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
