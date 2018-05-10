#ifndef VISITE_H
#define VISITE_H

 std::string visite(Node * f){
   std::string _visiteResult;
   Iterator<Node *>* position = f->createIterator();
   for(position->first(); !position->isDone(); position->next()){
     _visiteResult += ",";
     _visiteResult += position->currentItem()->name();
     Folder * folder = dynamic_cast<Folder *>(position->currentItem());
     if(folder){
       _visiteResult += ",";
       _visiteResult += visite(position->currentItem());
     }
   }
   _visiteResult.erase(_visiteResult.begin());
   return _visiteResult;
 }

#endif
