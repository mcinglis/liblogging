
##############################
### VARIABLES
##############################

DEPS_DIR ?= ./deps

CPPFLAGS += -I$(DEPS_DIR)

cflags_std := -std=c11
cflags_warnings := -Wall -Wextra -pedantic \
                   -Wcomments -Wformat=2 -Wlogical-op -Wmissing-include-dirs \
                   -Wnested-externs -Wold-style-definition -Wredundant-decls \
                   -Wshadow -Wstrict-prototypes -Wunused-macros -Wvla \
                   -Wwrite-strings \
                   -Wno-override-init -Wno-unused-parameter

CFLAGS ?= $(cflags_std) -g $(cflags_warnings)

example_sources := $(wildcard examples/*.c)
example_objects := $(example_sources:.c=.o)
examples := $(example_sources:.c=)

sources  := $(wildcard *.c)
objects  := $(sources:.c=.o)


mkdeps   := $(objects:.o=.dep.mk) $(example_objects:.o=.dep.mk)


##############################
### BUILDING
##############################

.PHONY: all
all: objects examples

.PHONY: fast
fast: CPPFLAGS += -DNDEBUG -DNO_ASSERT -DNO_REQUIRE -DNO_DEBUG
fast: CFLAGS = $(cflags_std) -O3 $(cflags_warnings)
fast: all


.PHONY: objects
objects: $(objects) logging.o

logging.o: $(objects)
	$(LD) -r $^ -o $@


.PHONY: examples
examples: $(examples)

$(examples): logging.o \
             $(DEPS_DIR)/libbase/char.o \
             $(DEPS_DIR)/libstr/str.o


.PHONY: clean
clean:
	rm -rf $(objects) logging.o $(example_objects) $(examples) $(mkdeps)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MF "$(@:.o=.dep.mk)" -c $< -o $@

-include $(mkdeps)


