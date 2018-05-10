#include "../src/visitor.h"
#include "../src/find_visitor.h"
#include "../src/countline_visitor.h"
#include "../src/countword_visitor.h"

class VisitorTest : public ::testing::Test{
  protected:
    virtual void SetUp(){
      test_data = new Folder("./test_data");
      hello_cpp = new File("./test_data/hello.cpp");
      folder_1 = new Folder("./test_data/folder_1");
      folder_2 = new Folder("./test_data/folder_1/folder_2");
      a_out = new File("./test_data/folder_1/a.out");
      a_out_2 = new File("./test_data/folder_1/folder_2/a.out");
      hello = new Link("./test_data/hello", a_out);
      link_to_folder_2 = new Link("./test_data/link_to_folder_2", folder_2);
      test_data->add(hello_cpp);
      test_data->add(folder_1);
      folder_1->add(a_out);
      folder_1->add(folder_2);
      folder_2->add(a_out_2);
      test_data->add(hello);
      test_data->add(link_to_folder_2);
    }

    Node * test_data;
    Node * hello_cpp;
    Node * folder_1;
    Node * a_out;
    Node * hello;
    Node * folder_2;
    Node * a_out_2;
    Node * link_to_folder_2;
};

TEST_F(VisitorTest, FindVisitorOnFile) {
  Visitor * v = new FindVisitor("hello.cpp");
  hello_cpp->accept(*v);
  ASSERT_EQ("./test_data/hello.cpp\n",v->getResult());
}

TEST_F(VisitorTest, FindVisitorOnFolder) {
  Visitor *v = new FindVisitor("a.out");
  test_data->accept(*v);
  ASSERT_EQ("./test_data/folder_1/a.out\n./test_data/folder_1/folder_2/a.out\n./test_data/link_to_folder_2/a.out\n", v->getResult());
}

TEST_F(VisitorTest, FindVisitorOnFolder1) {
  Visitor *v = new FindVisitor("test_data");
  test_data->accept(*v);
  ASSERT_EQ("./test_data\n", v->getResult());
}

TEST_F(VisitorTest, FindVisitorOnLink) {
  Visitor *v = new FindVisitor("hello");
  test_data->accept(*v);
  ASSERT_EQ("./test_data/hello\n", v->getResult());
}

TEST_F(VisitorTest, CountLineVisitorOnFile) {
  Visitor *v = new CountLineVisitor();
  hello_cpp->accept(*v);
  ASSERT_EQ("6", v->getResult());
}

TEST_F(VisitorTest, CountLineVisitorOnFile2) {
  Visitor *v = new CountLineVisitor();
  a_out->accept(*v);
  ASSERT_EQ("3", v->getResult());
}

TEST_F(VisitorTest, CountLineVisitorOnFile3) {
  Visitor *v = new CountLineVisitor();
  a_out_2->accept(*v);
  ASSERT_EQ("3", v->getResult());
}

TEST_F(VisitorTest, CountLineVisitorOnFolder) {
  Visitor *v = new CountLineVisitor();
  test_data->accept(*v);
  ASSERT_EQ("15", v->getResult());
}

TEST_F(VisitorTest, CountLineVisitorOnLink) {
  Visitor *v = new CountLineVisitor();
  hello->accept(*v);
  ASSERT_EQ("3", v->getResult());
}

TEST_F(VisitorTest, CountWordVisitorOnFile) {
  Visitor *v = new CountWordVisitor();
  hello_cpp->accept(*v);
  ASSERT_EQ("9", v->getResult());
}

TEST_F(VisitorTest, CountWordVisitorOnFolder) {
  Visitor *v = new CountWordVisitor();
  test_data->accept(*v);
  ASSERT_EQ("90", v->getResult());
}

TEST_F(VisitorTest, CountWordVisitorOnLink) {
  Visitor *v = new CountWordVisitor();
  hello->accept(*v);
  ASSERT_EQ("27", v->getResult());
}
