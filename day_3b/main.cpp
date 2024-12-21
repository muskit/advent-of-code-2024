#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

int main() {
    string fileName = "input.txt";
    // string fileName = "example.txt";
    ifstream fileStrm(fileName);
    if (fileStrm.fail()) {
        cerr << "failed to open " << fileName << ": " << strerror(errno) << endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << fileStrm.rdbuf();
    string dump = buffer.str();
    cout << dump << endl;

    /** Raw strings have
      * R"(
      * ...and...
      * )"
      * as delimiters. */
    regex funcRegex(R"((mul\((\d{1,3}),(\d{1,3})\))|(do\(\))|(don't\(\)))");
    auto regIt = sregex_iterator(dump.begin(), dump.end(), funcRegex);
    auto end = sregex_iterator();
    bool doIt = true;
    int sum = 0;

    cout << "[Matches]" << endl;
    for(; regIt != end; ++regIt) {
        smatch m = *regIt;
        string s = m.str();
        cout << s << endl;

        if(s.find("do()") != string::npos) {
            doIt = true;
        } else if(s.find("don't()") != string::npos) {
            doIt = false;
        } else {
            if(doIt) {
                cout << m[1] << "|" << m[2] << endl;
                sum += stoi(m[2]) * stoi(m[3]);
            }
        }
    }

    cout << "sum: " << sum << endl;
}