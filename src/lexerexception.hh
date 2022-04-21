#pragma once
#include <exception>
#include <stdio.h>

class LexerException : public std::exception
{
public:
  LexerException(int line, int col, char tok) {
    this->line = line;
    this->col = col;
    this->tok = tok;
  }

  const char * what() const noexcept override {
    char *buf = new char[256];
    snprintf(buf, 255, "Unexpected character '%s' in line %i column %i.", tok, line, col);
    return buf;
  }

private:
  int line;
  int col;
  char tok;
};
