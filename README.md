# Single File Libraries

This is my personal collection of libraries, I create them on my own for practice
purposes and small hobby projects, Ideally, one should use pre-existing libraries
in this domain to avoid security and memory bugs.

This repository is mostly C, with some hints of C++ or ASM perhaps.

The files in this repository are licensed to you under the MIT License.
Read more [here](LICENSE)

## Guidelines

Just download the file you need and it should work as a stand alone. By default
the implementation of the file in question is not compiled along with the main file
so that you can generate separate object files for it.

To generate the implementation alongside your main.c code

```c
#define ASF_IMPL
```

Note, any other files from this repository that are included will also be implemented
if you do this.

Ideally, include the following rule into your Makefile to compile the files from this
library separately into object files

```makefile
asflib/src/%.o: asflib/src/%.h
	$(CC) $(CFLAGS) -x c -c -DASF_IMPL -Wno-pragma-once-outside-header -Wno-unused-function -o $@ $<
```

where `asflib` is the folder where this repository is cloned.

Please also read the top block of each file, it contains important information
regarding custom compile options and other notes.