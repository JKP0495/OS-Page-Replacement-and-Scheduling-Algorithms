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
    static vector<pair<input *, output *>>
        hist;
};

class handler
{
    int RAMSize;
    int noOfProcess;
    int processSize;

    handler(int RAMSize, int noOfProcess, int processSize);

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

private:
    input *getInput();

public:
    static void createHistory();

public:
    int getRAMSize();
    
public:
    int getNoOfProcess();
    
public:
    int getProcessSize();
};

class output
{
    vector<int> mainOutput;
    output();

private:
    void mergeOutput(vector<int> curOutput);

public:
    static output *getOutput();

};

// Defination of Functions

// output class

output::output()
{
}

output *output::getOutput()
{
    return new output();
}

void output::mergeOutput(vector<int> curOutput)
{
    for (int i = 0; i < curOutput.size(); i++)
    {
        if (this->mainOutput.size() > i)
        {
            this->mainOutput[i] += curOutput[i];
        }
        else
        {
            this->mainOutput.push_back(curOutput[i]);
        }
    }
}

// input class
input::input(int RAMSize, int noOfProcess, int processSize)
{
    this->RAMSize = RAMSize;
    this->noOfProcess = noOfProcess;
    this->processSize = processSize;
}

input *input::getInput()
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
    return new input(RAMSize, noOfProcess, processSize);
}

void input::createHistory()
{
    input *in = getInput();
    output *out = output::getOutput();
    history::hist.push_back({in, out});
}

int input::getRAMSize(){
    return this->RAMSize;
}

int input::getNoOfProcess(){
    return this->noOfProcess;
}

int input::getProcessSize(){
    return this->processSize;
}

// Handler Class

handler::handler(int RAMSize, int noOfProcess, int processSize){
    this->RAMSize=RAMSize;
    this->noOfProcess=noOfProcess;
    this->processSize=processSize;
}

handler *handler::createHandler(){
    input *curInput=history::hist.back().first;
    return new handler(curInput->getRAMSize(),curInput->getNoOfProcess(),curInput->getProcessSize());
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
    return new analyze(noOfProcess, noOfPages, noOfRAMPages);
}

void analyze::runProcesses()
{
    for (int i = 0; i < noOfProcess; i++)
    {
        process *curProcess = process::createProcess(noOfPages, noOfRAMPages);
        vector<int> curOutput = curProcess->runProcess();
        output *mainOutput = history::hist.back().second;
        mainOutput->mergeOutput(curOutput);
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
        RAM *process = it.second.createFunction(noOfpages, noOfRAMPages, pageID);
        processOutput.push_back(process->processRAM(noOfpages, noOfRAMPages, pageID));
    }
    return processOutput;
}

int main()
{

    return 0;
}