#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <string>
#include <iostream>
using namespace std;

class node {
    public:
        char symbol;
        int freq;
        string bin;
        node* right;
        node* left;
        node* next;

        node();
        node(char s, int f);
        node(node* n, node* p); 

        char getSym() { return symbol; }
        int getFreq() { return freq; }
        string getBin() { return bin; }
};

class tree {
    private: 
        node* root;

    public: 
        tree() { root = nullptr; }
        ~tree() { root = nullptr; }

        void setRoot(node* r) { root = r; } 
        node* getRoot() { return root; }

        int size();

        void insertSort(char s, int f);
        void insertSort(node* n);
        void insertNew();
        node* pop();

        void printSort();
        void printTree(node* n);

        void setBinary(string binCode, node* n);
};

#endif