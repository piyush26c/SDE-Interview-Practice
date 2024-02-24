#include<bits/stdc++.h>
using namespace std;

struct Node {
    public:
    Node* links[26];
    bool isEndNode = false; // is it a end node?
    
    // checks if the reference trie is present or not
    bool containsKey(char ch) {
        return (links[ch - 'a'] != nullptr);
    } 

    // creating reference trie
    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    // to get the next node for traversal
    Node* get(char ch) {
        return links[ch - 'a'];
    }

    // setting isEndNode to true at the end of the word
    void setEnd() {
        isEndNode = true;
    }

    // checking if the word is completed or not
    bool isEnd() {
        return isEndNode;
    }
};

class Trie {
    private:
    Node* root;

    public:
    Trie() {
        root = new Node();
    }

    void insert(string word) {
        Node* node = root;
        for (int i = 0; i < (int) word.length(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node());
            }
            // moves to reference trie
            node = node->get(word[i]);
        }
        node->setEnd();
    }

    bool search(string word) {
        Node* node = root;
        for (int i = 0; i < (int) word.length(); i++) {
            if (node->containsKey(word[i])) {
                node = node->get(word[i]);
            } else {
                return false;
            }
        }
        return node->isEnd();
    }

    bool startsWith(string prefix) {
        Node* node = root;
        for (int i = 0; i < (int) prefix.length(); i++) {
            if (node->containsKey(prefix[i])) {
                node = node->get(prefix[i]);
            } else {
                return false;
            }
        }
        return true;
    }
};

int main() {
    
}