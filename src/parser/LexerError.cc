#include "LexerError.hh"

const char *LexerError::what() const noexcept
{
  char *buf = new char[256];
  snprintf(buf, 255, "Unexpected character '%s' in line %i column %i.\n", c, line, col);
  return buf;
}