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
class FIFO;

// Defination of Classes
class history
{
private
    static history *currentInstance;

public:
    static vector<pair<input *, output *>> hist;
    // deleting copy constructor
    history(const history &obj) = delete;
    static history *getInstance();
    void updateHistory(input *in, output *out);
    pair<input *, output *> getLastElement();
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

public:
    void runProcesses();

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
    RAM(int noOfRAMPages, int noOfpages, vector<int> pageID);

public:
    virtual int processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) = 0;
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

public:
    void printData();
};

class output
{
    vector<vector<int>> mainOutput;
    output();

public:
    void mergeOutput(vector<int> curOutput);

public:
    static output *getOutput();

public:
    void printData();
};

class FIFO : public RAM
{

public:
    FIFO(int noOfRAMPages, int noOfpages, vector<int> pageID) : RAM(noOfRAMPages, noOfpages, pageID){};

public:
    int processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) override;
};

// Mapping of algo to its name
map<string, algoData *> mapping = {
    {"FIFO", new algoData([&](int noOfRAMPages, int noOfpages, vector<int> pageID)
                          { return new FIFO(noOfRAMPages, noOfpages, pageID); }, 1)}};

// Defination of Functions

// history class
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

void output::mergeOutput(vector<int> curOutput)
{
    this->mainOutput.push_back(curOutput);
}

void output::printData()
{
    // Naisheel please complete this
    // This function prints output(analyzed) data given to it for final print of output
    cout << "HI" << endl;
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
    history::hist.push_back({in, out});
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

void input::printData()
{
    // Naisheel please complete this
    // This function prints input data given to it for final print of output
    cout << "HI" << endl;
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
    input *curInput = history::hist.back().first;
    return new handler(curInput->getRAMSize(), curInput->getNoOfProcess(), curInput->getProcessSize());
}

void handler::analyzeOnAllPageSize()
{
    for (int curPageSize = 0; curPageSize < processSize; curPageSize++)
    {
        analyze *curAnalyze = analyze::createAnalyze(noOfProcess, RAMSize, processSize, curPageSize);
        curAnalyze->runProcesses();
    }
}

void handler::printAnalyzedData()
{
    input *mainInput = history::hist.back().first;
    output *mainOutput = history::hist.back().second;

    // Prints input data
    mainInput->printData();

    // Prints input data
    mainOutput->printData();
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
        mergeOutput(curOutput);
    }
    output *mainOutput = history::hist.back().second;
    mainOutput->mergeOutput(this->curOutput);
}

void analyze::mergeOutput(vector<int> curOutput)
{
    for (int i = 0; i < curOutput.size(); i++)
    {
        if (this->curOutput.size() > i)
        {
            this->curOutput[i] += curOutput[i];
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
        RAM *process = it.second->createFunction(noOfpages, noOfRAMPages, pageID);
        processOutput.push_back(process->processRAM(noOfpages, noOfRAMPages, pageID));
    }
    return processOutput;
}

// RAM class

RAM::RAM(int noOfRAMPages, int noOfpages, vector<int> pageID)
{
    this->noOfpages = noOfpages;
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
int FIFO::processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID)
{
    int missCount = 0;
    set<int> chachedPages;
    queue<int> inOrder;
    for (int i = 0; i < pageID.size(); i++)
    {
        if (!chachedPages.count(pageID[i]))
        {
            missCount++;
            chachedPages.erase(inOrder.front());
            inOrder.pop();
            chachedPages.insert(pageID[i]);
            inOrder.push(pageID[i]);
        }
    }
}

int main()
{

    return 0;
}