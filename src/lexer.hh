#pragma once
#include <unordered_map>
#include <vector>

class Lexer
{
public:
  Lexer(const char *beg);
  ~Lexer();
  void scanAll();

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
  std::unordered_map<char *, Token> keywords = {
      {"while", Token::Kind::While},
      {"if", Token::Kind::If},
      {"else", Token::Kind::Else},
      {"skip", Token::Kind::Skip}};
  std::vector<Token *> tokens;
};