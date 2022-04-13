#include <iostream>
#include <string>
#include "tree.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: ./decode <string>";
        return 1;
    }
    HuffmanTree* T = buildHuffmanTree();
    T->decode(string(argv[1]));
    delete T;
    return 0;
}