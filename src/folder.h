#ifndef FOLDER_H
#define FOLDER_H

#include "node.h"
#include <string>
using namespace std;

class Folder : public Node {
public:
  class FolderIterator: public Iterator<Node *> {
  public:
    FolderIterator(Folder * f){
      _folder = f;
    }

    void first() {
      _currentPosition = _folder->_vNode.begin();
    }
    void next() {
      ++_currentPosition;
    }
    bool isDone() const {
      return (_currentPosition == _folder->_vNode.end());
    }
    Node* currentItem() {
      return *_currentPosition;
    }

  private:
    Folder * _folder;
    vector<Node *>::iterator _currentPosition;
  };
  Folder(const char *path)  : Node(path){
    if(S_ISDIR(_st.st_mode) != 1){
      pathError e;
      throw e;
    }
  }

  int numberOfNodes() {
    return _vNode.size();
  }

  void add(Node *node) {
    _vNode.push_back(node);
  }

  string getType() {
    return "folder";
  }

  Node *getChild(string name) {
    for(int i=0; i<numberOfNodes() ; i++){
      if(name==_vNode[i]->name()) {
        return _vNode[i];
      }
    }
    notFound e;
    throw e;
  }

  void del(string name) {
    bool found = false;
    for (int i = 0; i < numberOfNodes(); i++){
      if (name == _vNode[i]->name()) {
          _vNode.erase(_vNode.begin() + i);
          found = true;
          break;
      }
    }
    if(found == false){
      notFound e;
      throw e;
    }
  }

  int byteCount(){
    int bc = 0;
    for(int i = 0; i < numberOfNodes(); i++){
        bc += _vNode[i]->byteCount();
    }
    return bc;
  }

  int countWords(std::istream &is) {
    return 0;
  }

  int countLines(std::istream &is) {
    return 0;
  }

  Iterator<Node *>* createIterator() {
    return new FolderIterator(this);
  }

  void visite() {
    if(_vNode.size() != 0){
      Iterator<Node *>* position = this->createIterator();
      for(position->first(); !position->isDone(); position->next()){
        _visiteResult += ",";
        _visiteResult += position->currentItem()->name();
        Folder * folder = dynamic_cast<Folder *>(position->currentItem());
        if(folder){
          folder->visite();
          _visiteResult += ",";
          _visiteResult += folder->getAllFileName();
        }
      }
    }
  }

  string getAllFileName() {
    _visiteResult.erase(_visiteResult.begin());
    return _visiteResult;
  }

  void accept(Visitor &v) {
    v.visit(this);
  }

private:
  std::vector<Node *> _vNode;
  string _visiteResult = "";
};

#endif
