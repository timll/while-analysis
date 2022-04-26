#include "SyntaxError.hh"

const char *SyntaxError::what() const noexcept
{
  char *buf = new char[512];
  snprintf(buf, 511, "Syntax Error in line %i column %i: Expected %s but got %s.\n", got->getLine(), got->getCol(), "TODO" /* expected */, "TODO" /* got->getKind() */);
  return buf;
}
