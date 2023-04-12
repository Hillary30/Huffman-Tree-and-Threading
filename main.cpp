#include "huffmanTree.h"
#include "huffmanTree.cpp"
#include <fstream>
#include <vector>
#include <cctype>
#include <unistd.h>
#include <pthread.h>
using namespace std;

struct tempStruct {
    node* treeNode;
    string findBinary = "";
    char* foundSym;
    vector<int> positions;
    vector<char>* fMessage;
};

char* findBinaryChar(node* n, string find) {
    if(n->left == nullptr && n->right == nullptr) {
        return (&n->symbol);
    }
    else {
        if(find[0] == '0') {
            find = find.substr(1);
            return findBinaryChar(n->left, find);
        }
        else {
            find = find.substr(1);
            return findBinaryChar(n->right, find);
        }
    }
};

void* find_Symbol(void* void_ptr) {
    struct tempStruct *temp_ptr = (struct tempStruct*) void_ptr;
    temp_ptr->foundSym = findBinaryChar(temp_ptr->treeNode, temp_ptr->findBinary);

    for(int i = 0; i < temp_ptr->positions.size(); i++) {
        temp_ptr->fMessage->at(temp_ptr->positions[i]) = *temp_ptr->foundSym;
    }
    return NULL;
};

int main() {

    //FILE INFORMTION
    string myInput = "";
    string inFile = "symbols.txt"; 
    //cin >> inFile;
    ifstream input(inFile);
    
    string comInput = "";
    string comFile = "binary.txt";
    //cin >> comFile;
    ifstream compress(comFile);

    //MAKE THE PRIORITY QUEUE
    char sym;
    int freq = -1;
    int NTHREADS = 0; //NUMBER OF SYMBOLS
    tree myTree;
    
    while(getline(input, myInput)) { 
        sym = myInput[0];
        freq = stoi(myInput.substr(2));
        myTree.insertSort(sym, freq);
        NTHREADS++;
    }

    //MAKE THE TREE
    while(myTree.size() > 1) { 
        myTree.insertNew();
    }
    
    //PRINT BINARY CODES
    string binary = "";
    myTree.setBinary(binary, myTree.getRoot());
    myTree.printTree(myTree.getRoot());
    cout << endl;
    
    //THREADS
    static struct vector<tempStruct> arrayTree;
    pthread_t tid[NTHREADS]; 
    int message_size = 0; //NUMBER OF POSITIONS
    
    //BINARY AND POSITIONS
    while(getline(compress, comInput)) {
        tempStruct childTree;
        childTree.treeNode = myTree.getRoot();
        size_t found = comInput.find(" ");
    
        if(found != std::string::npos) {
            childTree.findBinary = comInput.substr(0, found);
            comInput = comInput.substr(found+1);
        }
        
        while(comInput.find(" ") != std::string::npos) {
            childTree.positions.push_back(stoi(comInput.substr(0, comInput.find(" "))));
            comInput = comInput.substr(comInput.find(" ") + 1);
            message_size++;
        }
        
        childTree.positions.push_back(stoi(comInput));
        message_size++;
        arrayTree.push_back(childTree);
    }
    
    //MESSAGE VECTOR ACCESSIBLE BY MAIN THREAD
    vector<char> messageVec(message_size);
    
    for(int i = 0; i < NTHREADS; i++) {
        arrayTree[i].fMessage = &messageVec; //PASS THE MESSAGE TO EACH CHILD
        if(pthread_create(&tid[i], NULL, find_Symbol, &arrayTree[i])) {
            fprintf(stderr, "Error creating thread\n");
			return 1;
        }
    }
    
    //JOIN THREADS
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(tid[i], NULL);
    }
    
    //PRINT MESSAGE
    cout << "Original message: ";
    for(int i = 0; i < messageVec.size(); i++) {
        cout << messageVec[i];
    }

    return 0;
}