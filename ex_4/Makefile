
MODULE_3 = sim_3

SRCS_3 = prod_3.cpp consum_3.cpp fifo_3.cpp main_3.cpp
OBJS_3 = $(SRCS_3:.cpp=.o)

TARGET_ARCH = linux64


SHELL  = /bin/sh

CC     = g++
OPT    = -O3
DEBUG  = -g
OTHER  = -DSC_INCLUDE_DYNAMIC_PROCESSES -Wno-deprecated
#CFLAGS = $(OPT) $(OTHER)
CFLAGS = $(DEBUG) $(OTHER)


INCDIR = -I. -I.. -I$(SYSTEMC)/include

LIBDIR = -L. -L.. -L$(SYSTEMC)/lib-$(TARGET_ARCH)

LIBS   = $(SYSTEMC)/lib-$(TARGET_ARCH)/libsystemc.a -lm -lpthread $(EXTRA_LIBS)


EXE_3    = $(MODULE_3).x

.SUFFIXES: .cc .cpp .o .x

$(EXE_3): $(OBJS_3)
	$(CC) $(CFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS_3) $(LIBS) 2>&1 | c++filt


.cpp.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

.cc.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJS_3) *~ $(EXE_3) core


depend:
	makedepend $(CFLAGS) $(INCDIR) $(SRCS_3) > /dev/null 2>&1
