// @import header
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// @@
// @name AhoCorasick Library
// @snippet     ahocorasick
// @alias       aho

// add(string)
// === build() ===
// match(string, f)           : [left, right], f(int left, int right, int key)
// next(node, char, f): Trie* : f(int len, int key)
// - right-inc -> left-dec order
// === --- ===
// if ML is tight, comment out "delete"
/// --- AhoCorasick Library {{{ ///

#include <functional>
#include <unordered_map>

struct AhoCorasick {
  struct Trie {
    unordered_map< char, Trie * > child;
    int id;
    Trie *failure = nullptr;
    Trie *next = nullptr; // next failure that has the word
    int word = -1;
    Trie *add(char c) {
      if(child.count(c)) {
        return child[c];
      } else {
        return child[c] = new Trie;
      }
    }
    Trie *go(char c) {
      if(child.count(c)) {
        return child[c];
      } else {
        if(failure == nullptr) { // only top can come here
          return this;
        } else {
          return failure->go(c);
        }
      }
    }
    ~Trie() {
      for(auto &x : child) {
        delete x.second;
      }
    }
  };
  Trie *top = new Trie;
  ~AhoCorasick() {
    // delete top;
  }
  vector< string > dict;
  void add(string word) {
    Trie *now = top;
    for(size_t i = 0; i < word.size(); i++) {
      now = now->add(word[i]);
    }
    now->word = dict.size();
    dict.emplace_back(word);
  }
  void build() {
    queue< Trie * > q;
    q.emplace(top);
    while(q.size()) {
      Trie *now = q.front();
      q.pop();
      for(pair< char, Trie * > ch : now->child) {
        q.emplace(ch.second);
        Trie *failure = ch.second->failure =
            now == top ? top : now->failure->go(ch.first);
        ch.second->next = failure->word >= 0 ? failure : failure->next;
      }
    }
  }
  Trie *next(Trie *now, char c,
             const function< void(int, int) > &f = [](int, int) {}) {
    now = now->go(c);
    Trie *tmp = now;
    while(tmp != nullptr && tmp != top) {
      int word = tmp->word;
      if(word >= 0) {
        f(dict[word].size(), word);
      }
      tmp = tmp->next;
    }
    return now;
  }
  void match(string s,
             const function< void(int, int, int) > &f = [](int, int, int) {}) {
    Trie *now = top;
    for(size_t i = 0; i < s.size(); i++) {
      now = now->go(s[i]);
      Trie *tmp = now;
      while(tmp != nullptr && tmp != top) {
        int word = tmp->word;
        if(word >= 0) {
          f(i - dict[word].size() + 1, i, word);
        }
        tmp = tmp->next;
      }
    }
  }
};

/// }}}--- ///

using Trie = AhoCorasick::Trie;
