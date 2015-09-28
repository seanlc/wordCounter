#include "wordCounter.h"

wordCounter::wordCounter()
{
    inputFile.open("C:/Users/Sandy/Desktop/Data Structures/2701.txt");
    outputFile.open("C:/Users/Sandy/Desktop/Data Structures/2701output.txt");
}

wordCounter::~wordCounter()
{
    inputFile.close();
    outputFile.close();
}
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

        outputFile << endl << endl << endl;
        outputFile << "Frequency Bank" << endl;
        for (map<int,vector<string> >::iterator i = frequencyCollection.end(); i != frequencyCollection.begin(); i--)
        {
            outputFile << i->first << endl;
            vectorSize = i->second.size();
            for (int n = 0; n < vectorSize; n++)
            {
                outputFile << i->second[n] << ", ";
                if (n % 3)
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
