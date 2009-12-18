# Makefile for Android operating system

OS = ANDROID
CPU := ARM
ARCH_DETECTED := 32BITS
NO_ASM := 1
TARGET = libmupen64plus.so.2.0.0
SONAME = libmupen64plus.so.2

SRCDIR = src
OBJDIR = _obj

SDLDIR = ~/SDL-1.2.13-android
CROSS_COMPILE = arm-eabi-

CC       = agcc
CXX      = ag++
LD       = ag++
RM       = rm
#INSTALL  = install
#LDCONFIG = ldconfig
STRIP       = $(CROSS_COMPILE)strip -s

# base CFLAGS, LIBS, and LDFLAGS
CFLAGS = -Wall -ffast-math -funroll-loops -fexpensive-optimizations -fno-strict-aliasing -I$(SRCDIR) -I$(SDLDIR)/include
# removed: -lpng -lfreetype so this would compile
LIBS = -ldl -lz -lm

# for android
CFLAGS += -fno-short-enums

# compiler/linker flags for various compile-time options.
# 1. macro for no assembly language
ifeq ($(NO_ASM), 1)
  CFLAGS += -DNO_ASM
endif

# the following were temporarily removed from SOURCE because they wouldn't compile without modifications:
# $(SRCDIR)/main/savestates.c \
# $(SRCDIR)/main/zip/ioapi.c \
# $(SRCDIR)/main/zip/zip.c \
# $(SRCDIR)/main/zip/unzip.c \
#$(SRCDIR)/osd/OGLFT.cpp \
#$(SRCDIR)/osd/osd.cpp \
#$(SRCDIR)/osd/screenshot.cpp

# list of required source files for compilation
SOURCE = \
	$(SRCDIR)/api/callbacks.c \
	$(SRCDIR)/api/common.c \
	$(SRCDIR)/api/config.c \
	$(SRCDIR)/api/debugger.c \
	$(SRCDIR)/api/frontend.c \
	$(SRCDIR)/api/vidext.c \
	$(SRCDIR)/main/main.c \
	$(SRCDIR)/main/util.c \
	$(SRCDIR)/main/cheat.c \
	$(SRCDIR)/main/eventloop.c \
	$(SRCDIR)/main/md5.c \
	$(SRCDIR)/main/rom.c \
	$(SRCDIR)/main/ini_reader.c \
	$(SRCDIR)/main/adler32.c \
	$(SRCDIR)/memory/dma.c \
	$(SRCDIR)/memory/flashram.c \
	$(SRCDIR)/memory/memory.c \
	$(SRCDIR)/memory/pif.c \
	$(SRCDIR)/memory/tlb.c \
	$(SRCDIR)/osal/dynamiclib_unix.c \
	$(SRCDIR)/osal/files_unix.c \
	$(SRCDIR)/plugin/plugin.c \
	$(SRCDIR)/plugin/dummy_video.c \
	$(SRCDIR)/plugin/dummy_audio.c \
	$(SRCDIR)/plugin/dummy_input.c \
	$(SRCDIR)/plugin/dummy_rsp.c \
	$(SRCDIR)/r4300/r4300.c \
	$(SRCDIR)/r4300/bc.c \
	$(SRCDIR)/r4300/cop0.c \
	$(SRCDIR)/r4300/cop1.c \
	$(SRCDIR)/r4300/cop1_d.c \
	$(SRCDIR)/r4300/cop1_l.c \
	$(SRCDIR)/r4300/cop1_s.c \
	$(SRCDIR)/r4300/cop1_w.c \
	$(SRCDIR)/r4300/exception.c \
	$(SRCDIR)/r4300/interupt.c \
	$(SRCDIR)/r4300/profile.c \
	$(SRCDIR)/r4300/pure_interp.c \
	$(SRCDIR)/r4300/recomp.c \
	$(SRCDIR)/r4300/special.c \
	$(SRCDIR)/r4300/regimm.c \
	$(SRCDIR)/r4300/tlb.c

# dynarec won't be supported for a while
ifeq ($(DYNAREC), )
  SOURCE += $(SRCDIR)/r4300/empty_dynarec.c
endif

ifeq ($(DEBUGGER), 1)
  SOURCE += \
        $(SRCDIR)/debugger/debugger.c \
        $(SRCDIR)/debugger/dbg_decoder.c \
        $(SRCDIR)/debugger/dbg_opprintf.c \
        $(SRCDIR)/debugger/dbg_memory.c \
        $(SRCDIR)/debugger/dbg_breakpoints.c
  LIBS += -lopcodes -lbfd
endif

# generate a list of object files to build, make a temporary directory for them
OBJECTS := $(patsubst $(SRCDIR)/%.c,   $(OBJDIR)/%.o, $(filter %.c,   $(SOURCE)))
OBJECTS += $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(filter %.cpp, $(SOURCE)))
OBJDIRS = $(dir $(OBJECTS))
$(shell mkdir -p $(OBJDIRS))

all: $(TARGET)

clean:
	$(RM) -rf $(TARGET) $(SONAME) ./_obj

# build rules
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(LIBS) $(OBJECTS) -o $@
	$(STRIP) $@
	if [ "$(SONAME)" != "" ]; then ln -sf $@ $(SONAME); fi

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -o $@ $(CFLAGS) -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

