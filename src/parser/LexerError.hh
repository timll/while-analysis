#pragma once
#include <exception>
#include <stdio.h>

class LexerError : public std::exception
{
public:
  LexerError(int line, int col, char c)
      : line(line), col(col), c(c) {}

  const char *what() const noexcept override;

private:
  int line;
  int col;
  char c;
};
