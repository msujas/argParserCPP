#include <vector>
#include <iostream>
#include <map>
#include <sstream>
#ifndef stringFunctions
#include "include/stringFunctions.cpp"
#include "stdlib.h"
#endif

using namespace std;



template<typename T>
T convertString(const string& stringValue){
    istringstream iss (stringValue);
    T outValue;
    iss >> outValue;
    if (iss.fail()){
        cout << "Error: type conversion failed for argument: " << stringValue << endl ;
        throw invalid_argument("type conversion failed");
    }
    return outValue;
}

class ArgParser{
    private:
    vector<string> kwargs;
    vector<string> shortKwargs;
    map<string, string> kwargValues;
    vector<string> posArgs;
    vector<string> allArgs;
    map<string, string> posValues;
    map<string,string> allValues;
    map<string, vector<string>> multiValues;
    string helpString;
    map<string,string> argHelpStrings;
    void checkArgs(string name){
        for (string arg: allArgs){
            if (name == arg){
                cout << "Error: '"+name +"' is declared more than once\n";
                throw runtime_error("is declared more than once");
            }
        }
    }

    public:
    ArgParser(){
        addKW("help", "", "h", "display this help message");
    }
    void addKW(const string fullName,string defaultValue = "", string shortName = "", string help = ""){
        checkArgs(fullName);
        if (shortName == ""){
            shortName = fullName;
        }
        shortKwargs.push_back(shortName);
        kwargs.push_back(fullName);
        kwargValues[fullName] = defaultValue;
        allValues[fullName] = defaultValue;
        allArgs.push_back(fullName);
        argHelpStrings[fullName] = help;
    }
    void addPositional(const string name, string defaultValue = "", string help = ""){
        checkArgs(name);
        posArgs.push_back(name);
        posValues[name] = defaultValue;
        allValues[name] = defaultValue;
        allArgs.push_back(name);
        argHelpStrings[name] = help;
        }
    void addMultiPositional(const string name, const int length = 1){
        allArgs.push_back(name);
        /*
        for (int i; i < length; i++){
            posArgs.push_back(name);
        }
        */
    }
    void readArguments(int argc, char *argv[]){
        vector<int> paPositions;
        bool inKW = false;
        string filename = argv[0];
        helpString = "usage: " + filename +" ";
        for (int i=0; i < kwargs.size();i++){
            helpString += "[--"+kwargs[i]+"/-"+ shortKwargs[i] + "] ";
        }
        for (string arg : posArgs){
            helpString += "<"+ arg + "> ";
        }
        helpString += "\n---------\n\nkey word arguments:\n\n";

        for (int i=0; i< kwargs.size(); i++){
            helpString += "--"+kwargs[i]+"/-"+shortKwargs[i] + ": " + argHelpStrings[kwargs[i]] + "\n";
        }
        helpString += "\npositional arguments:\n\n";
        for (string arg : posArgs){
            helpString += arg + ": " + argHelpStrings[arg] + "\n";
        }
        helpString += "\n";
        for (int i = 1; i < argc; i++){
            inKW = false;
            string argument = argv[i];
            if (argument == "--help" | argument == "-h" ){
                cout << helpString;
                exit(0);
            }
            for (int j = 0; j < kwargs.size();j++){
                string kw = kwargs[j];
                string skw = shortKwargs[j];
                if (argument == "--"+kw | argument == "-"+skw){
                    kwargValues[kw] = argv[i+1];
                    allValues[kw] = argv[i+1];
                    i++;
                    inKW = true;
                    break;
                }
            }
            if (!inKW){
                paPositions.push_back(i);
            }
        }
        if (paPositions.size() > posArgs.size()){
            cout << "warning: number of given arguments greater than number registered\n";
        }
        for (int i = 0; i < paPositions.size(); i++){
            if (i > posArgs.size()-1){
                break;
            }
            posValues[posArgs[i]] = argv[paPositions[i]];
            allValues[posArgs[i]] = argv[paPositions[i]];
        }


    }

    map<string, string> getAllArgs(){
        return allValues;
    }

    template<typename T>
    T getArg(const string& name){
        const string stringValue = allValues[name];
        T argValue = convertString<T>(stringValue);
        return argValue;
    }

    template<typename T2>
    vector<T2> getVectorArg(const string& name){
        const string stringValue = allValues[name];
        vector<string> stringSplit = splitString(stringValue);
        vector<T2> outVector;
        for (string s : stringSplit){
            T2 item = convertString<T2>(s);
            outVector.push_back(item);
        }
        return outVector;
    }
};