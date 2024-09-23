#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

struct HuffmanNode {
    char chr;
    int frecv;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : chr(c), frecv(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frecv > b->frecv|| a->frecv ==b->frecv && a->chr<b->chr;
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

        HuffmanNode* parent = new HuffmanNode(right->chr+left->chr, left->frecv + right->frecv);
        parent->left = left;
        parent->right = right;

        minHeap.push(parent);
    }

    return minHeap.top();
}

void generateHuffmanCodes(HuffmanNode* root, unordered_map<char, string>& codes, const string& code) {
    if (!root) {
        return;
    }

    if (!root->left && root->right == nullptr) {
        codes[root->chr] = code;
    }

    generateHuffmanCodes(root->left, codes, code + "0");
    generateHuffmanCodes(root->right, codes, code + "1");
}

string encodeHuffman(const string& text, const unordered_map<char, string>& codes) {
    string encoded;
    for (char c : text) {
        encoded += codes.at(c);
    }
    return encoded;
}

void deleteHuffmanTree(HuffmanNode* root) {
    if (!root) {
        return;
    }
    deleteHuffmanTree(root->left);
    deleteHuffmanTree(root->right);
    delete root;
}

int main() {

    string text;
    getline(fin, text);
    unordered_map<char, int> frecventa;
    for (char c : text) {
        frecventa[c]++;
    }

    vector<pair<char, int>> vectorFrecventa(frecventa.begin(), frecventa.end());
    std::sort(vectorFrecventa.begin(), vectorFrecventa.end(), lexicographicCompare);

    HuffmanNode* root = buildHuffmanTree(vectorFrecventa);
    unordered_map<char, string> codes;
    generateHuffmanCodes(root, codes, "");

    string encodedText = encodeHuffman(text, codes);
    for (const auto& c : vectorFrecventa) {
        fout << c.first << ": " << c.second << "\n";
    }

    fout << "Coduri Huffman:\n";
    for (const auto& pair : codes) {
        fout << pair.first << ": " << pair.second << "\n";
    }

    fout << "Text codificat:\n" << encodedText << "\n";

    deleteHuffmanTree(root);
    fin.close();
    fout.close();

    return 0;
}
