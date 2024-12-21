#include <iostream>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

#define FILENAME "input.txt"
#define WIDTH 140
#define HEIGHT 140

// #define FILENAME "example.txt"
// #define WIDTH 10
// #define HEIGHT 10

char grid[HEIGHT][WIDTH]; // the crossword puzzle

map<char, char> opposite = {
    {'M', 'S'}, {'S', 'M'}
};

const int offset[4][2] = {
{
        // down-right
        1,1
    },
{
        // up-left
        -1,-1
    },
{
        // down-left
        1,-1
    },
{
        // up-right
        -1,1
    }
};

// count how many times target string appears starting at a crossword grid tile
bool isX_MAS(int x, int y) {
    if (grid[y][x] != 'A') return 0;

    for (int c = 0; c < 4; c += 2) { 
        int aY = y + offset[c][0];
        int aX = x + offset[c][1];
        int bY = y + offset[c+1][0];
        int bX = x + offset[c+1][1];
        char tgt = opposite[grid[aY][aX]];

        if (aY < 0 || aY >= HEIGHT || aX < 0 || aX >= WIDTH
            || bY < 0 || bY >= HEIGHT || bX < 0 || bX >= WIDTH) {
            // out of bounds
            cout << y << "," << x << " OOB!" << endl;
            return false;
        }
        if(grid[bY][bX] != tgt) {
            // doesn't match target char
            cout << y << "," << x << " NEQ!" << endl;
            return false;
        }
    }
    cout << y << "," << x << endl;
    return true;
}

int main() {
    ifstream fileStrm(FILENAME);
    if (fileStrm.fail()) {
        cerr << "failed to open " << FILENAME << ": " << strerror(errno) << endl;
        return 1;
    }

    for(int y = 0; y < HEIGHT; ++y) {
        string line;
        getline(fileStrm, line);
        for(int x = 0; x < WIDTH; ++x) {
            grid[y][x] = line[x];
        }
    }

    uint xmasAppears = 0;
    for(int y = 0; y < HEIGHT; ++y) {
        for(int x = 0; x < WIDTH; ++x) {
            if (grid[y][x] == 'A') {
                xmasAppears += (uint)isX_MAS(x, y);
            }
        }
    }

    cout << "found " << xmasAppears << " instances of XMAS" << endl;
}