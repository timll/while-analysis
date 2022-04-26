#pragma once

#include <exception>
#include <stdio.h>
#include "Token.hh"

class SyntaxError : public std::exception
{
public:
  SyntaxError(Token::Kind expected, Token *got)
      : expected(expected), got(got) {}

  const char *what() const noexcept override;

private:
  Token::Kind expected;
  Token *got;
};
