
MODULE = sim_1b

SRCS = stimul.cpp counter.cpp bcd_decoder.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET_ARCH = linux64


SHELL  = /bin/sh

CC     = g++
OPT    = -O3
DEBUG  = -g
OTHER  = -Wno-deprecated
CFLAGS = $(OPT) $(OTHER)
#CFLAGS = $(DEBUG) $(OTHER)


INCDIR = -I. -I.. -I$(SYSTEMC)/include

LIBDIR = -L. -L.. -L$(SYSTEMC)/lib-$(TARGET_ARCH)

LIBS   = $(SYSTEMC)/lib-$(TARGET_ARCH)/libsystemc.a -lm -lpthread $(EXTRA_LIBS)


EXE    = $(MODULE).x

.SUFFIXES: .cc .cpp .o .x

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS) $(LIBS) 2>&1 | c++filt

.cpp.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

.cc.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJS) *~ $(EXE) core


depend:
	makedepend $(CFLAGS) $(INCDIR) $(SRCS) > /dev/null 2>&1

