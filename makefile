CXX       =g++
TARGET    =raytracer
TARGET_MP =$(TARGET)_mp
CFLAGS    =-O3 --std=c++11
CFLAGS_SP =$(CFLAGS) -o $(BIN_SP)
CFLAGS_MP =$(CFLAGS) -D=__USE_OPENMP__ -o $(BIN_MP)
LDFLAGS_SP=-lm
LDFLAGS_MP=$(LDFLAGS_SP) -fopenmp

# platform detection
PLATFORM  =
ifeq ($(OS),Windows_NT)
	LDFLAGS_SP+=-s
	BIN_SP=$(TARGET).exe
	BIN_MP=$(TARGET)_mp.exe
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		PLATFORM=win64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		PLATFORM=win32
	endif
else
	BIN_SP=$(TARGET)
	BIN_MP=$(TARGET)_mp
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		PLATFORM=linux
	endif
	ifeq ($(UNAME_S),Darwin)
		PLATFORM=darwin
		LDFLAGS_MP=$(LDFLAGS_SP) -Xpreprocessor -fopenmp -lomp
	endif
endif
OUTPUT    =bin/$(PLATFORM)
INCLUDE   =include
HEADERS   =$(INCLUDE)/vec3.h \
		   $(INCLUDE)/ray.h \
			$(INCLUDE)/sphere.h \
		   $(INCLUDE)/hitable.h \
		   $(INCLUDE)/hitable_list.h \
		   $(INCLUDE)/material.h \
		   $(INCLUDE)/rng.h \
		   $(INCLUDE)/camera.h \
		   $(INCLUDE)/bitmap.h \
		   $(INCLUDE)/timer.h

SOURCE=main.cpp

all: $(SOURCE) $(HEADERS)
	@echo ---------------------
	@echo - Binaries location = $(OUTPUT)
	@echo - Compile flags SP. = $(CFLAGS_SP)
	@echo - Compile flags MP. = $(CFLAGS_MP)
	@echo - Link flags SP.... = $(LDFLAGS_SP)
	@echo - Link flags MP.... = $(LDFLAGS_MP)
	@echo ---------------------

	@mkdir -p $(OUTPUT)

	@echo Building single-threaded app: $(BIN_SP)
	@$(CXX) $(CFLAGS_SP) $(SOURCE) $(LDFLAGS_SP)

	@echo Building multi-threaded app : $(BIN_MP)
	@$(CXX) $(CFLAGS_MP) $(SOURCE) $(LDFLAGS_MP)

	@echo Relocating binaries...
	@mv ./$(BIN_SP) $(OUTPUT)
	@mv ./$(BIN_MP) $(OUTPUT)

clean:
	@echo Cleaning previous binaries...
	@rm -f $(OUTPUT)/$(BIN_SP)
	@rm -f $(OUTPUT)/$(BIN_MP)
