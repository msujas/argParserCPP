#include <iostream>
#include "main/argParser.cpp"
#include <map>

using namespace std;

int main(int argc, char *argv[]){
    ArgParser ap;
    ap.addPositional("first", "1"); //args - long name, default value (string, default: "")
    ap.addPositional("second","2");
    ap.addKW("firstkw","3", "fkw"); // args - long name, default value (string, default: ""), short name
    ap.addKW("secondkw","4");
    ap.readArguments(argc,argv);
    map<string,string> allArgs = ap.getAllArgs(); //returns map of all arguments with long names as strings

    cout << "first positional: " << allArgs["first"] << endl;
    cout << "second positional: " << allArgs["second"] << endl;
    cout << "firstkw: " << allArgs["firstkw"] << endl;
    cout << "secondkw: " << allArgs["secondkw"] << endl;
    int firstkw = ap.getArg<int>("firstkw"); // get individual arguments as int, float or string types
    float firstPos = ap.getArg<float>("first");
    vector<string> secondPos = ap.getVectorArg<string>("second");
    cout << firstkw << endl;
    cout << firstPos << endl;
    cout << firstkw + firstPos << endl;
    for (string item : secondPos){
    cout << item << endl;
    }
    
}