#include <sstream>
#include <string.h>
#include "SyntaxError.hh"

const char *SyntaxError::what() const noexcept
{
  int line = got->getLine();
  int col = got->getCol();
  char buf[128]; 
  std::ostringstream *ss = new std::ostringstream();
  *ss << "Syntax Error in line " << line << " column " << col << ": Expected \"" << Token::toString(expected) << "\" but got \"" << Token::toString(got->getKind()) << "\".\n";
  const std::string& tmp = ss->str();   
  const char* cstr = tmp.c_str();
  char *copy = new char[strlen(cstr) + 1];
  strcpy(copy, cstr);
  return copy;
}
