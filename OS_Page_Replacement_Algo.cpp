#include <bits/stdc++.h>
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

const map<string, algoData *> mapping = {};

// Defination of Classes
class history
{
    vector<pair<input *, output *>> hist;
};

class handler
{
    int RAMSize;
    int noOfProcess;
    int processSize;

public:
    static handler *createHandler();

private:
    void analyzeOnAllPageSize();

private:
    void printAnalyzedData();
};

class analyze
{
    int noOfProcess;
    int noOfPages;
    int noOfRAMPages;
    vector<int> curOutput;

    analyze(int noOfProcess, int noOfPages, int noOfRAMPages);

public:
    static analyze *createAnalyze(int noOfProcess, int RAMSize, int processSize, int pageSize);

private:
    void runProcesses();

private:
    void updateOutput();

private:
    void mergeOutput(vector<int> newOutput);
};

class process
{
    int noOfRAMPages;
    int noOfpages;
    vector<int> pageID; // randomly generated, with length predefined

public:
    static process* createProcess(int noOfPages, int noOfRAMPages);

public:
    vector<int> runProcess();
};

class RAM
{
    int noOfRAMPages;
    int noOfpages;
    vector<int> pageID;

public:
    static int processRAM(int noOfPages, int noOfRAMPages);
};

class algoData
{
public:
    function<RAM *(int, int, vector<int>)> createFunction;
    int algoID;
};

// Defination of Functions

// Analyze Class

analyze::analyze(int noOfProcess, int noOfPages, int noOfRAMPages)
{
    this->noOfProcess = noOfProcess;
    this->noOfPages = noOfPages;
    this->noOfRAMPages = noOfRAMPages;
}

analyze *analyze::createAnalyze(int noOfProcess, int RAMSize, int processSize, int pageSize)
{
    int noOfPages = ((processSize + pageSize - 1) / pageSize);
    int noOfRAMPages = ((RAMSize + pageSize - 1) / pageSize);
    return new analyze(noOfProcess, noOfPages, noOfRAMPages);
}

void analyze::runProcesses(){
    int processRemaining=noOfProcess;
    while(processRemaining--){
        process* curProcess=process::createProcess(noOfPages,noOfRAMPages);
        vector<int> newOutput=curProcess->runProcess();
        this->mergeOutput(newOutput);
    }
}

void analyze::mergeOutput(vector<int> newOutput){
    for(int i=0;i<newOutput.size();i++){
        curOutput[i]+=newOutput[i];
    }
}


int main()
{
    return 0;
}