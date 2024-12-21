#include <iostream>
#include <regex>

using namespace std;

int main() {
    string s = "hello-hello, there!";
    regex r("hello");

    sregex_iterator it(s.begin(), s.end(), r);
    sregex_iterator end;
    for(; it != end; ++it) {
        cout << it->str() << endl;
    }
}