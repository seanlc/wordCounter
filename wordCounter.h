#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class wordCounter
{
    public:
        wordCounter();
        virtual ~wordCounter();
        bool writeOutputFile();
        bool fillWordCollection();
        void fillFreqCollection();
    protected:
    private:
        map<string, int> wordCollection;
        map<int,vector<string> > frequencyCollection;
        ifstream inputFile;
        ofstream outputFile;
};

#endif // WORDCOUNTER_H
