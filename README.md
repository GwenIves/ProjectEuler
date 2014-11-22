# Project Euler Solutions

Solutions to the Project Euler problems in various programming languages.


Unless noted otherwise in the language sections, every solution should be:
   * **General** - supports calculations for an arbitrary input parameter
   * **Fast** - finishes at worst in hundreds of milliseconds for the reference input using contemporary hardware
   * **Self-contained** - no 3rd party or non-standard library usage
   * **Clear** - employs good software engineering practices and language idioms


## Currently implemented problems:
   * **C** - 81 problems


## Performance report

You can generate a simple performance comparison report of the used languages by running:

	./performance_report.sh

The script will print the number of executed solutions and their total running time for each language.


## Build instructions and language notes

### c/ subdirectory --- C11/POSIX

An example of a barebones, compiled, procedural language approach.

Build by running make from the top of the c/ directory tree

	make build      // default, compiles all binaries in the src subdir
	make all        // compiles binaries and also runs tests
	make tests      // runs all tests
	make clean      // deletes compilation related generated files
	make distclean  // deletes all generated files
	make tags       // creates a single ctags database with symbol lookups

##### Limitations
Does not check for numeric overflows, consequently a number of the solutions will produce incorrect answers for very large input parameters
