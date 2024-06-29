A class for passing command line arguments. Usage in the argParseExample.cpp file. Compile example (e.g. 'g++ argParseExample.cpp -o argParseExample' , or 'cl /std:c++17 /EHsc argParseExample.cpp'). Then run with some arguments, e.g.

argParseExample.exe 5.7 -fkw 73 hello,world --secondkw hi

Result printed to terminal:

first positional: 5.7<br>
second positional: hello,world<br>
firstkw: 73<br>
secondkw: hi<br>
73<br>
5.7<br>
78.7<br>
hello<br>
world<br>