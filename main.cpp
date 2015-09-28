#include <iostream>
#include "WordCounter.h"

using namespace std;

int main()
{
    wordCounter mobyDick;
    if (mobyDick.fillWordCollection())
    {
        cout << "fill success" << endl;
    }
    else
    {
        cout << "fill failure" << endl;
    }
    if (mobyDick.writeOutputFile())
    {
        cout << "output success" << endl;
    }
    else
    {
        cout << "output failure" << endl;
    }

    return 0;
}
