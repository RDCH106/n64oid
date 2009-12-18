# Makefile for Android operating system

OS = ANDROID
CPU := ARM
ARCH_DETECTED := 32BITS
NO_ASM := 1
TARGET = n64oid

SRCDIR = src
OBJDIR = _obj

SDLDIR = ../SDL
CROSS_COMPILE = arm-eabi-

CC       = agcc
CXX      = ag++
LD       = agcc
RM       = rm
#INSTALL  = install
#LDCONFIG = ldconfig
STRIP       = $(CROSS_COMPILE)strip -s

# base CFLAGS, LIBS, and LDFLAGS
#CFLAGS = -Wall -ffast-math -funroll-loops -fexpensive-optimizations -fno-strict-aliasing -I$(SRCDIR) -I$(SDLDIR)/include
CFLAGS = -O2 -pipe -fno-short-enums -I../core/src/api

# compiler/linker flags for various compile-time options.
# 1. macro for no assembly language
ifeq ($(NO_ASM), 1)
  CFLAGS += -DNO_ASM
endif

# list of source files to compile
SOURCE = \
	$(SRCDIR)/cheat.c \
	$(SRCDIR)/compare_core.c \
	$(SRCDIR)/core_interface.c \
	$(SRCDIR)/main.c \
	$(SRCDIR)/plugin.c \
	$(SRCDIR)/osal_dynamiclib_unix.c \
	$(SRCDIR)/osal_files_unix.c

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

#$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
#	$(CXX) -o $@ $(CFLAGS) -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

