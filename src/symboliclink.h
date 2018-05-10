#ifndef LINK_H
#define LINK_H

#include "node.h"
#include <string>
#include <iostream>
using namespace std;

class Symboliclink : public Node{
public:
  Symboliclink(const char * path) : Node(path){
    if(S_ISLNK(_st.st_mode) != 1){
      pathError e;
      throw e;
    }
  }

  string getType() {
    return "symboliclink";
  }
private:
};

#endif
