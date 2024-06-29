#include <vector>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

class ArgParser{
    private:
    vector<string> kwargs;
    vector<string> shortKwargs;
    map<string, string> kwargValues;
    vector<string> posArgs;
    map<string, string> posValues;
    map<string,string> allValues;
    public:
    void addKW(const string fullName,string defaultValue = "", string shortName = ""){
        if (shortName == ""){
            shortName = fullName;
        }
        shortKwargs.push_back(shortName);
        kwargs.push_back(fullName);
        kwargValues[fullName] = defaultValue;
        allValues[fullName] = defaultValue;
    }
    void addPositional(const string name, string defaultValue = ""){
        posArgs.push_back(name);
        posValues[name] = defaultValue;
        allValues[name] = defaultValue;
    }
    void readArguments(int argc, char *argv[]){
        vector<int> kwargPositions;
        vector<int> paPositions;
        
        bool inKW = false;
        for (int i = 1; i < argc; i++){
            if (inKW){
                inKW = false;
                continue;
            }
            inKW = false;
            for (int j = 0; j < kwargs.size();j++){
                string kw = kwargs[j];
                string skw = shortKwargs[j];
                if (argv[i] == "--"+kw | argv[i] == "-"+skw){
                    kwargValues[kw] = argv[i+1];
                    kwargPositions.push_back(i);
                    kwargPositions.push_back(i+1);
                    allValues[kw] = argv[i+1];
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
        istringstream iss (stringValue);
        T argValue;
        iss >> argValue;
        if (iss.fail()){
            cout << "Error: type conversion failed for argument: " << name << endl ;
            throw invalid_argument("type conversion failed");
        }
        return argValue;
    }
};