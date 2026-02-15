#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

map<int, map<int, char>> canvas;

int min_y = 0;
int max_y = 0;
int max_x = 0;

void plot(int x, int y, char c) {
    canvas[y][x] = c;
    if (y < min_y) min_y = y;
    if (y > max_y) max_y = y;
    if (x > max_x) max_x = x;
}

void drawHomeUp(int currentX, int len, int height) {
    int roofHeight = len / 2;
    
    for (int i = 0; i < len; ++i) {
        plot(currentX + i, 0, '#');
    }

    for (int h = 1; h <= height; ++h) {
        plot(currentX, -h, '@');
        plot(currentX + len - 1, -h, '&');
    }

    for (int r = 0; r < roofHeight; ++r) {
        int y = -(height + 1 + r);
        int offset = r; 
        plot(currentX + offset, y, '/');
        plot(currentX + len - 1 - offset, y, '\\');
    }
}

void drawHomeDown(int currentX, int len, int height) {
    int roofHeight = len / 2;

    for (int i = 0; i < len; ++i) {
        plot(currentX + i, 0, '#');
    }

    for (int h = 1; h <= height; ++h) {
        plot(currentX, h, '&');
        plot(currentX + len - 1, h, '@');
    }

    for (int r = 0; r < roofHeight; ++r) {
        int y = height + 1 + r;
        int offset = r;
        plot(currentX + offset, y, '\\');
        plot(currentX + len - 1 - offset, y, '/');
    }
}

void drawHomeLeft(int currentX, int len, int height) {
    int roofHeight = len / 2;
    int totalWidth = height + roofHeight;
    
    int baseX = currentX + totalWidth - 1;
    for (int i = 0; i < len; ++i) {
        plot(baseX, -i, '#');
    }

    for (int w = 0; w < height; ++w) {
        int x = currentX + roofHeight + w;
        plot(x, -(len - 1), '&');
        plot(x, 0, '@');
    }

    for (int r = 0; r < roofHeight; ++r) {
        int k = r;
        int x = currentX + roofHeight - 1 - k;
        
        plot(x, -(len - 1) + k, '/');
        plot(x, 0 - k, '\\');
    }
}

void drawHomeRight(int currentX, int len, int height) {
    int roofHeight = len / 2;
    int totalWidth = height + roofHeight;

    int baseX = currentX;
    for (int i = 0; i < len; ++i) {
        plot(baseX, -i, '#');
    }

    for (int w = 0; w < height; ++w) {
        int x = baseX + 1 + w;
        plot(x, -(len - 1), '@');
        plot(x, 0, '&');
    }

    for (int k = 0; k < roofHeight; ++k) {
        int x = baseX + height + 1 + k;
        
        plot(x, -(len - 1) + k, '\\');
        plot(x, 0 - k, '/');
    }
}

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    string spec;

    int currentX = 0;
    int gap = 1;

    while (ss >> spec) {
        size_t xPos = spec.find('x');
        if (xPos == string::npos) continue;
        
        char dir = spec.back();
        string hStr = spec.substr(xPos + 1, spec.length() - xPos - 2);
        string lStr = spec.substr(0, xPos);

        int len = stoi(lStr);
        int height = stoi(hStr);
        
        int widthUsed = 0;

        if (dir == 'H' || dir == 'U') {
            drawHomeUp(currentX, len, height);
            widthUsed = len;
        } else if (dir == 'D') {
            drawHomeDown(currentX, len, height);
            widthUsed = len;
        } else if (dir == 'L') {
            drawHomeLeft(currentX, len, height);
            widthUsed = height + (len / 2);
        } else if (dir == 'R') {
            drawHomeRight(currentX, len, height);
            widthUsed = height + (len / 2);
        }

        currentX += widthUsed + gap;
    }

    for (int y = min_y; y <= max_y; ++y) {
        int rowMaxX = 0;
        if(canvas.count(y)) {
            for(auto const& [x, val] : canvas[y]) {
                if(x > rowMaxX) rowMaxX = x;
            }
        }
        
        for (int x = 0; x <= rowMaxX; ++x) {
            if (canvas[y].count(x)) {
                cout << canvas[y][x];
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }

    return 0;
}