#include <cstdio>
#include <cstring>
#include <ios>
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
    regex funcRegex(R"(mul\((\d{1,3}),(\d{1,3})\))");
    auto regIt = sregex_iterator(dump.begin(), dump.end(), funcRegex);
    auto end = sregex_iterator();
    int sum = 0;
    cout << "[Matches]" << endl;
    for(; regIt != end; ++regIt) {
        smatch m = *regIt;
        cout << m.str() << endl;
        sum += stoi(m[1]) * stoi(m[2]);
    }

    cout << "sum: " << sum << endl;
}