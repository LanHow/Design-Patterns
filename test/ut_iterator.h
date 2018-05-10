#ifndef UT_ITERATOR_H
#define UT_ITERATOR_H
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/link.h"
#include "../src/iterator.h"
#include "../src/find.h"
#include "../src/visite.h"

class IteratorTest : public ::testing::Test{
  protected:
    virtual void SetUp(){
      test_data = new Folder("./test_data");
      hello_cpp = new File("./test_data/hello.cpp");
      folder_1 = new Folder("./test_data/folder_1");
      a_out = new File("./test_data/folder_1/a.out");
      hello = new Link("./test_data/hello", a_out);
      test_data->add(hello_cpp);
      test_data->add(folder_1);
      folder_1->add(a_out);
      test_data->add(hello);
    }
    Node * test_data;
    Node * hello_cpp;
    Node * folder_1;
    Node * a_out;
    Node * hello;
};

TEST_F(IteratorTest,FileShouldCreateNullIterator){
  Iterator<Node*>* it = hello_cpp->createIterator();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest,FolderShouldCreateFolderIterator){
  Iterator<Node*>* it = test_data->createIterator();
  it->first();
  ASSERT_EQ("hello.cpp", it->currentItem()->name());
  it->next();
  ASSERT_EQ("folder_1", it->currentItem()->name());
  it->next();
  ASSERT_EQ("hello", it->currentItem()->name());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(IteratorTest, FindByname){
  ASSERT_EQ("test_data/hello",find(test_data,"hello"));
}

TEST_F(IteratorTest, RecursiveFindByName){
  ASSERT_EQ("test_data/folder_1/a.out", find(test_data, "a.out"));
}

TEST_F(IteratorTest, FolderVisiteTest){
  test_data->visite();
  Folder *f1 = dynamic_cast<Folder*>(test_data);
  ASSERT_EQ("hello.cpp,folder_1,a.out,hello", f1->getAllFileName());
}

TEST_F(IteratorTest, VisiteTest){
  ASSERT_EQ("hello.cpp,folder_1,a.out,hello", visite(test_data));
}
#endif
