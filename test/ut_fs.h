#ifndef UTFS_H
#define UTFS_H

#include "../src/file.h"
#include "../src/folder.h"
#include "../src/link.h"
#include <sys/stat.h>
#include <fstream>

class FileSystemTest : public ::testing::Test{
protected:
  virtual void SetUp(){
    nTestData = new Folder("./test_data");
    nHelloCpp = new File("./test_data/hello.cpp");
    nFolder1 = new Folder("./test_data/folder_1");
    nAout = new File("./test_data/folder_1/a.out");
    nLink = new Link("./test_data/hello", nAout);
    nTestData->add(nHelloCpp);
    nTestData->add(nFolder1);
    nFolder1->add(nAout);
    nTestData->add(nLink);
  }
  Node * nTestData;
  Node * nHelloCpp;
  Node * nFolder1;
  Node * nAout;
  Node * nLink;
};


TEST_F(FileSystemTest, FileAsObject){
  ASSERT_EQ(83, nHelloCpp->size());
}

TEST_F(FileSystemTest, FileNotExist){
  ASSERT_ANY_THROW(File("./test_data/f.cpp"));
}

TEST_F(FileSystemTest, FolderAsObject){
  ASSERT_EQ(4096, nFolder1->size());
}

TEST_F(FileSystemTest, NodeAsObject){
  ASSERT_EQ(3, static_cast<Folder *>(nTestData)->numberOfNodes());
}

TEST_F(FileSystemTest, LinkAsObject){
  ASSERT_EQ(14, nLink->size());
}

TEST_F(FileSystemTest, PolymorphismGetType){
  ASSERT_EQ("file",nHelloCpp->getType());
  ASSERT_EQ("folder",nFolder1->getType());
  ASSERT_EQ("link",nLink->getType());
}

TEST_F(FileSystemTest, Name) {
  ASSERT_EQ("hello.cpp", nHelloCpp->name());
}

TEST_F(FileSystemTest, GetChild) {
  ASSERT_EQ(83, nHelloCpp->size());
}

TEST_F(FileSystemTest, DeleteChild) {
  nTestData->del("hello.cpp");
  ASSERT_ANY_THROW(nTestData->getChild("hello.cpp"));
}

TEST_F(FileSystemTest, FolderPathIsFile){
  ASSERT_ANY_THROW(Folder("./test_data/hello.cpp"));
  try {
    Folder("./test_data/hello.cpp");
  }
  catch(std::exception &e){
    ASSERT_EQ("pathError", e.what());
  }
}

TEST_F(FileSystemTest, FolderPathIsSymboliclink){
  ASSERT_ANY_THROW(Folder("./test_data/hello"));
  try {
    Folder("./test_data/hello");
  }
  catch(std::exception &e){
    ASSERT_EQ("pathError", e.what());
  }
}

TEST_F(FileSystemTest, FileNotExistForFile){
  ASSERT_ANY_THROW(File("./test_data/file"));
  try{
    File("./test_data/file");
  }
  catch(std::exception &e){
    ASSERT_EQ("File not Exist!", e.what());
  }
}

TEST_F(FileSystemTest, FolderNotExistForFolder){
  ASSERT_ANY_THROW(Folder("./test_data/folder"));
  try{
    Folder("./test_data/folder");
  }
  catch(std::exception &e){
    ASSERT_EQ("File not Exist!", e.what());
  }
}

TEST_F(FileSystemTest, LinkNotExistForSymboliclink){
  Node * nAout = new File("./test_data/folder_1/a.out");
  ASSERT_ANY_THROW(Link("./test_data/link", nAout));
  try{
    Link("./test_data/link", nAout);
  }
  catch(std::exception &e){
    ASSERT_EQ("File not Exist!", e.what());
  }
}

TEST_F(FileSystemTest, GetChildException){
  Folder test_data("./test_data");
  ASSERT_ANY_THROW(test_data.getChild("nothing"));
  try{
    test_data.getChild("nothing");
  }
  catch(std::exception &e){
    ASSERT_EQ("Not Found", e.what());
  }
}

TEST_F(FileSystemTest, DelException){
  Folder test_data("./test_data");
  ASSERT_ANY_THROW(test_data.del("nothing"));
  try{
    test_data.del("nothing");
  }
  catch(std::exception &e){
    ASSERT_EQ("Not Found", e.what());
  }
}

TEST_F(FileSystemTest, NodeByteCount){
  ASSERT_EQ(83, nHelloCpp->byteCount());
}

TEST_F(FileSystemTest, FolderByteCount){
  Node * nTestData = new Folder("./test_data");
  Node * nHelloCpp = new File("./test_data/hello.cpp");
  Node * nFolder1 = new Folder("./test_data/folder_1");
  Node * nAout = new File("./test_data/folder_1/a.out");
  nTestData->add(nHelloCpp);
  nTestData->add(nFolder1);
  nFolder1->add(nAout);
  ASSERT_EQ(8432+83, nTestData->byteCount());
}

TEST_F(FileSystemTest, LinkTest){
  ASSERT_EQ(8432, nLink->byteCount());
  ASSERT_EQ(83+8432+8432, nTestData->byteCount());
}

TEST_F(FileSystemTest, LinkNullPointerException){
  ASSERT_ANY_THROW(Link("./test_data/hello", nullptr));
  try{
    Link("./test_data/hello", nullptr);
  }
  catch(std::exception &e){
    ASSERT_EQ("Node can not be null", e.what());
  }
}

TEST_F(FileSystemTest, CountWordsFile){
  Node * nFile = new File("./test_data/hello.cpp");
  std::filebuf fb;
  fb.open("./test_data/hello.cpp", std::ios::in);
  std::istream is(&fb);
  ASSERT_EQ(9, nFile->countWords(is));
}

TEST_F(FileSystemTest, CountWordsFolder){
  std::filebuf fb;
  fb.open("./test_data/folder_1", std::ios::in);
  std::istream is(&fb);
  ASSERT_EQ(0, nFolder1->countWords(is));
}

TEST_F(FileSystemTest, CountWordsLink){
  std::filebuf fb;
  fb.open("./test_data/hello", std::ios::in);
  std::istream is2(&fb);
  ASSERT_EQ(27, nLink->countWords(is2));
}

TEST_F(FileSystemTest, CountLinesFile){
  std::filebuf fb;
  fb.open("./test_data/hello.cpp", std::ios::in);
  std::istream is(&fb);
  ASSERT_EQ(6, nHelloCpp->countLines(is));
}

TEST_F(FileSystemTest, CountLinesFolder){
  std::filebuf fb;
  fb.open("./test_data/folder_1", std::ios::in);
  std::istream is(&fb);
  ASSERT_EQ(0, nFolder1->countLines(is));
}

TEST_F(FileSystemTest, CountLinesLink){
  std::filebuf fb;
  fb.open("./test_data/hello", std::ios::in);
  std::istream is(&fb);
  ASSERT_EQ(3, nLink->countLines(is));
}
#endif
