#pragma once
#include <exception>
#include <stdexcept>
#include <stdio.h>
#include "Token.hh"

class SyntaxError : public std::exception
{
public:
  explicit SyntaxError(Token::Kind expected, Token *got)
      : expected(expected), got(got) {}

  const char *what() const noexcept;

private:
  Token::Kind expected;
  Token *got;
};
