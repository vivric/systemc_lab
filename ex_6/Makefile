
MODULE = processing_cpu

PATH_COMMON = ../npu_common
SRCS_COMMON = $(PATH_COMMON)/DmaChannel.cpp $(PATH_COMMON)/EthernetLink.cpp $(PATH_COMMON)/IoModule.cpp $(PATH_COMMON)/IpPacket.cpp $(PATH_COMMON)/memory.cpp $(PATH_COMMON)/MemoryManager.cpp $(PATH_COMMON)/PcapImporter.cpp $(PATH_COMMON)/RAM.cpp $(PATH_COMMON)/SimpleBusAT.cpp $(PATH_COMMON)/report.cpp $(PATH_COMMON)/globals.cpp $(PATH_COMMON)/RoutingTable.cpp $(PATH_COMMON)/Cpu_proc.cpp

SRCS_LOCAL = Cpu.cpp main.cpp

SRCS =$(SRCS_COMMON) $(SRCS_LOCAL)

OBJS_COMMON = $(SRCS_COMMON:.cpp=.o)
OBJS_LOCAL = $(SRCS_LOCAL:.cpp=.o)

TARGET_ARCH = linux64


SHELL  = /bin/sh

CC     = g++
OPT    = -O3
DEBUG  = -g
OTHER  = -DSC_INCLUDE_DYNAMIC_PROCESSES -Wno-deprecated
#CFLAGS = $(OPT) $(OTHER)
CFLAGS = $(DEBUG) $(OTHER)
EXTRA_LIBS = -lpcap


INCDIR = -I. -I$(PATH_COMMON) -I$(SYSTEMC)/include

LIBDIR = -L. -L$(PATH_COMMON) -L$(SYSTEMC)/lib-$(TARGET_ARCH)

LIBS   = $(SYSTEMC)/lib-$(TARGET_ARCH)/libsystemc.a  -lm -lpthread $(EXTRA_LIBS)


EXE    = $(MODULE).x

.SUFFIXES: .cc .cpp .o .x

$(EXE): $(OBJS_LOCAL) $(OBJS_COMMON)
	$(CC) $(CFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS_LOCAL) $(OBJS_COMMON) $(LIBS) 2>&1 | c++filt


.cpp.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

.cc.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJS_LOCAL) $(EXE) core

clean_all:
	rm -f $(OBJS_LOCAL) $(OBJS_COMMON) $(EXE) core

depend:
	makedepend $(CFLAGS) $(INCDIR) $(SRCS) > /dev/null 2>&1


