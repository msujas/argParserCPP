For building, check CMake files for example. If you add this as a submodule into a repository, in the CMake file you can use 
```CMake
add_submodule(argParserCPP/argParser)
target_link_libraries(executableName
argParser
)
```
To compile the library alone, run in the argParser subdirectory:
```
mkdir build
cmake -B build
cmake --build build --config release/debug
```
File will be in the build folder or build/release or build/debug . You can then link the library file (.lib (Windows MSVC) or .a (gcc/g++)) to your project.

For use in .cpp file see below. Alternatively, you can include the .cpp file instead of the .h if you don't want to compile the library.

A class for passing command line arguments. Usage in the argParseExample.cpp file. Compile example (same as above with cmake, but in top directory). Then run with some arguments. Keywords and their arguments must be space separated.

Arguments beginning '-' are assumed to be a keyword or flag argument. If it isn't in the list, the program exits.

E.g.

```example 5.6 -fkw 42 hello,world --secondkw hi -kw3 5.7,1.2,98.3 --flag1 ```

Result printed to terminal:
```
first positional (string): 5.6
second positional (string): hello,world
firstkw (string): 42
secondkw (string): hi
flag1 string: true
firstkw (int): 42
first positional (float): 5.6
firstkw + first positional: 47.6
p2 unpacked:
        hello
        world
kw3 unpacked:
        5.7
        1.2
        98.3
flag1: 1
multi positional aguments
```

Use -h or --help to display the help message:
```
usage: ./example [--help/-h] [--firstkw/-fkw] [--secondkw/-secondkw] [--kw3/-kw3] [--flag1/-f1] <first> <second> <multipositional(multiple positions)> 
---------

key word arguments:

--help/-h:                display this help message and exit
--firstkw/-fkw:           the first keyword argument, integer
--secondkw/-secondkw:     the second keyword argument, string
--kw3/-kw3:               the third keyword argument, vector<float>

flags

--flag1/-f1:              flag argument

positional arguments:

--first:                  the first positional argument, float
--second:                 the second positional argument, vector<string>
--multipositional:        a multi positiona argument, vector<string>

```
```C++
#include "argParser.h"
#include <vector>

int main(int argc, char *argv[]){
ArgParser ap;
ap.addKW("kw1","1"); //full name, default value, short name
ap.addKW("kw2","1,2,3,4");
ap.addPositional("p1","2"); //name, default value

ap.readArguments(argc,argv); //needed to process arguments

int kw1 = ap.getArg<int>("kw1");
float p1 = ap.getArg<float>("p1");
std::vector<float> kw2 = ap.getVectorArg<float>("kw2");
}
```
