#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <deque>
#include "Token.hh"

class Lexer
{
public:
  Lexer(const char *pSource, bool keepTokens) : pSource(pSource), keepTokens(keepTokens) {}
  Lexer(const char *pSource) : Lexer(pSource, false) {}
  ~Lexer();
  Token *getNextToken();

private:
  char consume();
  void consumeDigit(char c);
  void consumeIdentifierOrKeyword(char c);
  char peek();
  bool match(char expected);
  void addToken(Token *token);
  void scan();

  const char *pSource;
  bool keepTokens;
  int line = 1;
  int col = 1;
  std::deque<Token *> deque;
  std::unordered_map<std::string, Token::Kind> keywords = {
      {"while", Token::Kind::While},
      {"if", Token::Kind::If},
      {"else", Token::Kind::Else},
      {"skip", Token::Kind::Skip},
      {"int", Token::Kind::Int},
      {"bool", Token::Kind::Bool},
      {"true", Token::Kind::True},
      {"false", Token::Kind::False}};
};
