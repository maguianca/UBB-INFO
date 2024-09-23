#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

struct HuffmanNode {
    char chr;
    int frecv;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : chr(c), frecv(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frecv > b->frecv || (a->frecv == b->frecv && a->chr > b->chr);
    }
};

bool lexicographicCompare(const pair<char, int>& a, const pair<char, int>& b) {
    return a.first < b.first;
}

HuffmanNode* buildHuffmanTree(const vector<pair<char, int>>& frecventa) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    for (const auto& pair : frecventa) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* parent = new HuffmanNode(left->chr+right->chr, left->frecv + right->frecv);
        parent->left = left;
        parent->right = right;

        minHeap.push(parent);
    }

    return minHeap.top(); 
}

string decodeHuffman(HuffmanNode* root, const string& encodedText) {
    string decodedText;
    HuffmanNode* current = root;

    for (char bit : encodedText) {
        if (bit == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (!current->left && !current->right) { 
            decodedText += current->chr;
            current = root; 
        }
    }

    return decodedText;
}

void deleteHuffmanTree(HuffmanNode* root) {
    if (!root) return;
    deleteHuffmanTree(root->left);
    deleteHuffmanTree(root->right);
    delete root;
}

int main(int argc, char** argv) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    int n, x;
    unordered_map<char, int> frecventa;
    char c;

  
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> c >> x;
        frecventa[c] = x;
    }

    string text;
   while( getline(fin, text)); 

 
    vector<pair<char, int>> vectorFrecventa(frecventa.begin(), frecventa.end());
    std::sort(vectorFrecventa.begin(), vectorFrecventa.end(), lexicographicCompare);  

    HuffmanNode* root = buildHuffmanTree(vectorFrecventa);

    string decodedText = decodeHuffman(root, text); 

   
    fout << decodedText << "\n";

    deleteHuffmanTree(root); 

    fin.close();
    fout.close();

    return 0;
}
