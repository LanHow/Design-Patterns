#ifndef FIND_VISITOR_H
#define FIND_VISITOR_H

#include "visitor.h"
#include "file.h"
#include <string>
#include <vector>

class FindVisitor : public Visitor {
public:
  FindVisitor(std::string name):_name(name), _result("") {}

  void visit(File * f) {
    findName(f);
    _pathStack.pop_back();
  }

  void visit(Link * l) {
    findName(l);
    Folder *folder = dynamic_cast<Folder *>(l->target());
    if(folder) {
      Iterator<Node*>* it = folder->createIterator();
      for(it->first(); !it->isDone(); it->next()) {
        it->currentItem()->accept(*this);
      }
    }
    _pathStack.pop_back();
  }

  void visit(Folder * fd) {
    Iterator<Node*>* it = fd->createIterator();
    findName(fd);
    for(it->first(); !it->isDone(); it->next()) {
      it->currentItem()->accept(*this);
    }
    _pathStack.pop_back();
  }

  void findName(Node *n) {
    if(_pathStack.empty()){
      _pathStack.push_back(n->path());
    }
    _pathStack.push_back(n->name());
    if(n->name() == _name) {
      std::vector<std::string>::iterator it;
      std::string currentPath;
      for(it=_pathStack.begin(); it!=_pathStack.end(); it++){
        currentPath += *it + "/";
      }
      _result += currentPath.substr(0, currentPath.size()-1) + "\n";
    }
  }

  std::string getResult() {
    return _result;
  }
private:
  std::string _name;
  std::string _result;
  std::vector<std::string> _pathStack;
};

#endif
