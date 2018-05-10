#ifndef VISITOR_H
#define VISITOR_H

#include <string>
class File;
class Link;
class Folder;

class Visitor {
public:
  virtual void visit(File * f) = 0;
  virtual void visit(Link * l) = 0;
  virtual void visit(Folder * fd) = 0;
  virtual std::string getResult() = 0;
};



#endif
