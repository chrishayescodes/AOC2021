# Advent of Code 2021 chrishayescodes

## Preface
Never done this before BUT, this year I will do it in WebAssembly.
I've never done WebAssembly NOR C NOR C++ so this is all new for
a crusty .Net dev.

Have been following Tsoding on youtube: https://www.youtube.com/c/TsodingDaily

## Links

Advent of Code: https://adventofcode.com/2021

User docker with the emscripten image: https://hub.docker.com/r/emscripten/emsdk

## Journal
### Day 1
Got set up with docker, wsl, and emscripten image on local machine.

File access in C and WebAssembly. You need to load the file to the WASM image. See: https://emscripten.org/docs/porting/files/packaging_files.html

C file access, see: https://stackoverflow.com/questions/19123334/how-to-use-stdgetline-to-read-a-text-file-into-an-array-of-strings-in-c

### Day 2
Basically just did Day 1 and 2 together. Fairly simple problems.

### Day 3
Learned about linked lists in C. See: 
- https://stackoverflow.com/questions/982388/how-to-implement-a-linked-list-in-c
- http://cslibrary.stanford.edu/103/LinkedListBasics.pdf

Also learned about bit shifting. I already knew ABOUT it but 
never had a need for it in .Net. Definitely had fun using it
in these problems.

Also learned about Function pointers. I use function arguments
in C# all the time, it's good to know they are available in
C and C++.

### Day 4
Part 01

A lot more understanding of pointers and pointers to pointers. 
Passing, understanding state, pointers that are arrays. Getting
pointers, deconstructing from pointers.

There was considerable refactoring to get work into separate
methods. Another learning point was the management of state
via pointers. Where object oriented programing deals with state
in an object based on a class, state in a language like C
depends on allocating memory in a root method and passing that
value to other methods to modify it's value. This is a
foriegn idea to a language like C# where you tend to avoid
out variables and ref values in favor of state managed at
the class level.