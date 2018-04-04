
#
# Define OS
#
OS ?= $(shell uname -s)

ifneq (,$(findstring /cygdrive/,$(PATH)))
	OSNAME := Cygwin
else
	ifneq (,$(findstring Windows_NT,$(OS)))
		OSNAME := Windows
	else
		ifneq (,$(findstring mingw32,$(MAKE)))
			OSNAME := Windows
		else
			ifneq (,$(findstring MINGW32,$(shell uname -s)))
				OSNAME = Windows
			else
				OSNAME := $(shell uname -s)
			endif
		endif
	endif
endif

#
# Set Current Dir
#
ifeq ($(OSNAME), Windows)	
	CURDIR := $(shell echo %cd%)
else
	CURDIR := $(shell pwd)
endif

BASEDIR := $(abspath $(CURDIR)/..)
PROJECT ?= $(notdir $(BASEDIR))
PROJECT := $(strip $(PROJECT))

ERTS_INCLUDE_DIR ?= $(shell erl -noshell -s init stop -eval "io:format(\"~ts/erts-~ts/include\", [code:root_dir(), erlang:system_info(version)]).")
ERL_INTERFACE_INCLUDE_DIR ?= $(shell erl -noshell -s init stop -eval "io:format(\"~ts\", [code:lib_dir(erl_interface, include)]).")
ERL_INTERFACE_LIB_DIR ?= $(shell erl -noshell -s init stop -eval "io:format(\"~ts\", [code:lib_dir(erl_interface, lib)]).")

#
# OS SPECIFIc
# 
ifeq ($(OSNAME), Windows)
	SLEXT := .dll
	LIBNAME := erlsass_nif$(SLEXT)
	COPY := copy ".\libsass\lib\libsass$(SLEXT)" ".\..\priv"
	COPY2 := copy "$(LIBNAME)" ".\..\priv"
	RM := del /f
else 
	SLEXT := .so
	LIBNAME := erlsass_nif$(SLEXT)
	COPY := cp libsass/lib/libsass$(SLEXT) ../priv
	COPY2 := cp $(LIBNAME) ../priv
	RM := rm -f
endif

#
# OPTIONS
#
CC       ?= gcc
CXX      ?= g++
CFLAGS ?= -O3 -std=c99 -finline-functions -Wall -Wmissing-prototypes
CXXFLAGS ?= -O3 -finline-functions -Wall

#
#	Compilation
#
CFLAGS += -I "$(ERTS_INCLUDE_DIR)" -I "$(ERL_INTERFACE_INCLUDE_DIR)" -I "libsass/include" -I "libsass"
CXXFLAGS += -I "$(ERTS_INCLUDE_DIR)" -I "$(ERL_INTERFACE_INCLUDE_DIR)"  -I "libsass/include" "../priv/libsass.dll"

LDLIBS += -L "$(ERL_INTERFACE_LIB_DIR)" -lerl_interface -lei
LDFLAGS += -shared

# $(info ${OS})
# $(info ${OSNAME})
# $(info ${CURDIR})
# $(info ${PROJECT})
# $(info ${ERTS_INCLUDE_DIR})
# $(info ${ERL_INTERFACE_INCLUDE_DIR})
# $(info ${ERL_INTERFACE_LIB_DIR})

ifeq (,$(wildcard ./$(LIBNAME))) 
all: copy1 compile copy2 
else
all: compile
endif	

compile:
	$(shell g++ -o $(LIBNAME) -fpic -shared erlsass_nif.cpp $(CXXFLAGS))

copy1:
	$(COPY)

copy2:
	$(COPY2)

clean:
	$(RM) $(LIBNAME)

.PHONY: copy1 copy2