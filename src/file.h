#ifndef FILE_H
#define FILE_H

#include "node.h"
#include <string>
using namespace std;

class File  : public Node {
public:
  File(const char *path) : Node(path){
    if(S_ISREG(_st.st_mode) != 1){
      pathError e;
      throw e;
    }
  }

  string getType() {
    return "file";
  }

  int countWords(std::istream &is) {
    int count = 0;
    for(string word; is >> word; count++) {}
    return count;
  }

  int countLines(std::istream &is) {
    int count = 0;
    char c;
    while(is.get(c)){
      if(c == '\n')
        count++;
    }
    return count;
  }

  void accept(Visitor &v) {
    v.visit(this);
  }

};

#endif
