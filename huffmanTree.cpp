#include "huffmanTree.h"

node::node() {
    symbol = '-';
    freq = -1;
    bin = "";
    right = nullptr;
    left = nullptr;
    next = nullptr;
}

node::node(char s, int f) { 
    symbol = s;
    freq = f;
    bin = "";
    right = nullptr;
    left = nullptr;
    next = nullptr;
}

node::node(node* n, node* p) {
    symbol = '-';
    freq = n->freq + p->freq;
    bin = "";
    next = nullptr;
    
    if(n->freq < p->freq) {
        left = n;
        right = p;
    }
    else if(n->freq > p->freq){
        left = p;
        right = n;
    }
    else if(n->freq == p->freq) {
        if(n->symbol == '-') {
            left = n;
            right = p;
        }
        else if(p->symbol == '-') {
            left = p;
            right = n;
        }
        else {
            left = n;
            right = p;
        }
    }
    else {
        left = n;
        right = p;
    }
}

int tree::size() {
    if(root == nullptr) {
        return 0;
    }
    else {
        int i = 0;
        node* cu = root;
        while(cu != nullptr) {
            i++;
            cu = cu->next;
        }
        return i;
    }
}

void tree::insertSort(char s, int f) {
    node* temp = new node(s, f);
    if(root == nullptr) { 
        root = temp;
        return;
    }
    else if(root->getFreq() == f) { 
        if(root->symbol > s) {
            temp->next = root;
            root = temp;
            return;
        }
        else {  
            node* cu = root;
            while(cu->next != nullptr) {
                if(cu->next->getFreq() != root->getFreq()) {
                    break;
                }
                else if(cu->next->getSym() > temp->getSym()) {
                    temp->next = cu->next;
                    cu->next = temp;
                    return;
                }
                else {
                    cu = cu->next;
                }
            }
            temp->next = cu->next;
            cu->next = temp;
            return;
        }
    }
    else if(root->getFreq() > f) { 
        temp->next = root;
        root = temp;
        return;
    }
    else if(root->getFreq() < f) { 
        node* cu = root;
        while(cu->next != nullptr) {
            if(cu->next->getFreq() > f) {
                temp->next = cu->next;
                cu->next = temp;
                return;
            }
            else if(cu->next->getFreq() == f) { 
                if(cu->next->symbol < s) {
                    cu = cu->next;
                }
                else if(cu->next->getSym() > s) {
                    temp->next = cu->next;
                    cu->next = temp;
                    return;
                }
                else {
                    node* cuu = cu;
                    while(cuu->next != nullptr) {
                        if(cuu->next->getFreq() != cu->getFreq()) {
                            break;
                        }
                        else if(cuu->next->getSym() > temp->getSym()) {
                            temp->next = cuu->next;
                            cuu->next = temp;
                            return;
                        }
                        cuu = cuu->next;
                    }
                    temp->next = cu->next;
                    cu->next = temp;
                    return;
                }
            }
            else {
                cu = cu->next;
            }
        }
        temp->next = cu->next;
        cu->next = temp;
        return;
    }
}

void tree::insertSort(node* n) {
    if(root == nullptr) { 
        root = n;
        return;
    }
    else if(root->getFreq() == n->getFreq()) { 
        if(root->getSym() > n->getSym()) {
            n->next = root;
            root = n;
            return;
        }
        else { 
            node* cu = root;
            while(cu->next != nullptr) {
                if(cu->next->getFreq() != root->getFreq()) {
                    break;
                }
                else if(cu->next->getSym() > n->getSym()) {
                    n->next = cu->next;
                    cu->next = n;
                    return;
                }
                cu = cu->next;
            }
            n->next = cu->next;
            cu->next = n;
        }
    }
    else if(root->getFreq() > n->getFreq()) { 
        n->next = root;
        root = n;
        return;
    }
    else if(root->getFreq() < n->getFreq()) { 
        node* cu = root;
        while(cu->next != nullptr) {
            if(cu->next->getFreq() > n->getFreq()) {
                n->next = cu->next;
                cu->next = n;
                return;
            }
            else if(cu->next->getFreq() == n->getFreq()) { 
                if(cu->next->symbol > n->getSym()) {
                    n->next = cu->next;
                    cu->next = n;
                    return;
                }
                else {
                    node* cuu = cu;
                    while(cuu->next != nullptr) {
                        if(cuu->next->getFreq() != cu->getFreq()) {
                            break;
                        }
                        else if(cuu->next->getSym() > n->getSym()) {
                            n->next = cuu->next;
                            cuu->next = n;
                            return;
                        }
                        cuu = cuu->next;
                    }
                    n->next = cu->next;
                    cu->next = n;
                    return;
                }
            }
            cu = cu->next;
        }
        n->next = cu->next;
        cu->next = n;
        return;
    }
}

void tree::insertNew() {
    if(size() > 1) {
        node* temp1 = pop();
        node* temp2 = pop();
        node* newNode = new node(temp1, temp2);
        insertSort(newNode);
    }
}

node* tree::pop() {
    if(root != nullptr) {
        node* temp = root;
        root = root->next;
        temp->next = nullptr;
        return temp;
    }
    return nullptr;
}

void tree::printSort() {
    if(root == nullptr) {
        cout << "Empty Sorted List." << endl;
        return;
    }
    else {
        node* cu = root;
        int i = 0;
        while(cu != nullptr) {
            cout << i << ": " << cu->getSym() << " - " << cu->getFreq() << endl;
            i++;
            cu = cu->next;
        }
    }

}

void tree::printTree(node* n) {
    if(n == nullptr) {
        return;
    }
    else {
        if(n->getSym() == '-') {
            printTree(n->left);
            printTree(n->right);
        }
        else {
            cout << "Symbol: " << n->getSym() << ", Frequency: " << n->getFreq() << ", Code: " << n->getBin() << endl;
            printTree(n->left);
            printTree(n->right);
        }
    }
}

void tree::setBinary(string binCode, node* n) {
    if(n->left == nullptr && n->right == nullptr) {
        n->bin = binCode;
    }
    else {
        setBinary(binCode + "0", n->left);
        setBinary(binCode + "1", n->right);
    }
}