
##############################
### VARIABLES
##############################

DEPS_DIR ?= ./deps

LIBSTR ?= $(DEPS_DIR)/libstr

CPPFLAGS += -I$(DEPS_DIR)

cflags_std := -std=c11
cflags_warnings := -Wall -Wextra -pedantic \
                   -Wcomments -Wformat=2 -Wlogical-op -Wmissing-include-dirs \
                   -Wnested-externs -Wold-style-definition -Wredundant-decls \
                   -Wshadow -Wstrict-prototypes -Wunused-macros -Wvla \
                   -Wwrite-strings \
                   -Wno-override-init -Wno-unused-parameter

CFLAGS ?= $(cflags_std) -g $(cflags_warnings)


sources  := $(wildcard *.c)
objects  := $(sources:.c=.o)
mkdeps   := $(objects:.o=.dep.mk)
examples := $(basename $(wildcard examples/*.c))


##############################
### BUILDING
##############################

.PHONY: all
all: objects examples

.PHONY: fast
fast: CPPFLAGS += -DNDEBUG
fast: CFLAGS = $(cflags_std) -O3 $(cflags_warnings)
fast: all

.PHONY: objects
objects: $(objects) liblogging.o

.PHONY: examples
examples: $(examples)

.PHONY: clean
clean:
	rm -rf $(objects) liblogging.o $(examples) $(mkdeps)


%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MF "$(@:.o=.dep.mk)" -c $< -o $@


liblogging.o: $(objects)
	$(LD) -r $^ -o $@

$(examples): logging.o \
             $(LIBSTR)/str.o


-include $(mkdeps)


