#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
using namespace std;

inline bool outOfRange(bool increasing, int delta) {
        return (( increasing && delta < 1 || delta > 3 )
            || (!increasing && delta > -1 || delta < -3));
}

bool lineIsGood(vector<string> report) {

    int prevVal;
    bool increasing = false;

    for (int i = 0; i < report.size(); ++i) {
        int val = stoi(report[i]);
        if(i == 0) {
            prevVal = val;
            continue;
        }
        else if (i == 1) {
            if(val == prevVal) return false;
            increasing = val > prevVal;
        }

        int delta = val - prevVal;
        if (outOfRange(increasing, delta)) {
            return false;
        }

        prevVal = val;
    }

    return true;
}

int main() {
    int validReports = 0;

    // from file
    {
        string fileName = "input.txt";
        // string fileName = "example.txt";
        ifstream fileStrm(fileName);
        if (fileStrm.fail()) {
            cerr << "failed to open " << fileName << ": " << strerror(errno) << endl;
            return 1;
        }

        string line;
        vector<string> report;
        while(getline(fileStrm, line)) {
            cout << "[" << line << "]" << endl;
            boost::split(report, line, boost::is_space(), boost::token_compress_on);
            for(int i = -1; i < (int)report.size(); i++) {
                vector<string> input = report;
                if (i != -1) {
                    input.erase(next(input.begin(), i));
                } 

                for (auto word : input) {
                    cout << word << " ";
                }
                cout << endl;

                if(lineIsGood(input)) {
                    cout << "VALID" << endl;
                    ++validReports;
                    break;
                }
            }
        }

        fileStrm.close();
    }

    // debug
    // {
    //     string line = "27 23 20 18 17 14";
    //     if (lineIsGood(line))
    //         validReports++;
    // }

    cout << "valid reports: " << validReports << endl;
    cout << "355 < answer < 370 (NOT 361)" << endl;
}