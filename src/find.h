#ifndef FIND_H
#define FIND_H

#include "node.h"
#include <string>
std::string find(Node* n, std::string name){
  std::string returnString;
  Iterator<Node *> * it = n->createIterator();
  for(it->first(); !it->isDone(); it->next()){
    Folder * folder = dynamic_cast<Folder *>(it->currentItem());
    if(name == it->currentItem()->name()){
      returnString = n->name() + "/" + name;
    }
    else if(folder)
      returnString = n->name() + "/" + find(folder, name);
  }
  return returnString;
}
#endif
