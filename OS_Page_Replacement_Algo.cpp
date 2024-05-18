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
    vector<int> pageID;

    public: static void createProcess(int noOfPages,int noOfRAMPages);
    private: vector<int> runProcess();
};

class RAM{
    
};



// Defination of Functions




int main(){

    return 0;
}