#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <stdio.h>
#include "simplecanvas/simplecanvas.h"
using namespace std;

class TreeNode {
    public:
        char key;
        long count;
        int x, y; // Relative coordinates of node
        TreeNode* left;
        TreeNode* right;

        TreeNode(char key, long count);

        /**
         * @brief Recursively draw the tree, based on precomputed coordinates
         * 
         * @param canvas Canvas to which to draw the tree
         * @param xMax Maximum x coordinate, used to scale tree to canvas
         * @param maxDepth Maximum y coordinate, used to scale tree to canvas
         */
        void draw(SimpleCanvas& canvas, int xMax, int maxDepth);

        /**
         * @brief Recursively precompute the x and y coordinates
         * of the tree nodes
         * 
         * @param depth Depth of recursion
         * @param x Inorder x coordinate (by reference)
         * @param maxDepth Maximum depth seen so far (by reference)
         */
        void getCoords(int depth, int* x, int* maxDepth);

        /**
         * @brief A recursive function to create the codebook for
         * converting from a character to a binary string
         * 
         * @param s String that's being built recursively
         * @param codebook Codebook that's being built
         */
        void makeCodebook(string s, map<char, string>& codebook);
};


class TreeNodeComparator {
    public:
        bool operator() (TreeNode* x, TreeNode* y) {
            return x->count > y->count;
        }
};


class HuffmanTree {
    private:
        void cleanup(TreeNode* N);
        map<char, string> codebook;
    public:
        TreeNode* root;
        HuffmanTree() {
            root = NULL;
        }
        ~HuffmanTree() {
            cleanup(root);
        }
        
        /**
         * @brief Make the codebook mapping a character to a binary string
         * according to arrangement of the nodes in this tree
         */
        void makeCodebook();

        /**
         * @brief Draw the tree and save it to a file
         * 
         * @param res Resolution of canvas to which to draw tree
         * @param filename Filename to which to save tree image
         */
        void draw(int res, string filename);

        /**
         * @brief Encode a string into binary using this tree
         * 
         * @param s String to encode
         */
        void encode(string s);
        
        /**
         * @brief Decode a binary string using this tree
         * 
         * @param s Binary string to decode
         */
        void decode(string s);
};

HuffmanTree* buildHuffmanTree();

#endif