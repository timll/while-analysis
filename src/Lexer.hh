#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "Token.hh"

class Lexer
{
public:
  Lexer(const char *beg);
  ~Lexer();
  void scanAll();
  Token *getToken(int i);

private:
  char consume();
  void consumeDigit(char c);
  void consumeIdentifierOrKeyword(char c);
  char peek();
  bool match(char expected);
  void addToken(Token *token);
  void scan();

  const char *pSource;
  int line = 1;
  int col = 1;
  std::unordered_map<std::string, Token::Kind> keywords = {
      {"while", Token::Kind::While},
      {"if", Token::Kind::If},
      {"else", Token::Kind::Else},
      {"skip", Token::Kind::Skip}};
  std::vector<Token *> tokens;
};
