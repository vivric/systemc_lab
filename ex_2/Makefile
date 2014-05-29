
MODULE_1 = sim_1

SRCS_1 = prod_1.cpp fifo_1.cpp consum_1.cpp main_1.cpp
OBJS_1 = $(SRCS_1:.cpp=.o)

TARGET_ARCH = linux64


SHELL  = /bin/sh

CC     = g++
OPT    = -O3
DEBUG  = -g
OTHER  = -Wno-deprecated
#CFLAGS = $(OPT) $(OTHER)
CFLAGS = $(DEBUG) $(OTHER)


INCDIR = -I. -I.. -I$(SYSTEMC)/include

LIBDIR = -L. -L.. -L$(SYSTEMC)/lib-$(TARGET_ARCH)

LIBS   = $(SYSTEMC)/lib-$(TARGET_ARCH)/libsystemc.a -lm -lpthread $(EXTRA_LIBS)


EXE_1    = $(MODULE_1).x

.SUFFIXES: .cc .cpp .o .x

$(EXE_1): $(OBJS_1)
	$(CC) $(CFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS_1) $(LIBS) 2>&1 | c++filt



.cpp.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

.cc.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJS_1) *~ $(EXE_1) core


depend:
	makedepend $(CFLAGS) $(INCDIR) $(SRCS_1) > /dev/null 2>&1

