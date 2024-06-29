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
    void addKW(string fullName,string defaultValue = "", string shortName = ""){
        if (shortName == ""){
            shortName = fullName;
        }
        shortKwargs.push_back(shortName);
        kwargs.push_back(fullName);
        kwargValues[fullName] = defaultValue;
        allValues[fullName] = defaultValue;
    }
    void addPositional(string name, string defaultValue = ""){
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

    map<string, string> getAllPositionalArgs(){
        return posValues;
    }
    map<string, string> getAllKWs(){
        return kwargValues;
    }
    template<typename T>
    T getArg(const string& name){
        const string stringValue = allValues[name];
        istringstream iss (stringValue);
        T argValue;
        iss >> argValue;
        if (iss.fail()){
            cout << "type conversion failed\n";
            throw invalid_argument("type conversion failed");
        }
        return argValue;
    }
};

int main(int argc, char *argv[]){
    ArgParser ap;
    ap.addPositional("first", "1");
    ap.addPositional("second","2");
    ap.addKW("firstkw","3");
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
    cout << firstkw << endl;
    cout << firstPos << endl;
    cout << firstkw + firstPos << endl;

}