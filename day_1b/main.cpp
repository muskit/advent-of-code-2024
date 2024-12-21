#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <map>

using namespace std;

int main() {
    string fileName = "input.txt";
    vector<int> lefts;
    map<int, int> rightFreqs;

    ifstream fileStream(fileName);
    if (fileStream.fail()) {
        cerr << "failed to open " << fileName << ": " << strerror(errno) << endl;
        return 1;
    }

    // populate lists (sorted insert)
    string line;
    while (getline(fileStream, line)) {
        vector<string> words(2);
        boost::split(words, line, boost::is_space(), boost::token_compress_on);

        lefts.push_back(stoi(words[0]));
        rightFreqs[stoi(words[1])]++;
    }

    // close file
    fileStream.close();

    // calculate sum
    int score = 0;
    for (int l : lefts) {
        score += l*rightFreqs[l];
    }
    cout << score << endl;
}