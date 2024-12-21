#include <iostream>
#include <regex>

using namespace std;

int main() {
    string s = "hello-hello, there!";
    regex r("hello");

    sregex_iterator it(s.begin(), s.end(), r);
    for(auto match = it->begin(); match != it->end(); ++match) {
        cout << match->str() << endl;
    }
}