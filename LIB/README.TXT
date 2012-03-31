The Makefile in this folder calls the one in the library.

"$ make clean" will remove objects from both the library and the "main" dir.

If the library exist, calling make in the root directory will _NOT_ trigger the
secondary Makefile so any changes in the library sources will _NOT_ be detected.
