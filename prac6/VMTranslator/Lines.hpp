#pragma once
#include <string>

struct File {
  std::string __a;

  inline void ins(const std::string &in) {
    __a += in + "\n";
  }
  inline void ins(const std::string &in, const std::string &comment) {
    __a += in +"\t// "+ comment +"\n";
    // __a += in +"\n";
  }

  inline std::string str() {
    if (__a.back() == '\n') {
      __a.pop_back();
    }
    return __a;
  }
};