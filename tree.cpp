#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <sstream>
#include <stdio.h>
#include "simplecanvas/simplecanvas.h"
#include "tree.h"
using namespace std;

TreeNode::TreeNode(char key, long count) {
    this->key = key;
    this->count = count;
    left = NULL;
    right = NULL;
}

/**
 * @brief Recursively draw the tree, based on precomputed coordinates
 * 
 * @param canvas Canvas to which to draw the tree
 * @param xMax Maximum x coordinate, used to scale tree to canvas
 * @param maxDepth Maximum y coordinate, used to scale tree to canvas
 */
void TreeNode::draw(SimpleCanvas& canvas, int xMax, int maxDepth) {
    int x1 = 10+x*(canvas.width-20)/xMax;
    int y1 = 10+y*(canvas.height-20)/maxDepth;
    if (left != NULL) {
        int x2 = 10+left->x*(canvas.width-20)/xMax;
        int y2 = 10+left->y*(canvas.height-20)/maxDepth;
        canvas.drawLine(x1, y1, x2, y2, 0, 0, 0); 
        int xmid = (x1+x2)/2-10;
        int ymid = (y1+y2)/2-10;
        canvas.drawString("0", xmid, ymid, "simplecanvas/");
        left->draw(canvas, xMax, maxDepth);
    }
    if (right != NULL) {
        int x2 = 10+right->x*(canvas.width-20)/xMax;
        int y2 = 10+right->y*(canvas.height-20)/maxDepth;
        canvas.drawLine(x1, y1, x2, y2, 0, 0, 0);   
        int xmid = (x1+x2)/2+10;
        int ymid = (y1+y2)/2-10;
        canvas.drawString("1", xmid, ymid, "simplecanvas/");
        right->draw(canvas, xMax, maxDepth);
    }
    stringstream stream;
    stream << key;
    canvas.fillCircle(x1, y1, 10, 100, 255, 255);
    canvas.drawString(stream.str(), x1-3, y1-8, "simplecanvas/");
}


/**
 * @brief Recursively precompute the x and y coordinates
 * of the tree nodes
 * 
 * @param depth Depth of recursion
 * @param x Inorder x coordinate (by reference)
 * @param maxDepth Maximum depth seen so far (by reference)
 */
void TreeNode::getCoords(int depth, int* x, int* maxDepth) {
    if (left != NULL) {
        left->getCoords(depth+1, x, maxDepth);
    }
    this->x = *x;
    (*x)++;
    this->y = depth;
    if (depth > *maxDepth) {
        *maxDepth = depth;
    }
    if (right != NULL) {
        right->getCoords(depth+1, x, maxDepth);
    }
}

void HuffmanTree::cleanup(TreeNode* N) {
    if (N != NULL) {
        cleanup(N->left);
        cleanup(N->right);
        delete N;
    }
}

/**
 * @brief A recursive function to create the codebook for
 * converting from a character to a binary string
 * 
 * @param s String that's being built recursively
 * @param codebook Codebook that's being built
 */
void TreeNode::makeCodebook(string s, map<char, string>& codebook) {
    if (left == NULL && right == NULL) {
        codebook.insert(pair<char, string>(key, s));
    }
    if (left != NULL) {
        stringstream stream;
        stream << s << "0";
        left->makeCodebook(stream.str(), codebook);
    }
    if (right != NULL) {
        stringstream stream;
        stream << s << "1";
        right->makeCodebook(stream.str(), codebook);
    }
}

/**
 * @brief Make the codebook mapping a character to a binary string
 * according to arrangement of the nodes in this tree
 */
void HuffmanTree::makeCodebook() {
    if (this->root) {
        this->root->makeCodebook("", codebook);
    }
}


/**
 * @brief Draw the tree and save it to a file
 * 
 * @param res Resolution of canvas to which to draw tree
 * @param filename Filename to which to save tree image
 */
void HuffmanTree::draw(int res, string filename) {
    SimpleCanvas canvas(res, res);
    canvas.clearRect(255, 255, 255);
    int x = 0;
    int maxDepth = 0;
    if (root != NULL) {
        root->getCoords(0, &x, &maxDepth);
        root->draw(canvas, x, maxDepth);
    }
    canvas.write(filename);
}

HuffmanTree* buildHuffmanTree() {
    // Step 1: Load all of the characters and their counts, and sort
    // in descending order of count
    priority_queue<TreeNode*, vector<TreeNode*>, TreeNodeComparator> nodes;
    ifstream file("charcounts.txt");
    if (file.is_open()) {
        string line;
        while(getline(file, line)) {
            char c = line[0];
            long count = atol(line.substr(2, line.length()).c_str());
            nodes.push(new TreeNode(c, count));
        }
    }

    // Step 2: Build the Huffman Tree
    // TODO: Fill this in.  Take off the top two nodes of the
    // priority queue.  Let n1 be the node with the smaller count
    // and n2 be the node with the larger count.  Create a new
    // internal node whose left child is n1 and whose right child
    // is n2, and whose count is the sum of n1 and n2's counts, 
    // and add this new node to the queue.
    // The last node on the queue should become the root of the tree
    HuffmanTree* tree = new HuffmanTree();

    // Step 3: Make the codebook
    tree->makeCodebook();
    return tree;
}

void HuffmanTree::encode(string s) {
    // TODO: Fill this in.  Look up each character of 
    // s in the codebook and print out the binary string
    // that represents it
}

/**
 * @brief Decode a binary string using this tree
 * 
 * @param s Binary string to decode
 */
void HuffmanTree::decode(string s) {
    // TODO: Fill this in.  Start at the root and walk
    // left or right depending on if s's character is a 0
    // or a 1.  When you get to a leaf node, print its key
    // and jump back to the root
}