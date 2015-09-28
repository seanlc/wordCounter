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
        wordCounter();              /// constructor
        virtual ~wordCounter();     /// destructor
        bool writeOutputFile();     /// writes the contents of wordCollection and frequencyCollection to separate files
        bool fillWordCollection();  /// fills wordCollection map with each word in inputFile along with frequency
        void fillFreqCollection();  /// fills frequency collection using the data stored in word collection
    protected:
    private:
        map<string, int> wordCollection;                /// map with words as key and frequency of use as value
        map<int,vector<string> > frequencyCollection;   /// map with frequency as key and string vector of words as value
        ifstream inputFile;                 /// input stream that will be used to populate wordCollection
        ofstream outputFile;                /// output stream that will be used to write two output files
};

#endif // WORDCOUNTER_H
