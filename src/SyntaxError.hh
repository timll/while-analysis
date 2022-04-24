#pragma once

#include <exception>
#include <stdio.h>
#include "Token.hh"

class SyntaxError : public std::exception
{
public:
  SyntaxError(Token::Kind expected, Token *got)
      : expected(expected), got(got) {}

  const char *what() const noexcept override
  {
    char *buf = new char[512];
    snprintf(buf, 500, "Syntax Error in line %i column %i: Expected %s but got %s.", got->getLine(), got->getCol(), expected, "TODO" /* got->getKind() */);
    return buf;
  }

private:
  Token::Kind expected;
  Token *got;
};
