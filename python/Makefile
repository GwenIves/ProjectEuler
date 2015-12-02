############### Definitions

main_sources := $(wildcard src/*)
lib_sources := $(wildcard common/*.py)
test_sources := $(wildcard tests/*.py)

sources := $(main_sources) $(lib_sources) $(test_sources)

############### Top level targets

.PHONY: tests
tests:
	cd tests && ./test_all.sh

.PHONY: verify
verify:
	@pylint3 $(sources)

.PHONY: clean
clean:
	@find . -name __pycache__ | xargs rm -fr
	@find . -name "*.pyc" | xargs rm -fr

.PHONY: distclean
distclean: clean
	@echo "Deleting all generated files"
	@rm -f tags

tags: $(sources)
	ctags --recurse=yes
