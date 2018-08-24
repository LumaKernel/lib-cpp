// @import header
// @@
// @name AhoCorasick Library
// @title AhoCorasick
// @snippet     ahocorasick
// @alias       aho
// never fail to call build() !!
/// --- AhoCorasick Library {{{ ///

struct AhoCorasick {
  struct Trie {
    unordered_map<char, Trie*> child;
    Trie* failure = nullptr;
    vector<int> words;
    Trie* add(char c) {
      if(child.count(c)) {
        return child[c];
      } else {
        return child[c] = new Trie;
      }
    }
    Trie* go(char c) {
      if(child.count(c)) {
        return child[c];
      } else {
        if(failure == nullptr) {
          return this;
        } else {
          return failure -> go(c);
        }
      }
    }
  };
  Trie* top = new Trie;
  vector<string> dict;
  void add(string word) {
    Trie* now = top;
    for(size_t i = 0; i < word.size(); i++){
      now = now -> add(word[i]);
    }
    now -> words.emplace_back(dict.size());
    dict.emplace_back(word);
  }
  void build() {
    queue<Trie*> q;
    q.emplace(top);
    while(q.size()) {
      Trie* now = q.front();
      q.pop();
      for(pair<char, Trie*> ch : now -> child) {
        q.emplace(ch.second);
        ch.second -> failure = now == top ? top : now -> failure -> go(ch.first);
        /// only from failure!!
        vector<int> &words = ch.second -> words;
        words.insert(end(words),begin(failure -> words), end(failure -> words));
      }
    }
  }
  vector< tuple<int, int, int> > match(string s) {
    Trie* now = top;
    vector< tuple<int, int, int> > res;
    for(size_t i = 0; i < s.size(); i++) {
      now = now -> go(s[i]);
      for(int word : now -> words) {
        res.emplace_back(i - dict[word].size() + 1, i, word);
      }
    }
    return res;
  }
};

/// }}} --- ///
