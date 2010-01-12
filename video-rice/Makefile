# Makefile for Android operating system

OS = ANDROID
CPU := ARM
ARCH_DETECTED := 32BITS
NO_ASM := 1
TARGET = libvideorice.so

SRCDIR = src
OBJDIR = _obj

SDLDIR = ../SDL

# defines to use ndk-wrapper library for STL
WRAPPER := $(ANDROID_SDK)/ndk-wrappers
STLLIB := -L$(WRAPPER)/stlport/build/lib/obj/arm-linux-gcc/so

CC       = $(WRAPPER)/bin/arm-linux-gcc
CXX      = $(WRAPPER)/bin/arm-linux-g++
LD       = $(WRAPPER)/bin/arm-linux-g++
RM       = rm
#INSTALL  = install
#LDCONFIG = ldconfig
#STRIP       = $(CROSS_COMPILE)strip -s

# base CFLAGS, LIBS, and LDFLAGS
#CFLAGS = -Wall -ffast-math -funroll-loops -fexpensive-optimizations -fno-strict-aliasing -I$(SRCDIR) -I$(SDLDIR)/include
CFLAGS = -O2 -pipe -fno-short-enums -I../core/src/api -I$(SDLDIR)/include -I$(ANDROID_SDK)/src/frameworks/base/opengl/include
#CPPFLAGS = -fexceptions

SRC_PATH=$(ANDROID_SDK)/src
ALIB=$(SRC_PATH)/out/target/product/generic/obj/lib

GCCLIBS = $(shell $(CC) -mthumb-interwork -print-libgcc-file-name)
LIBS = -L$(SDLDIR) -lSDL -lGLESv1_CM -ldl -lstdc++ -lstlport
LDFLAGS = -Wl,-soname,$(notdir $(TARGET)) -nostdlib -T $(SRC_PATH)/build/core/armelf.xsc -shared -Bsymbolic -L$(ALIB) --no-whole-archive -lc -lm -ldl -lz --no-undefined

# compiler/linker flags for various compile-time options.
# 1. macro for no assembly language
ifeq ($(NO_ASM), 1)
  CFLAGS += -DNO_ASM
endif

# removed temporarily
#        $(SRCDIR)/liblinux/pngrw.c \
#        $(SRCDIR)/OGLCombinerNV.cpp
#        $(SRCDIR)/OGLFragmentShaders.cpp \
#        $(SRCDIR)/OGLExtCombiner.cpp \
#        $(SRCDIR)/OGLCombinerTNT2.cpp \
#        $(SRCDIR)/OGLExtRender.cpp \

# list of source files to compile
SOURCE = \
	$(SRCDIR)/liblinux/BMGImage.c \
	$(SRCDIR)/liblinux/BMGUtils.cpp \
	$(SRCDIR)/liblinux/bmp.c \
	$(SRCDIR)/osal_dynamiclib_unix.c \
	$(SRCDIR)/Blender.cpp \
	$(SRCDIR)/Combiner.cpp \
	$(SRCDIR)/CombinerTable.cpp \
	$(SRCDIR)/Config.cpp \
	$(SRCDIR)/ConvertImage.cpp \
	$(SRCDIR)/ConvertImage16.cpp \
	$(SRCDIR)/CNvTNTCombiner.cpp \
	$(SRCDIR)/Debugger.cpp \
	$(SRCDIR)/DecodedMux.cpp \
	$(SRCDIR)/DirectXDecodedMux.cpp \
	$(SRCDIR)/DeviceBuilder.cpp \
	$(SRCDIR)/FrameBuffer.cpp \
	$(SRCDIR)/GeneralCombiner.cpp \
	$(SRCDIR)/GraphicsContext.cpp \
	$(SRCDIR)/OGLCombiner.cpp \
	$(SRCDIR)/OGLDecodedMux.cpp \
	$(SRCDIR)/OGLGraphicsContext.cpp \
	$(SRCDIR)/OGLRender.cpp \
	$(SRCDIR)/OGLRenderExt.cpp \
	$(SRCDIR)/OGLTexture.cpp \
	$(SRCDIR)/Render.cpp \
	$(SRCDIR)/RenderBase.cpp \
	$(SRCDIR)/RenderExt.cpp \
	$(SRCDIR)/RenderTexture.cpp \
	$(SRCDIR)/RSP_Parser.cpp \
	$(SRCDIR)/RSP_S2DEX.cpp \
	$(SRCDIR)/Texture.cpp \
	$(SRCDIR)/TextureFilters.cpp \
	$(SRCDIR)/TextureFilters_2xsai.cpp \
	$(SRCDIR)/TextureFilters_hq2x.cpp \
	$(SRCDIR)/TextureFilters_hq4x.cpp \
	$(SRCDIR)/TextureManager.cpp \
	$(SRCDIR)/VectorMath.cpp \
	$(SRCDIR)/fake_REMOVE.c \
	$(SRCDIR)/Video.cpp

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
	$(LD) $(LDFLAGS) $(STLLIB) $(OBJECTS) $(LIBS) $(GCCLIBS) -o $@

#	$(STRIP) $@
#	if [ "$(SONAME)" != "" ]; then ln -sf $@ $(SONAME); fi

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -o $@ $(CFLAGS) $(CPPFLAGS) -c $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

