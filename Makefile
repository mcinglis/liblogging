
##############################
### VARIABLES
##############################

DEPS_DIR ?= deps

LIBMAYBE := $(DEPS_DIR)/libmaybe
LIBSTR   := $(DEPS_DIR)/libstr

CPPFLAGS += -I$(DEPS_DIR)

cflags_std := -std=c11
cflags_warnings := -Wall -Wextra -pedantic \
                   -Wcomments -Wformat=2 -Wlogical-op -Wmissing-include-dirs \
                   -Wnested-externs -Wold-style-definition -Wredundant-decls \
                   -Wshadow -Wstrict-prototypes -Wunused-macros -Wvla \
                   -Wwrite-strings \
                   -Wno-override-init -Wno-unused-parameter

CFLAGS ?= $(cflags_std) -g $(cflags_warnings)

TPLRENDER ?= $(DEPS_DIR)/tplrender/tplrender


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
objects: $(objects)

.PHONY: examples
examples: $(examples)

.PHONY: clean
clean:
	rm -rf $(objects) $(examples) $(mkdeps) \
	       $(LIBSTR)/str.o \
	       $(LIBMAYBE)/def/maybe-size.h


%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MF "$(@:.o=.dep.mk)" -c $< -o $@


$(LIBSTR)/str.o: $(LIBMAYBE)/def/maybe-size.h

$(LIBMAYBE)/def/maybe-size.h: $(LIBMAYBE)/def.h.jinja
	$(TPLRENDER) $< "size_t" -o $@

logseverity.o: $(LIBMAYBE)/def/maybe-size.h

$(examples): logseverity.o \
             logger.o \
             $(LIBSTR)/str.o


-include $(mkdeps)


