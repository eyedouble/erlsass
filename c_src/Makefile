OSNAME := $(shell erl -noshell -s init stop -eval "{Osfamily, Osname} = os:type(), io:format(\"~ts\", [Osfamily]).")

ifeq ($(OSNAME), win32)	
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

$(info .${OSNAME}.)
$(info .${ERTS_INCLUDE_DIR}.)
$(info .${ERL_INTERFACE_INCLUDE_DIR}.)
$(info .${ERL_INTERFACE_LIB_DIR}.)

# $(info .${C_SRC_DIR}.)

# C_SRC_DIR = $(CURDIR)
# C_SRC_OUTPUT ?= $(CURDIR)/../priv/$(PROJECT).so


# System type and C compiler/flags.

#UNAME_SYS := $(shell uname -s)
ifeq ($(OSNAME), unix)
	CC ?= gcc
	CFLAGS ?= -O3 -std=c99 -finline-functions -Wall -Wmissing-prototypes
	CXXFLAGS ?= -O3 -finline-functions -Wall
	LIBNAME := erlsass_nif.so
	COPY := cp libsass/lib/libsass.so ../priv
else ifeq ($(OSNAME), win32)
	CC ?= gcc
	CFLAGS ?= -O3 -std=c99 -finline-functions -Wall -Wmissing-prototypes
	CXXFLAGS ?= -O3 -finline-functions -Wall
	LIBNAME := erlsass_nif.dll	
	COPY := copy ".\libsass\lib\libsass.dll" ".\..\priv"
endif

CFLAGS += -I "$(ERTS_INCLUDE_DIR)" -I "$(ERL_INTERFACE_INCLUDE_DIR)" -I "libsass/include" -I "libsass"
# WINCXXFLAGS += -L "libsass/lib" -lsass -I "$(ERTS_INCLUDE_DIR)" -I "$(ERL_INTERFACE_INCLUDE_DIR)"  -I "libsass/include" 
CXXFLAGS += -I "$(ERTS_INCLUDE_DIR)" -I "$(ERL_INTERFACE_INCLUDE_DIR)"  -I "libsass/include" $(CURDIR)/libsass/lib/libsass.so

LDLIBS += -L "$(ERL_INTERFACE_LIB_DIR)" -lerl_interface -lei
LDFLAGS += -shared





all:
	$(shell gcc -o ../priv/$(LIBNAME) -fpic -shared erlsass_nif.cpp $(CXXFLAGS))
	$(COPY)

# # Verbosity.

# c_verbose_0 = @echo " C     " $(?F);
# c_verbose = $(c_verbose_$(V))

# cpp_verbose_0 = @echo " CPP   " $(?F);
# cpp_verbose = $(cpp_verbose_$(V))

# link_verbose_0 = @echo " LD    " $(@F);
# link_verbose = $(link_verbose_$(V))

# SOURCES := $(shell find $(C_SRC_DIR) -type f \( -name "*.c" -o -name "*.C" -o -name "*.cc" -o -name "*.cpp" \))
# OBJECTS = $(addsuffix .o, $(basename $(SOURCES)))

# COMPILE_C = $(c_verbose) $(CC) $(CFLAGS) $(CPPFLAGS) -c
# COMPILE_CPP = $(cpp_verbose) $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c

# $(C_SRC_OUTPUT): $(OBJECTS)
# 	@mkdir -p $(BASEDIR)/priv/
# 	$(link_verbose) $(CC) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(C_SRC_OUTPUT)

# %.o: %.c
# 	$(COMPILE_C) $(OUTPUT_OPTION) $<

# %.o: %.cc
# 	$(COMPILE_CPP) $(OUTPUT_OPTION) $<

# %.o: %.C
# 	$(COMPILE_CPP) $(OUTPUT_OPTION) $<

# %.o: %.cpp
# 	$(COMPILE_CPP) $(OUTPUT_OPTION) $<

# clean:
# 	@rm -f $(C_SRC_OUTPUT) $(OBJECTS)
