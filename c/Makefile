############### Definitions

main_sources := $(wildcard src/*.c)
lib_sources := $(wildcard common/*.c)
test_sources := $(wildcard tests/*.c)

sources := $(main_sources) $(lib_sources) $(test_sources)
headers := $(wildcard common/include/*.h)

dependencies := $(subst .c,.d,$(sources))
objects := $(subst .c,.o,$(sources))

executables := $(subst .c,,$(main_sources) $(test_sources))

WARNINGS := -Werror --pedantic -Wall -Wextra -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wwrite-strings -Wstrict-prototypes -Wno-overlength-strings
CFLAGS += $(WARNINGS) -std=c11
CPPFLAGS += -Icommon/include -D_POSIX_C_SOURCE=200809L
LDFLAGS += -L.

VPATH := common

############### Top level targets

.PHONY: build
build: CFLAGS += -O3
build: $(executables)

.PHONY: debug
debug: CFLAGS += -O0 -g
debug: $(executables)

.PHONY: all
all: build tags tests

.PHONY: tests
tests: build
	cd tests && ./test_all.sh

.PHONY: verify
verify: debug
	cd tests && ./verify_all.sh

.PHONY: clean
clean:
	@echo "Deleting all executables"
	@rm -f $(executables) 2>/dev/null
	@echo "Deleting all object files"
	@rm -f $(objects) 2>/dev/null
	@echo "Deleting all dependency files"
	@rm -f $(dependencies)
	@echo "Deleteing all archive files"
	@rm -f *.a

.PHONY: distclean
distclean: clean
	@echo "Deleting all generated files"
	@rm -f tags

tags: $(sources) $(headers)
	ctags --recurse=yes

############### Dependency generation

INCLUDE_DEPS := $(if $(findstring $(MAKECMDGOALS),clean distclean tags),N,Y)

# $(call make-dependencies,source-file,object-file,depend-file)
define make-dependencies
  $(CC) -x c           \
        -MM            \
        -MF $3         \
        -MP            \
        -MT $2         \
        -MT $3         \
        $(CPPFLAGS)    \
        $1
endef

ifeq "$(INCLUDE_DEPS)" "Y"
  -include $(dependencies)
endif

############### Explicit dependencies and rules

%.d: %.c
	$(call make-dependencies, $<,$(subst .d,.o,$@),$@)

$(executables): libeuler.a -lm

libeuler.a: $(patsubst %,libeuler.a(%),$(subst .c,.o,$(foreach file,$(lib_sources),$(notdir $(file)))))
