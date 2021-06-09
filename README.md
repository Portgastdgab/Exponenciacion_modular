## Project Fyle Structure

    Project_name/
    |
    |---- CMakeLists.txt
    |
    |---- include/
    |       |
    |       |---- Project_name
    |               |
    |               |---- public_headers.h
    |---- src/
    |       |
    |       |---- private_headers.hh (C++ only)
    |       |---- private_headers.h  (C & C++)
    |       |---- implementation_files.cc
    |       |---- implementation_files.C (if compiler doesn't accept .cc)
    |       |---- inline_definition_files.icc
    |       |---- main.cpp
    |
    |---- libs/
    |       |
    |       |---- A
    |       |
    |       |---- B
    |
    |---- tests/

## Compile the project

```bash I'm A tab
    take build/
    cmake ..
    make .
```
