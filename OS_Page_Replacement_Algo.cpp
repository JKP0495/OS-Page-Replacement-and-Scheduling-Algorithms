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
public:
    static vector<pair<input *, output *>> hist;
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

    analyze(int noOfProcess, int RAMSize, int processSize);

public:
    static analyze *createAnalyze(int noOfProcess, int RAMSize, int processSize, int pageSize);

private:
    void runProcesses();

private:
    void updateOutput();

private:
    void mergeOutput(vector<int> curOutput);
};

class process
{
    int noOfRAMPages;
    int noOfpages;
    vector<int> pageID; // randomly generated, with length predefined

    process(int noOfPages, int noOfRAMPages, vector<int> pageID);

public:
    static process *createProcess(int noOfPages, int noOfRAMPages);

public:
    vector<int> runProcess();
};

class RAM
{
    int noOfRAMPages;
    int noOfpages;
    vector<int> pageID;

public:
    static int processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID);
};

class algoData
{
public:
    function<RAM *(int, int, vector<int>)> createFunction;
    int algoID;
};

// input
class input
{
    int RAMSize;
    int noOfProcess;
    int processSize;
    input(int RAMSize, int noOfProcess, int processSize);

public:
    static void getInput();
};

// Defination of Functions

// input class
input::input(int RAMSize, int noOfProcess, int processSize)
{
    this->RAMSize = RAMSize;
    this->noOfProcess = noOfProcess;
    this->processSize = processSize;
}
void input::getInput()
{
    int RAMSize;
    int noOfProcess;
    int processSize;
    cout << "Enter the number of processes on which you want to test the compatability of different algorithms" << endl;
    cin >> noOfProcess;
    cout << "Enter the RAM size for which you want to test the compatability of different algorithms" << endl;
    cin >> RAMSize;
    cout << "Enter the size of the process on which you want to test the compatability of different algorithms" << endl;
    cin >> processSize;
    history::hist.push_back(new input(RAMSize, noOfProcess, processSize), NULL);
}

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
    return new analyze(noOfProcess,noOfPages,noOfRAMPages);
}

void analyze::runProcesses()
{
    for(int i=0;i<noOfProcess;i++){
        process* curProcess=process::createProcess(noOfPages,noOfRAMPages);
        vector<int> curOutput=curProcess->runProcess();
        mergeOutput(curOutput);
    }
}

void analyze::mergeOutput(vector<int> curOutput){
    for(int i=0;i<curOutput.size();i++){
        if(this->curOutput.size()>i){
            this->curOutput[i]+=curOutput[i];
        }
        else{
            this->curOutput.push_back(curOutput[i]);
        }
    }
}

// Process class

process::process(int noOfPages, int noOfRAMPages, vector<int> pageID)
{
    this->noOfpages = noOfPages;
    this->noOfRAMPages = noOfRAMPages;
    this->pageID = pageID;
}

process *process::createProcess(int noOfPages, int noOfRAMPages)
{
    vector<int> pageID;
    int noOfBlocks = 10 * noOfPages;
    for (int i = 0; i < noOfBlocks; i++)
    {
        int pid = (rand() % noOfPages) + 1;
        pageID.push_back(pid);
    }
    return new process(noOfPages, noOfRAMPages, pageID);
}

vector<int> process::runProcess()
{
    vector<int> processOutput;
    for (auto it : mapping)
    {
        RAM *process = it.second.createFunction(noOfpages,noOfRAMPages,pageID);
        processOutput.push_back(process->processRAM(noOfpages, noOfRAMPages, pageID));
    }
    return processOutput;
}

int main()
{

    return 0;
}