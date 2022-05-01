#include <sstream>
#include <string.h>
#include "ContextError.hh"

const char *TypeMismatch::what() const noexcept
{
  std::ostringstream *ss = new std::ostringstream();
  *ss << "Type mismatch. Expected " << Token::toString(type) << "." << "\n";
  const std::string& tmp = ss->str();   
  const char* cstr = tmp.c_str();
  char *copy = new char[strlen(cstr) + 1];
  strcpy(copy, cstr);
  return copy;
}

const char *VariableRedefined::what() const noexcept
{
  std::ostringstream *ss = new std::ostringstream();
  *ss << "Variable " << this->name << " is already defined in this scope." << "\n";
  const std::string& tmp = ss->str();   
  const char* cstr = tmp.c_str();
  char *copy = new char[strlen(cstr) + 1];
  strcpy(copy, cstr);
  return copy;
}

const char *VariableUndefined::what() const noexcept
{
  std::ostringstream *ss = new std::ostringstream();
  *ss << "Variable " << this->name << " is not defined in this scope." << "\n";
  const std::string& tmp = ss->str();   
  const char* cstr = tmp.c_str();
  char *copy = new char[strlen(cstr) + 1];
  strcpy(copy, cstr);
  return copy;
}
