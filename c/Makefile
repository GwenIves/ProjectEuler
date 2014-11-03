############### Definitions

main_sources := $(wildcard *.c)
lib_sources := $(wildcard common/*c)

sources := $(main_sources) $(lib_sources)
headers := $(wildcard *.h common/*.h)

dependencies := $(subst .c,.d,$(sources))
objects := $(subst .c,.o,$(sources))

executables := $(subst .c,,$(main_sources))

CFLAGS += --pedantic -Wall -Werror -std=gnu99 -O3
CPPFLAGS += -Icommon/include
LDFLAGS += -L.

VPATH := common

############### Top level targets

.PHONY: build
build:  $(executables)

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
