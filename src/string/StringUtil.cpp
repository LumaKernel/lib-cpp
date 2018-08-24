// @import header
// @@
// @name split
// @snippet     split
vector<string> split(const string& s, char delim) {
  std::vector<string> elms;
  size_t offset = 0;
  while (true) {
    size_t next = s.find_first_of(delim, offset);
    if (next == string::npos) {
      elms.emplace_back(s.substr(offset));
      return elms;
    }
    elms.emplace_back(s.substr(offset, next - offset));
    offset = next + 1;
  }
}

