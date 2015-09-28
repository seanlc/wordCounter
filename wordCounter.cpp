#include "wordCounter.h"

///********************************
///Function: Constructor
///Task:   creates wordCounter object and prepares input and output files for use
///Returns: nothing
///********************************
wordCounter::wordCounter()
{
    inputFile.open("C:/Users/Sandy/Desktop/Data Structures/2701.txt");
    outputFile.open("C:/Users/Sandy/Desktop/Data Structures/2701output.txt");
}
///********************************
///Function: Destructor
///Task:   closes input and output files
///Returns: nothing
///********************************
wordCounter::~wordCounter()
{
    inputFile.close();
    outputFile.close();
}
///********************************
///Function: writeOutputFile
///Task:   Writes the data within the two maps into separate files
/// 2701output.txt: alphabetical list of each word used within the input file along with the frequency of use
/// 2701outputfrequency.txt: list of frequencies along with associated words, descending order
///Returns: true if the outputFile stream was accessed successfully, false otherwise
///********************************
bool wordCounter::writeOutputFile()
{
    int vectorSize;
    if (outputFile)
    {
        outputFile << "Word \t\t frequency" << endl;
        for (map<string, int>::iterator i = wordCollection.begin(); i != wordCollection.end(); i++)
        {
            outputFile << i->first << "\t\t\t" << i->second << endl;
        }

        outputFile.close();
        outputFile.open("C:/Users/Sandy/Desktop/Data Structures/2701frequencyoutput.txt");

        outputFile << "Frequency Bank" << endl;
        for (map<int,vector<string> >::iterator i = frequencyCollection.end(); i != frequencyCollection.begin(); i--)
        {
            if (i == frequencyCollection.end())
            {
                i++;    /// skip last entry since it contains garbage instead of a valid entry
            }
            outputFile << i->first << endl;
            vectorSize = i->second.size();
            for (int n = 0; n < vectorSize; n++)
            {
                outputFile << i->second[n];
                if(n != (vectorSize - 1))
                {
                    outputFile << ", ";
                }
                if ( ((n+1) % 5 == 0) and n != (vectorSize - 1))
                {
                    outputFile << endl;
                }
            }
            outputFile << endl << endl;
        }

        return true;
    }
    cout << "There was an error opening the output file" << endl;
    return false;
}
///********************************
///Function: fillWordCollection
///Task: fills the wordCollection map with every word used in the input file along with the associated frequency
/// get one string at a time from .txt file using >> operator
/// format strings to remove capitalization and punctuation before checking against wordCollection map
///Returns: true if inputFile is accessed successfully, false otherwise
///********************************
bool wordCounter::fillWordCollection()
{
    string rawWord;
    string formattedWord = "";
    int wordLength;
    if (inputFile)
    {
        while (!inputFile.eof())
        {
            inputFile >> rawWord;
            wordLength = rawWord.length();
            for (int i = 0; i < wordLength; i++)
            {
                rawWord[i] = tolower(rawWord[i]);
                if(!ispunct(rawWord[i]))
                {
                    formattedWord.push_back(rawWord[i]);
                }
            }
            if (wordCollection.find(formattedWord) != wordCollection.end() )
            {
                wordCollection[formattedWord]++;
            }
            else
            {
                wordCollection[formattedWord] = 1;
            }
            formattedWord = "";
        }
        fillFreqCollection();
        return true;
    }
    cout << "Error opening inputFile" << endl;
    return false;
}
///********************************
///Function: fillFreqCollection
///Task:   fills the frequencyCollection map using the frequencies stored in wordCollection map
///Returns: nothing
///********************************
void wordCounter::fillFreqCollection()
{
    string word;
    int frequency;
    for (map<string,int>::iterator i = wordCollection.begin(); i != wordCollection.end(); i++)
    {
        word = i->first;
        frequency = i->second;
        if (frequencyCollection.find(frequency) != frequencyCollection.end())
        {
            frequencyCollection[frequency].push_back(word);
        }
        else
        {
            vector<string> words;
            words.push_back(word);
            frequencyCollection[frequency] = words;
        }
    }
}
