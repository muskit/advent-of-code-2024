#include <algorithm>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

int main() {
    string fileName = "input.txt";
    vector<int> lists[] = {
        vector<int>{}, vector<int>{}
    };

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

        for (int i = 0; i < 2; ++i) {
            try {
                int val = stoi(words[i]);
                lists[i].insert(
                    upper_bound(lists[i].begin(), lists[i].end(), val),
                    val
                );
            } catch (invalid_argument ex) {
                cerr << "invalid_argument " << words[i] << "! " << ex.what() << endl;
                return 1;
            }

        }
    }

    // close file
    fileStream.close();

    // calculate sum
    int sum = 0;
    for(int i = 0; i < lists[0].size(); ++i) {
        // cout << lists[0][i] << " " << lists[1][i] << endl;
        int diff = abs(lists[0][i] - lists[1][i]);
        cout << diff << endl;
        sum += diff;
    }
    cout << "sum: " << sum << endl;
}