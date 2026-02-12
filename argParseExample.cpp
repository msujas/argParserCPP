#include <iostream>
#include "argParser.h"
#include <map>
#include <vector>
#include <string>

#define MULTIARGS

using namespace std;


int main(int argc, char *argv[]){
    ArgParser ap;
    ap.addPositional("first", "1", "the first positional argument, float "+ std::string(150,'a')); //args - name, default value (string, default: "")
    ap.addPositional("second","2", "the second positional argument, vector<string>");
    ap.addKW("firstkw","3", "fkw", "the first keyword argument, integer"); // args - long name, default value (string, default: ""), short name (default: long name)
    ap.addKW("secondkw","4", "", "the second keyword argument, string");
    ap.addKW("kw3","5", "", "the third keyword argument, vector<float>");
    ap.addFlag("flag1",true, "f1","flag argument");
    #ifdef MULTIARGS
    ap.addMultiPositional("multipositional", "a multi positiona argument, vector<string>");
    #endif
    ap.readArguments(argc,argv);
    map<string,string> allArgs = ap.getAllArgs(); //returns map of all arguments with long names as strings

    std::cout << "first positional (string): " << allArgs["first"] << endl;
    std::cout << "second positional (string): " << allArgs["second"] << endl;
    std::cout << "firstkw (string): " << allArgs["firstkw"] << endl;
    std::cout << "secondkw (string): " << allArgs["secondkw"] << endl;
    std::cout << "flag1 string: " << allArgs["flag1"] << endl;
    int kw1 = ap.getArg<int>("firstkw"); // get individual arguments as int, float or string types
    
    float p1 = ap.getArg<float>("first");
    vector<string> p2 = ap.getVectorArg<string>("second");
    vector<float> kw3 = ap.getVectorArg<float>("kw3");
    bool flag1 = ap.getFlag("flag1");
    #ifdef MULTIARGS
    vector<string> multiPos = ap.getMultiArgs();
    #endif
    std::cout << "firstkw (int): " << kw1 << endl;
    std::cout << "first positional (float): " << p1 << endl;
    std::cout << "firstkw + first positional: " << kw1 + p1 << endl;
    std::cout << "p2 unpacked:\n";
    for (string item : p2){
    std::cout << '\t' << item << endl;
    }
    std::cout << "kw3 unpacked:\n";
    for (float item : kw3){
        std::cout << '\t' << item << endl;
    }
    std::cout << "flag1: " << flag1 << endl;
    #ifdef MULTIARGS
    std::cout << "multi positional aguments\n";
    for (string item : multiPos){
        std::cout << '\t' << item << '\n';
    }
    #endif
}