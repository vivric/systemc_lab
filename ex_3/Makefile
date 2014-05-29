
MODULE_2 = sim_2

SRCS_2 = prod_2.cpp consum_2.cpp fifo_2.cpp main_2.cpp
OBJS_2 = $(SRCS_2:.cpp=.o)

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


EXE_2    = $(MODULE_2).x

.SUFFIXES: .cc .cpp .o .x

$(EXE_2): $(OBJS_2)
	$(CC) $(CFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS_2) $(LIBS) 2>&1 | c++filt


.cpp.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

.cc.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJS_2) *~ $(EXE_2) core


depend:
	makedepend $(CFLAGS) $(INCDIR) $(SRCS_2) > /dev/null 2>&1


