#ifndef LINK_H
#define LINK_H

#include "node.h"
#include <string>
using namespace std;

class Link : public Node{
public:
  Link(const char * path, Node * target) : Node(path){
    if(target == nullptr){
      NodeCanNotBeNull e;
      throw e;
    }
    _target = target;
    if(S_ISLNK(_st.st_mode) != 1){
      pathError e;
      throw e;
    }
  }

  string getType() {
    return "link";
  }

  int byteCount() {
    return _target->byteCount();
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

  Node *target() {
    return _target;
  }

private:
  Node *_target;
};

#endif
