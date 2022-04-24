#pragma once

#include <exception>
#include <stdio.h>

class LexerError : public std::exception
{
public:
  LexerError(int line, int col, char c)
      : line(line), col(col), c(c) {}

  const char *what() const noexcept override
  {
    char *buf = new char[256];
    snprintf(buf, 255, "Unexpected character '%s' in line %i column %i.", c, line, col);
    return buf;
  }

private:
  int line;
  int col;
  char c;
};
