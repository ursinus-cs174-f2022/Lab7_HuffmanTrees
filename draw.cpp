#include <iostream>
#include "tree.h"

using namespace std;

int main() {
    HuffmanTree* T = buildHuffmanTree();
    T->draw(800, "tree.png");
    delete T;
    return 0;
}