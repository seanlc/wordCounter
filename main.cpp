#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

int main()
{
        string word;    // string will which hold raw text input
        string word2 = "";  //string will which hold formatted words
        map<string,int> wordBank; // map where the string is the key and frequency int is the value
        map<int,vector<string> > frequencyBank; // map where the frequency int is key and string is the value
        ifstream inputFile("/home/sean/Desktop/my CS2 workplace/moby10b.txt"); // defining file to be used as input as ifstream
        ofstream outputFile("/home/sean/Desktop/my CS2 workplace/mobydata.txt"); // defining output file for the frequencyBank
        if (inputFile)      //code will run if innputFile opens the indicated file successfully
        {
            while (!inputFile.eof())    // while the end of the input file has not been reached
            {
                inputFile >> word;  // gets input from inputFile and puts it in string word
                for (int i = 0; i < word.length(); i++) // loop through each character of string word
                {
                    word[i] = tolower(word[i]);     // change character to lowercase
                    if (!ispunct(word[i]))
                    {
                        word2.push_back(word[i]);   // if the character is not punctuation, add it to a second string word2
                    }
                }
                if (wordBank.find(word2) != wordBank.end())     // if string word2 is found in wordBank map
                {
                    wordBank[word2]++;  // increment the count integer value
                } else                  // if string word2 is not found in wordBank map
                {
                    wordBank.insert({word2,1}); // insert word2 into wordBank map and assign it an initial value of integer 1
                }
                word2 = "";     // change the value of word2 to an empy string
            }
            string word3 = "";      // define new empty string to be used while iterating through wordBank map
            int frequency = 0;      // define new integer value of zero to be used while iterating through wordBank map

            for (map<string,int>::iterator i = wordBank.begin(); i != wordBank.end(); i++)  // loop initialization to go from beginning of the map to the end
            {
                word3 = i->first;   // change the value of string word3 to the key in the map entry
                frequency = i->second;  // change the value of int frequency to the value in the map entry
                if (frequencyBank.find(frequency) != frequencyBank.end())   // if int frequency is already a key in the frequencyBank map
                {
                    frequencyBank[frequency].push_back(word3);  // add string word3 to the vector of values associated with key int frequency
                } else      // if int frequency is not already a key in frequencyMap map
                {
                    vector<string> words;   // create a new string vector to be used as the value for the new entry
                    words.push_back(word3); // add string word3 to this newly created vector
                    frequencyBank.insert({frequency, words});   // insert a new entry into map frequencyBank with int frequency as key and string vector words as value
                }
            }
        }
        else
        {
            cout << "There was an error opening the file" << endl; // code that will run if there is a file input error
            return 0; // to end to the program
        }

        outputFile << "word \t\t frequency" << endl; // formatting for wordBank output file
        for (map<string,int>::iterator i = wordBank.begin(); i != wordBank.end(); i++)
        {
            outputFile << i->first << "\t\t\t" << i->second << endl; // writes a line for each entry in wordBank with key and value
        }
        outputFile.close(); // close wordBank output file
        ofstream secondoutputFile("/home/sean/Desktop/my CS2 workplace/mobywordfreq.txt");   // create a new output file to be filled with the contents of the frequencyBank
        secondoutputFile << "----------------------------------------" << endl; // formatting for frequencyBank output file
        secondoutputFile << "Frequency Bank" << endl;
        int wordCount = 0;
        for (map<int,vector<string> >::iterator n = frequencyBank.begin(); n != frequencyBank.end(); n++)
        {       // loop iterates through each entry in frequencyBank, starting at beginning and finishing at the end
            secondoutputFile << n->first << endl;   // write the integer key value to file
            for (int i = 0; i < n->second.size(); i++)
            {   // loop through the string vector that is value for map entry
                secondoutputFile << n->second[i] << ", ";   // write string in vector to file
                if (i % 3 == 0)
                {
                    secondoutputFile << endl;   // formatting
                }
            }
            secondoutputFile << endl << endl;       // formatting
        }
        cout << "File analysis complete" << endl;
        inputFile.close();  // close inputFile
        secondoutputFile.close();   // close secondoutputFile

    return 0;
}
