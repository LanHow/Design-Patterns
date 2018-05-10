#ifndef COUNTWORD_VISITOR_H
#define COUNTWORD_VISITOR_H
#include <fstream>
#include <string>
#include "visitor.h"
#include "file.h"

class CountWordVisitor : public Visitor {
public:
  void visit(File * f) {
    getistream(f);
  }

  void visit(Folder * fd) {
    getistream(fd);
    Iterator<Node*>* it = fd->createIterator();
    for(it->first(); !it->isDone(); it->next()) {
      it->currentItem()->accept(*this);
    }
  }

  void visit(Link * l) {
    getistream(l);
  }

  void getistream(Node * n) {
    std::filebuf fb;
    fb.open(n->fullPath(), std::ios::in);
    std::istream is(&fb);
    _result += n->countWords(is);
  }

  std::string getResult() {
    return std::to_string(_result);
  }

private:
  int _result;
};

#endif
