#include <iostream>
using namespace std;

class Trie {
private:
    struct node {
        bool isWord;
        node* children[26];

        node() {
            isWord = false;
            for (int i = 0; i < 26; i++)
                children[i] = nullptr;
        }
    };

    node* root;

    bool isEmpty(node* curr) {
        for (int i = 0; i < 26; ++i)
            if (curr->children[i] != nullptr)
                return false;
        return true;
    }

    node* deleteHelper(node* curr, const string& word, int depth) {
        if (!curr) return nullptr;

        if (depth == word.size()) {
            curr->isWord = false;

            if (isEmpty(curr)) {
                delete curr;
                return nullptr;
            }
            return curr;
        }

        int idx = word[depth] - 'a';
        curr->children[idx] = deleteHelper(curr->children[idx], word, depth + 1);

        if (!curr->isWord && isEmpty(curr)) {
            delete curr;
            return nullptr;
        }
        return curr;
    }

public:
    Trie() {
        root = new node();
    }

    void insert(const string& word) {
        node* curr = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!curr->children[idx])
                curr->children[idx] = new node();
            curr = curr->children[idx];
        }
        curr->isWord = true;
    }

    bool search(const string& word) {
        node* curr = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!curr->children[idx])
                return false;
            curr = curr->children[idx];
        }
        return curr->isWord;
    }

    void deleteSoft(const string& word) {
        node* curr = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!curr->children[idx])
                return;
            curr = curr->children[idx];
        }
        curr->isWord = false;
    }

    void deleteHard(const string& word) {
        root = deleteHelper(root, word, 0);
    }

    ~Trie() {
        clear(root);
    }

    void clear(node* node) {
        if (!node) return;
        for (int i = 0; i < 26; ++i)
            clear(node->children[i]);
        delete node;
    }
};

void solve() {
    int q;
    cin >> q;
    Trie trie;

    while (q--) {
        int type;
        string word;
        cin >> type >> word;

        if (type == 1) {
            trie.insert(word);
        } else if (type == 2) {
            cout << (trie.search(word) ? "YES" : "NO") << endl;
        } else if (type == 3) {
            if (trie.search(word))
                trie.deleteHard(word);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();
    return 0;
}
