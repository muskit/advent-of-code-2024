#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

#define FILENAME "input.txt"
#define WIDTH 140
#define HEIGHT 140

// #define FILENAME "example.txt"
// #define WIDTH 10
// #define HEIGHT 10

char grid[HEIGHT][WIDTH]; // the crossword puzzle

const int offset[8][3][2] = {
    {
        // directly right
        {0,1},
        {0,2},
        {0,3}
    },
    {
        // down-right
        {1,1},
        {2,2},
        {3,3}
    },
    {
        // directly down
        {1,0},
        {2,0},
        {3,0}
    },
    {
        // down-left
        {1,-1},
        {2,-2},
        {3,-3}
    },
    {
        // directly left
        {0,-1},
        {0,-2},
        {0,-3}
    },
    {
        // up-left
        {-1,-1},
        {-2,-2},
        {-3,-3}
    },
    {
        // directly up
        {-1,0},
        {-2,0},
        {-3,0}
    },
    {
        // up-right
        {-1,1},
        {-2,2},
        {-3,3}
    }
};

// count how many times target string appears starting at a crossword grid tile
int countAppearances(int x, int y, string target = "XMAS") {
    if (grid[y][x] != 'X') return 0;

    uint appearances = 0;
    bool isGood = true;
    for (int g = 0; g < 8; ++g) { // each delta group
        for(int c = 0; c < 3; ++c) { // delta coordinate
            int tY = y + offset[g][c][0];
            int tX = x + offset[g][c][1];
            if (tY < 0 || tY >= HEIGHT || tX < 0 || tX >= WIDTH) {
                // out of bounds
                isGood = false;
                break;
            }
            if(grid[tY][tX] != target[1+c]) {
                // doesn't match target string
                isGood = false;
                break;
            }
        }
        if(isGood) {
            appearances++;
        }
        isGood = true;
    }

    return appearances;
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

    unsigned int xmasAppears = 0;
    for(int y = 0; y < HEIGHT; ++y) {
        for(int x = 0; x < WIDTH; ++x) {
            if (grid[y][x] == 'X') {
                xmasAppears += countAppearances(x, y);
            }
        }
    }

    cout << "found " << xmasAppears << " instances of XMAS" << endl;
}