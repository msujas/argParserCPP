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
    map<string,string> pas = ap.getAllPositionalArgs();
    map<string,string> kws = ap.getAllKWs();
    cout << pas["first"] << endl;
    cout << pas["second"] << endl;
    cout << "firstkw: " << kws["firstkw"] << endl;
    cout << "secondkw: " << kws["secondkw"] << endl;
    int firstkw = ap.getArg<int>("firstkw");
    float firstPos = ap.getArg<float>("first");
    string secondPos = ap.getArg<string>("second");
    cout << firstkw << endl;
    cout << firstPos << endl;
    cout << firstkw + firstPos << endl;
    cout << secondPos << endl;
}