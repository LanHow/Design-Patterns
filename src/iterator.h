#ifndef ITERATOR_H
#define ITERATOR_H

template <class Item>
class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual bool isDone() const = 0;
  virtual Item currentItem() = 0;
};

template <class Item>
class NullIterator : public Iterator<Item> {
public:
  void first() {}
  void next() {}
  bool isDone() const {return true;}
  Item currentItem() {return Item();}
};
#endif
