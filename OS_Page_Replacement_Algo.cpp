#include<bits/stdc++.h>
using namespace std;

// Declaration of Classes
class history;
class handler;
class input;
class output;
class analyze;
class Process;
class RAM;
class algoData;

const map<string,algoData*> mapping = {
};


// Defination of Classes
class history{
    vector<pair<input*,output*>> hist;
};

class handler{
    int RAMSize;
    int noOfProcess;
    int processSize;

    public: static void createHandler();
    private: void analyzeOnAllPageSize();
    private: void printAnalyzedData();
};

class analyze{
    int pageSize;
    int noOfProcess;
    int noOfPages;
    int noOfRAMPages;
    vector<int> curOutput;

    public: static void createAnalyze(int noOfProcess,int RAMSize,int processSize,int pageSize);
    private: void runProcesses();
    private: void updateOutput();
};

class process{
    int noOfRAMPages;
    int noOfpages;
    vector<int> pageID;

    public: static void createProcess(int noOfPages,int processSize,int noOfRAMPages);
    private: vector<int> runProcess();
};

class RAM{
    int noOfRAMPages;
    int noOfpages;
    vector<int> pageID;

    public: static int processRAM(int noOfPages,int processSize,int noOfRAMPages);
};

class algoData{
    public:
    function<RAM*(int,int,vector<int>)> createFunction;
    int algoID;
};



// Defination of Functions




int main(){

    return 0;
}