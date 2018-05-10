#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

struct notFound : std::exception {
  const char* what() const noexcept {return "Not Found";}
};

struct pathError : std::exception {
  const char* what() const noexcept {return "pathError";}
};

struct illegalOperation : std::exception {
  const char* what() const noexcept {return "Illegal operation";}
};

struct fileNotExist : std::exception {
  const char* what() const noexcept {return "File not Exist!";}
};

struct NodeCanNotBeNull : std::exception {
  const char* what() const noexcept {return "Node can not be null";}
};
#endif
