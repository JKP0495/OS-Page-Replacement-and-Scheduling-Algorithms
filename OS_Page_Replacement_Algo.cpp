#include <bits/stdc++.h>
using namespace std;

const int MISS = 0;
const int TOTAL = 1;

// Declaration of Classes
class history;
class handler;
class input;
class output;
class analyze;
class Process;
class RAM;
class algoData;
class FIFO;

// Defination of Classes
class history
{
private:
    static history *currentInstance;
    vector<pair<input *, output *>> hist;

public:
    // deleting copy constructor
    // history(const history &obj) = delete;
    static history *getInstance();
    history(){};
    void updateHistory(input *in, output *out);
    pair<input *, output *> getLastElement();
    void printCurrentStats();
};

class handler
{
    int RAMSize;
    int noOfProcess;
    int processSize;

    handler(int RAMSize, int noOfProcess, int processSize);

public:
    static handler *createHandler();

public:
    void analyzeOnAllPageSize();

public:
    void printAnalyzedData();
};

class analyze
{
    int noOfProcess;
    int noOfPages;
    int noOfRAMPages;
    vector<vector<int>> curOutput;

    analyze(int noOfProcess, int RAMSize, int processSize);

public:
    static analyze *createAnalyze(int noOfProcess, int RAMSize, int processSize, int pageSize);

public:
    void runProcesses();

private:
    void mergeOutput(vector<vector<int>> curOutput);
};

class process
{
    int noOfRAMPages;
    int noOfPages;
    vector<int> pageID; // randomly generated, with length predefined

    process(int noOfPages, int noOfRAMPages, vector<int> pageID);

public:
    static process *createProcess(int noOfPages, int noOfRAMPages);

public:
    vector<vector<int>> runProcess();
};

class RAM
{
    int noOfRAMPages;
    int noOfPages;
    vector<int> pageID;

public:
    RAM(int noOfRAMPages, int noOfPages, vector<int> pageID);

public:
    virtual vector<int> processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) = 0;
};

class algoData
{

public:
    algoData(function<RAM *(int, int, vector<int>)> createFunction, int algoID);

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
    static input *getInput();

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
    output();

public:
    vector<vector<vector<int>>> mainOutput;

public:
    void mergeOutput(vector<vector<int>> curOutput);

public:
    static output *getOutput();
};

class FIFO : public RAM
{

public:
    FIFO(int noOfRAMPages, int noOfPages, vector<int> pageID) : RAM(noOfRAMPages, noOfPages, pageID){};

public:
    vector<int> processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) override;
};

// Mapping of algo to its name
map<string, algoData *> mapping = {
    {"FIFO", new algoData([&](int noOfRAMPages, int noOfPages, vector<int> pageID)
                          { return new FIFO(noOfRAMPages, noOfPages, pageID); }, 1)}};

// Defination of Functions

// history class

history *history::currentInstance = NULL;

void history::printCurrentStats()
{
    input *currInput = hist.back().first;
    output *currOutput = hist.back().second;

    cout << "Results for "<<"FIFO"<<":" << endl;
    cout << "Page size \t -> \t Hit rate" << endl;
    int n = currOutput->mainOutput.size();
    for (int i = 1; i < n; i++)
    {
        int total = currOutput->mainOutput[i][0][TOTAL];
        int miss = currOutput->mainOutput[i][0][MISS];
        cout << i+1 << "\t -> \t" << 1.0 * (total - miss) / total << endl;
    }
    
}

history *history::getInstance()
{
    if (currentInstance == NULL)
    {
        // We can access private members
        // within the class.
        currentInstance = new history();

        // returning the instance pointer
        return currentInstance;
    }
    else
    {
        return currentInstance;
    }
}

void history::updateHistory(input *in, output *out)
{
    hist.push_back({in, out});
}

pair<input *, output *> history::getLastElement()
{
    return hist.back();
}

// output class

output::output()
{
}

output *output::getOutput()
{
    return new output();
}

void output::mergeOutput(vector<vector<int>> curOutput)
{
    this->mainOutput.push_back(curOutput);
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
    input *in = input::getInput();
    output *out = output::getOutput();
    history *instance = history::getInstance();
    instance->updateHistory(in, out);
}

