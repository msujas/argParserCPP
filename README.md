A class for passing command line arguments. Usage in the argParseExample.cpp file. Compile example (e.g. 'g++ argParseExample.cpp -o argParseExample' , or 'cl /std:c++17 /EHsc argParseExample.cpp'). Then run with some arguments. Keywords and their arguments must be space separated, e.g.

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

Use -h or --help to display the help message:

usage: a [--help/-h] [--firstkw/-fkw] [--secondkw/-secondkw] [--kw3/-kw3] \<first\> \<second\><br> 
---------<br>

key word arguments:

--help/-h: display this help message<br>
--firstkw/-fkw: the first keyword argument<br>
--secondkw/-secondkw: the second keyword argument<br>
--kw3/-kw3: the third keyword argument

positional arguments:

first: the first positional argument<br>
second: the second positional argument<br>

```C++
int main(int argc, char *argv[]){
ArgParser ap;
ap.addKW("kw1","1"); //full name, default value, short name
ap.addKW("kw2","1,2,3,4")
ap.addPositional("p1","2"); //name, default value
ap.readArguments(argc,argv);
int kw1 = ap.getArg<int>("kw1");
float p1 = ap.getArg<float>("p1");
vector<float> kw2 = ap.getVectorArg<float>("kw2");
}
```