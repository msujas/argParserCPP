#include <iostream>
#include "main/argParser.cpp"
#include <map>

using namespace std;

int main(int argc, char *argv[]){
    ArgParser ap;
    ap.addPositional("first", "1");
    ap.addPositional("second","2");
    ap.addKW("firstkw","3", "fkw");
    ap.addKW("secondkw","4");
    ap.readArguments(argc,argv);
    map<string,string> allArgs = ap.getAllArgs();

    cout << "first positional: " << allArgs["first"] << endl;
    cout << "second positional: " << allArgs["second"] << endl;
    cout << "firstkw: " << allArgs["firstkw"] << endl;
    cout << "secondkw: " << allArgs["secondkw"] << endl;
    int firstkw = ap.getArg<int>("firstkw");
    float firstPos = ap.getArg<float>("first");
    string secondPos = ap.getArg<string>("second");
    cout << firstkw << endl;
    cout << firstPos << endl;
    cout << firstkw + firstPos << endl;
    cout << secondPos << endl;
}