int input::getRAMSize()
{
    return this->RAMSize;
}

int input::getNoOfProcess()
{
    return this->noOfProcess;
}

int input::getProcessSize()
{
    return this->processSize;
}

// Handler Class

handler::handler(int RAMSize, int noOfProcess, int processSize)
{
    this->RAMSize = RAMSize;
    this->noOfProcess = noOfProcess;
    this->processSize = processSize;
}

handler *handler::createHandler()
{
    history *instance = history::getInstance();
    input::createHistory();
    input *curInput = instance->getLastElement().first;
    return new handler(curInput->getRAMSize(), curInput->getNoOfProcess(), curInput->getProcessSize());
}

void handler::analyzeOnAllPageSize()
{
    for (int curPageSize = 1; curPageSize <= processSize; curPageSize++)
    {
        analyze *curAnalyze = analyze::createAnalyze(noOfProcess, RAMSize, processSize, curPageSize);
        curAnalyze->runProcesses();
    }
}

void handler::printAnalyzedData()
{
    history *instance = history::getInstance();
    instance->printCurrentStats();
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
    int noOfPages = (pageSize == 0 ? -1 : ((processSize + pageSize - 1) / pageSize));
    int noOfRAMPages = (pageSize == 0 ? -1 : ((RAMSize + pageSize - 1) / pageSize));
    return new analyze(noOfProcess, noOfPages, noOfRAMPages);
}

void analyze::runProcesses()
{
    for (int i = 0; i < noOfProcess; i++)
    {
        process *curProcess = process::createProcess(noOfPages, noOfRAMPages);
        vector<vector<int>> curOutput = curProcess->runProcess();
        mergeOutput(curOutput);
    }
    history *instance = history::getInstance();
    output *mainOutput = instance->getLastElement().second;
    mainOutput->mergeOutput(this->curOutput);
}

void analyze::mergeOutput(vector<vector<int>> curOutput)
{
    for (int i = 0; i < curOutput.size(); i++)
    {
        if (this->curOutput.size() > i)
        {
            this->curOutput[i][TOTAL] += curOutput[i][TOTAL];
            this->curOutput[i][MISS] += curOutput[i][MISS];
        }
        else
        {
            this->curOutput.push_back(curOutput[i]);
        }
    }
}

// Process class

process::process(int noOfPages, int noOfRAMPages, vector<int> pageID)
{
    this->noOfPages = noOfPages;
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

vector<vector<int>> process::runProcess()
{
    vector<vector<int>> processOutput;
    for (auto it : mapping)
    {
        if(noOfPages == -1){
            processOutput.push_back({-1,-1});
            continue;
        }
        RAM *process = it.second->createFunction(noOfPages, noOfRAMPages, pageID);
        processOutput.push_back(process->processRAM(noOfPages, noOfRAMPages, pageID));
    }
    return processOutput;
}

// RAM class

RAM::RAM(int noOfRAMPages, int noOfPages, vector<int> pageID)
{
    this->noOfPages = noOfPages;
    this->noOfRAMPages = noOfRAMPages;
    this->pageID = pageID;
}

// algoData class

algoData::algoData(function<RAM *(int, int, vector<int>)> createFunction, int algoID)
{
    this->algoID = algoID;
    this->createFunction = createFunction;
}

// FIFO class
vector<int> FIFO::processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID)
{
    int missCount = 0;
    int total = pageID.size();
    set<int> chachedPages;
    queue<int> inOrder;
    for (int i = 0; i < pageID.size(); i++)
    {
        if (!chachedPages.count(pageID[i]))
        {
            missCount++;
            chachedPages.erase(inOrder.front());
            if(chachedPages.size() == noOfRAMPages)inOrder.pop();
            chachedPages.insert(pageID[i]);
            inOrder.push(pageID[i]);
        }
    }
    return {missCount,total};
}

int main()
{
    handler* run=handler::createHandler();
    run->analyzeOnAllPageSize();
    run->printAnalyzedData();
    return 0;
}