# Makefile for Android operating system

OS = ANDROID
CPU := ARM
ARCH_DETECTED := 32BITS
NO_ASM := 1
TARGET = libinputsdl.so

SRCDIR = src
OBJDIR = _obj

SDLDIR = ../SDL
CROSS_COMPILE = arm-eabi-

CC       = agcc
CXX      = ag++
LD       = $(CROSS_COMPILE)gcc
RM       = rm
#INSTALL  = install
#LDCONFIG = ldconfig
STRIP       = $(CROSS_COMPILE)strip -s

# base CFLAGS, LIBS, and LDFLAGS
#CFLAGS = -Wall -ffast-math -funroll-loops -fexpensive-optimizations -fno-strict-aliasing -I$(SRCDIR) -I$(SDLDIR)/include
CFLAGS = -O2 -pipe -fno-short-enums -I$(SRCDIR) -I$(SDLDIR)/include -I../core/src/api

SRC_PATH=$(ANDROID_SDK)/src
ALIB=$(SRC_PATH)/out/target/product/generic/obj/lib

GCCLIBS = $(shell $(CC) -mthumb-interwork -print-libgcc-file-name)
LDFLAGS = -Wl,-soname,$(notdir $(TARGET)) -nostdlib -T $(SRC_PATH)/build/core/armelf.xsc -shared -Bsymbolic -L$(ALIB) --no-whole-archive -lc -lm -ldl -lz --no-undefined $(GCCLIBS) --whole-archive 

LIBS = -L$(SDLDIR) -lSDL

ifeq ($(PLUGINDBG), 1)
  CFLAGS += -D_DEBUG
endif

# list of source files to compile
SOURCE = \
        $(SRCDIR)/plugin.c \
        $(SRCDIR)/autoconfig.c \
        $(SRCDIR)/config.c \
        $(SRCDIR)/osal_dynamiclib_unix.c

# generate a list of object files to build, make a temporary directory for them
OBJECTS := $(patsubst $(SRCDIR)/%.c,   $(OBJDIR)/%.o, $(filter %.c,   $(SOURCE)))
#OBJECTS += $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(filter %.cpp, $(SOURCE)))
OBJDIRS = $(dir $(OBJECTS))
$(shell mkdir -p $(OBJDIRS))

all: $(TARGET)

clean:
	$(RM) -rf $(TARGET) $(SONAME) ./_obj

# build rules
$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) $(LIBS) $(OBJECTS) -o $@

#	$(STRIP) $@
#	if [ "$(SONAME)" != "" ]; then ln -sf $@ $(SONAME); fi

#$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
#	$(CXX) -o $@ $(CFLAGS) -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

