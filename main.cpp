#include <iostream>
#include <fstream>
#include <map>
#include <cstdio>
#include <cctype>
#include <vector>

using namespace std;

int main()
{
        string word;
        string word2 = "";
        map<string,int> wordBank;
        map<int,vector<string> > frequencyBank;
        ifstream inputFile("/home/sean/Desktop/my CS2 workplace/345.txt");
        ofstream outputFile("/home/sean/Desktop/my CS2 workplace/draculadata.txt");
        if (inputFile)
        {
            cout << "file loaded successsfully" << endl;
            inputFile >> word;
            for (int i = 0; i < word.length(); i++)
            {
                word[i] = tolower(word[i]);
                if (!ispunct(word[i]))
                {
                    word2.push_back(word[i]);
                }
            }
            while (!inputFile.eof())
            {
                if (wordBank.find(word2) != wordBank.end())
                {
                    wordBank[word2]++;
                } else
                {
                    wordBank.insert({word2,1});
                }
                inputFile >> word;
                word2 = "";
                for (int i = 0; i < word.length(); i++)
                {
                    word[i] = tolower(word[i]);
                    if (!ispunct(word[i]))
                    {
                        word2.push_back(word[i]);
                    }
                }
            }
            string word3 = "";
            int frequency = 0;

            for (map<string,int>::iterator i = wordBank.begin(); i != wordBank.end(); i++)
            {
                word3 = i->first;
                frequency = i->second;
                if (frequencyBank.find(frequency) != frequencyBank.end())
                {
                    frequencyBank[frequency].push_back(word3);
                } else
                {
                    vector<string> words;
                    words.push_back(word3);
                    frequencyBank.insert({frequency, words});
                }
            }
        }
        else
        {
            cout << "There was an error opening the file" << endl;
        }

        outputFile << "word \t\t frequency" << endl;
        for (map<string,int>::iterator i = wordBank.begin(); i != wordBank.end(); i++)
        {
            outputFile << i->first << "\t\t\t" << i->second << endl;
        }
        outputFile.close();
        ofstream secondoutputFile("/home/sean/Desktop/my CS2 workplace/draculawordfreq.txt");
        secondoutputFile << "----------------------------------------" << endl;
        secondoutputFile << "Frequency Bank" << endl;
        int wordCount = 0;
        for (map<int,vector<string> >::iterator n = frequencyBank.begin(); n != frequencyBank.end(); n++)
        {
            wordCount = 0;
            secondoutputFile << n->first << endl;
            for (int i = 0; i < n->second.size(); i++)
            {
                secondoutputFile << n->second[i] << ", ";
                if (i % 3 == 0)
                {
                    secondoutputFile << endl;
                }
                wordCount++;
            }
            secondoutputFile << endl << endl;
        }

        inputFile.close();
        secondoutputFile.close();


    return 0;
}
