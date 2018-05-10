#ifndef NODE_H
#define NODE_H

#include "exception.h"
#include "iterator.h"
#include "visitor.h"
using namespace std;

class Node {
public:
  Node(const char *path) {
    if(lstat(path, &_st)!=0){
      fileNotExist e;
      throw e;
    }
    int n = string(path).rfind('/');
    _name = string(path).substr(n+1);
    _path = string(path).substr(0, n);
    _fullPath = string(path);
  }

  int size() {
    return _st.st_size;
  }

  virtual string getType() {}

  string name() {
    return _name;
  }

  string path() {
    return _path;
  }

  string fullPath() {
    return _fullPath;
  }

  virtual void add(Node * np) {
    illegalOperation e;
    throw e;
  }

  virtual Node *getChild(string name) {
    illegalOperation e;
    throw e;
  }

  virtual void del(string name) {
    illegalOperation e;
    throw e;
  }

  virtual int byteCount() {
    return size();
  }

  virtual int countWords(std::istream &is) {
    illegalOperation e;
    throw e;
  }

  virtual int countLines(std::istream &is) {
    illegalOperation e;
    throw e;
  }

  virtual Iterator<Node *> * createIterator(){
    return new NullIterator<Node *>;
  }

  virtual void visite(){
    illegalOperation e;
    throw e;
  }
  virtual string getAllFileName(){
    illegalOperation e;
    throw e;
  }

  virtual void accept(Visitor &v) {
  }



protected:
  struct stat _st;
  string _name;
  string _path;
  string _fullPath;
};

#endif
