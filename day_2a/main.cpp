#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    string fileName = "input.txt";
    ifstream fileStrm(fileName);

    if (fileStrm.fail()) {
        cerr << "failed to open " << fileName << ": " << strerror(errno) << endl;
        return 1;
    }

    int valid = 0;
    string line;
    while(getline(fileStrm, line)) {
        vector<string> words;
        boost::split(words, line, boost::is_space(), boost::token_compress_on);

        int prevVal;
        bool increasing = false;
        bool isValid = true;

        for (int i = 0; i < words.size(); ++i) {
            int val = stoi(words[i]);
            if(i == 0) {
                prevVal = val;
                continue;
            }
            else if (i == 1) {
                increasing = val > prevVal;
            }

            int delta = val - prevVal;
            if(increasing && delta < 1 || delta > 3) {
                cout << line << " (" << delta << ")" << endl;
                isValid = false;
                break;
            }
            else if(!increasing && delta > -1 || delta < -3) {
                cout << line << " (" << delta << ")" << endl;
                isValid = false;
                break;
            }

            prevVal = val;
        }

        // cout << line << ": " << isValid << endl;
        if(isValid) {
            ++valid;
        }
    }

    fileStrm.close();

    cout << "valid reports: " << valid << endl;
}