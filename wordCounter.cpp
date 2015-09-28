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
        outputFile << "Word \t\t frequency" << endl;        /// formatting for wordCollection file listing
        for (map<string, int>::iterator i = wordCollection.begin(); i != wordCollection.end(); i++)
        {
            /// list every entry in wordCollection along with the frequency
            outputFile << i->first << "\t\t\t" << i->second << endl;
        }
        /// close first output file and open second that will be used to store frequencyCollection
        outputFile.close();
        outputFile.open("C:/Users/Sandy/Desktop/Data Structures/2701frequencyoutput.txt");
        /// formatting for frequencyCollection file listing
        outputFile << "Frequency Bank" << endl;
        for (map<int,vector<string> >::iterator i = frequencyCollection.end(); i != frequencyCollection.begin(); i--)
        {
            if (i == frequencyCollection.end())
            {
                i++;    /// skip last entry since it contains garbage instead of a valid entry
            }
            /// write frequency
            outputFile << i->first << endl;
            vectorSize = i->second.size();
            /// loop through the string vector and write each string associated with current frequency
            for (int n = 0; n < vectorSize; n++)
            {
                outputFile << i->second[n];
                if(n != (vectorSize - 1))
                {
                    outputFile << ", ";     /// add comma if string is not last element in vector
                }
                if ( ((n+1) % 5 == 0) and n != (vectorSize - 1))
                {
                    outputFile << endl;     /// formatting to make results more readable
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
        while (!inputFile.eof())    /// while end of the file has not been reached
        {
            inputFile >> rawWord;   /// take one word at time into rawWord string
            wordLength = rawWord.length();
            for (int i = 0; i < wordLength; i++)
            {
                rawWord[i] = tolower(rawWord[i]);       /// convert word to lowercase
                if(!ispunct(rawWord[i]))
                {
                    formattedWord.push_back(rawWord[i]);    /// push non-punctuation character onto formattedWord string
                }
            }
            if (wordCollection.find(formattedWord) != wordCollection.end() )
            {
                wordCollection[formattedWord]++;        /// increment value associated with word if word is already in wordCollection
            }
            else
            {
                wordCollection[formattedWord] = 1;      /// create a new entry if word is not already in collection
            }
            formattedWord = "";         /// reset formatted word to empty string for next iteration of loop
        }
        fillFreqCollection();           /// fill frequencyCollection using the data stored in wordCollection
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
        /// set word and frequency variables to appropriate values based on entry pointed to by i in wordCollection
        word = i->first;
        frequency = i->second;
        if (frequencyCollection.find(frequency) != frequencyCollection.end())
        {
            frequencyCollection[frequency].push_back(word);
            /// if frequency is already present, add the word to the string vector associated with it
        }
        else
        {
            /// if frequency is not present, create a new string vector, add the word to the vector and create
            /// an entry in frequencyCollection with the frequency as the key and the string vector as the value
            vector<string> words;
            words.push_back(word);
            frequencyCollection[frequency] = words;
        }
    }
}
