#include <vector>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

bool isIn(string s, string pattern){
    if (s.find(pattern)!= -1){
        return true;
    }
    else {
        return false;
    }
}

vector<string> splitString(string inputString, string delimiter=","){
    int pos;
    string substring;
    vector<string> outVector;
    string  tempString = inputString;
    if (delimiter ==" "){
        while (isIn(tempString,"  ")){ // check if 2 consecutive spaces in string, replace with 1
            tempString = tempString.replace(tempString.find("  "),2," ");
        }
        if (tempString.find(" ") == 0){
            tempString = tempString.replace(0,1,"");
        }
    }
    while (true){
        pos = tempString.find(delimiter);
        substring = tempString.substr(0,pos);
        outVector.push_back(substring);
        if (tempString.find(delimiter) == -1){
            break;
        }
        tempString.erase(0,pos+delimiter.length());    
    }
    return outVector;
}

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
        vector<int> paPositions;
        bool inKW = false;
        for (int i = 1; i < argc; i++){
            inKW = false;
            for (int j = 0; j < kwargs.size();j++){
                string kw = kwargs[j];
                string skw = shortKwargs[j];
                if (argv[i] == "--"+kw | argv[i] == "-"+skw){
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