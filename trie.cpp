#include <string>
#include <unordered_map>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    unsigned long position;
    unsigned long length;
    int prefixCount;

    TrieNode() : isEndOfWord(false), position(0), length(0), prefixCount(0) {}
};

class Trie {
private:
    TrieNode* root;

    void deleteNode(TrieNode* node) {
        if (node == nullptr) return;
        
        for (auto& pair : node->children) {
            deleteNode(pair.second);
        }
        delete node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        deleteNode(root);
    }

    void insert(const std::string& word, unsigned long pos, unsigned long len) {
        TrieNode* current = root;
        
        for (char c : word) {
            current->prefixCount++;
            
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        
        current->prefixCount++;
        current->isEndOfWord = true;
        current->position = pos;
        current->length = len;
    }

    bool search(const std::string& word, unsigned long& pos, unsigned long& len) const {
        TrieNode* node = root;
        
        for (char c : word) {
            if (node->children.find(c) == node->children.end()) {
                return false;
            }
            node = node->children[c];
        }
        
        if (node->isEndOfWord) {
            pos = node->position;
            len = node->length;
            return true;
        }
        return false;
    }

    int countPrefix(const std::string& prefix) const {
        TrieNode* node = root;
        
        for (char c : prefix) {
            if (node->children.find(c) == node->children.end()) {
                return 0;
            }
            node = node->children[c];
        }
        
        return node->prefixCount;
    }
};
