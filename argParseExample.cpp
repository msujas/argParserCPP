#include <iostream>
#include "argParser.h"
#include <map>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){
    ArgParser ap;
    ap.addPositional("first", "1", "the first positional argument"); //args - name, default value (string, default: "")
    ap.addPositional("second","2", "the second positional argument");
    ap.addKW("firstkw","3", "fkw", "the first keyword argument"); // args - long name, default value (string, default: ""), short name (default: long name)
    ap.addKW("secondkw","4", "", "the second keyword argument");
    ap.addKW("kw3","5", "", "the third keyword argument");
    ap.addFlag("flag1",true, "f1","flag argument");
    ap.readArguments(argc,argv);
    map<string,string> allArgs = ap.getAllArgs(); //returns map of all arguments with long names as strings

    cout << "first positional: " << allArgs["first"] << endl;
    cout << "second positional: " << allArgs["second"] << endl;
    cout << "firstkw: " << allArgs["firstkw"] << endl;
    cout << "secondkw: " << allArgs["secondkw"] << endl;
    cout << "flag1 string: " << allArgs["flag1"] << endl;
    int kw1 = ap.getArg<int>("firstkw"); // get individual arguments as int, float or string types
    float p1 = ap.getArg<float>("first");
    vector<string> p2 = ap.getVectorArg<string>("second");
    vector<float> kw3 = ap.getVectorArg<float>("kw3");
    bool flag1 = ap.getFlag("flag1");
    cout << kw1 << endl;
    cout << p1 << endl;
    cout << kw1 + p1 << endl;
    cout << "p2 unpacked:\n";
    for (string item : p2){
    cout << item << endl;
    }
    cout << "kw3 unpacked:\n";
    for (float item : kw3){
        cout << item << endl;
    }
    cout << "flag1: " << flag1 << endl;
}